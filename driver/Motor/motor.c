//
// Created by simon on 20-5-3.
//
#include "motor.h"

#include <asm/io.h>
#include <asm/irq.h>  //linux中断定义
#include <asm/uaccess.h>  //linux中的用户态内存交互函数，copy_from_user(),copy_to_user()等
#include <linux/delay.h>
#include <linux/device.h>  //
#include <linux/fs.h>  //文件系统有关的，结构体file_operations也在fs头文件定义
#include <linux/gfp.h>
#include <linux/gpio.h>
#include <linux/init.h>  //init和exit相关宏
#include <linux/interrupt.h>  //包含与中断相关的大部分宏及结构体的定义，request_irq()等
#include <linux/irq.h>
#include <linux/kernel.h>
#include <linux/module.h>  //所有模块都需要的头文件
#include <linux/mutex.h>
#include <linux/poll.h>
#include <linux/sched.h>  //声明printk()这个内核态的函数
#include <linux/slab.h>
#include <linux/time.h>

//内核需要开启高精度timer 
// General setup  ---> 
//   Timers subsystem  ---> 
//     [*] High Resolution Timer Support
//外部参数设定
#define MOTOR_GEAR_RATIO 64    //齿轮比 1/32
#define MOTOR_STEP_ANGLE 5625  //步进角度×1000
#define MOTOR_SPEED 20         // unit: ms/度

//内部参数设定
//定时器触发间隔,一次触发一个步进 unit: us
#define MOTOR_TIMER_INV (MOTOR_STEP_ANGLE * MOTOR_SPEED / MOTOR_GEAR_RATIO)
//调试打印间隔
#define MOTOR_PRINT_INV (1000 * 1000 / MOTOR_TIMER_INV)  // unit: us

#define Angle2Step(x) ((x)*1000 * MOTOR_GEAR_RATIO / MOTOR_STEP_ANGLE)
#define Step2Angle(x) ((x)*MOTOR_STEP_ANGLE / MOTOR_GEAR_RATIO / 1000)

static int g_centre_v = -1;	///垂直中心点全程百分比
module_param(g_centre_v, int, S_IRUGO);
MODULE_PARM_DESC(g_centre_v, "The value is vertical centre percent");

static int g_centre_h = -1;	///水平中心点全程百分比
module_param(g_centre_h, int, S_IRUGO);
MODULE_PARM_DESC(g_centre_h, "The value is horizontal centre percent");


static unsigned int g_asyn_run = 0;
module_param(g_asyn_run, int, S_IRUGO);
MODULE_PARM_DESC(g_asyn_run, "Whether the two motors operate asynchronously");


unsigned int motor_speed = MOTOR_SPEED;
unsigned long motor_Timer_inv = MOTOR_TIMER_INV;

typedef enum { MOTOR_NOT_INIT = 0, MOTOR_INITTING, MOTOR_INITED } MOTOR_STAT_E;
typedef enum { MOTOR_CW = 0, MOTOR_CCW } MOTOR_DIR_E;
//蓝 棕 黄 黑
// 0 cw,1 ccw
unsigned char CCCW[2][8][4] = {{
	   {0, 0, 0, 1},
	   {0, 0, 1, 1},
	   {0, 0, 1, 0},
	   {0, 1, 1, 0},
	   {0, 1, 0, 0},
	   {1, 1, 0, 0},
	   {1, 0, 0, 0},
	   {1, 0, 0, 1},
   },
   {{0, 0, 0, 1},
	{1, 0, 0, 1},
	{1, 0, 0, 0},
	{1, 1, 0, 0},
	{0, 1, 0, 0},
	{0, 1, 1, 0},
	{0, 0, 1, 0},
	{0, 0, 1, 1}}};
	
int mpinA[] = {
	GPIO_PWR(20),
	GPIO_PWR(21),
	GPIO_PWR(22),
	GPIO_PWR(23)
};	

int mpinB[] = {
	GPIO_PWR(25),
	GPIO_PWR(26),
	GPIO_PWR(18),
	GPIO_PWR(19)
};

	

typedef struct {
	int cycle_idx;
	int posi;
	int max_posi;
	int offset;
	int dir;
	int *pin;
	int angle;
} motor_t;

typedef struct {
	struct hrtimer timer;
	ktime_t kt;
	struct class *mclass;
	struct device *mdevice;
	int major;
	int posi_inited;
	motor_t mo[2];
	struct mutex mutex;
	int turn_status;				//电机转动状态 0- 停止，1- 转动
} motor_drv;

static motor_drv motor;

static void motor_step(void) {
	int i, j, step;
	static int cnt = 0;
	if (motor.posi_inited == MOTOR_NOT_INIT) return;
	for (i = 0; i < 2; i++) {
		// reload motor direction at the beginning of cycle
		if (motor.mo[i].cycle_idx == 0)
			motor.mo[i].dir = motor.mo[i].offset > 0 ? MOTOR_CW : MOTOR_CCW;
		if ((motor.mo[i].posi <= -motor.mo[i].max_posi && motor.mo[i].offset < 0) ||
				(motor.mo[i].posi >= motor.mo[i].max_posi && motor.mo[i].offset > 0)) {
			motor.mo[i].offset = 0;
		}
		// if offset not equal to 0 or if the cycle not complete,then finish it
		if (motor.mo[i].offset || motor.mo[i].cycle_idx) {
			for (j = 0; j < 4; j++)
				gpio_set_value(motor.mo[i].pin[j],
						CCCW[motor.mo[i].dir][motor.mo[i].cycle_idx][j]);
			if (i) {
				cnt++;
				// printk("%d,cnt=%d\n", motor.mo[i].dir, cnt);
			}
			motor.mo[i].cycle_idx++;
			if (motor.mo[i].cycle_idx == 8) {
				motor.mo[i].cycle_idx = 0;
			}
			step = (motor.mo[i].dir == MOTOR_CW) ? 1 : -1;
			motor.mo[i].posi += step;
			if (motor.mo[i].offset) motor.mo[i].offset -= step;
			return;
		} else {
			for (j = 0; j < 4; j++) gpio_set_value(motor.mo[i].pin[j], 0);
		}
	}
}


static int motor_step_time_share(int chn,int run) {
	int i = chn;
	int j, step;
	if (motor.posi_inited == MOTOR_NOT_INIT) 
		return -1;
	if(run == 0) {
		for (j = 0; j < 4; j++) gpio_set_value(motor.mo[i].pin[j], 0);
		return 0;
	}
	// reload motor direction at the beginning of cycle
	if (motor.mo[i].cycle_idx == 0)
		motor.mo[i].dir = motor.mo[i].offset > 0 ? MOTOR_CW : MOTOR_CCW;
	if ((motor.mo[i].posi <= -motor.mo[i].max_posi && motor.mo[i].offset < 0) ||
			(motor.mo[i].posi >= motor.mo[i].max_posi && motor.mo[i].offset > 0)) {
		motor.mo[i].offset = 0;
	}
	// if offset not equal to 0 or if the cycle not complete,then finish it
	if (motor.mo[i].offset || motor.mo[i].cycle_idx) {
		for (j = 0; j < 4; j++)
			gpio_set_value(motor.mo[i].pin[j],
					CCCW[motor.mo[i].dir][motor.mo[i].cycle_idx][j]);

		motor.mo[i].cycle_idx++;
		if (motor.mo[i].cycle_idx == 8) {
			motor.mo[i].cycle_idx = 0;
		}
		step = (motor.mo[i].dir == MOTOR_CW) ? 1 : -1;
		if(motor.mo[i].offset){
			motor.mo[i].posi += step;
			if (motor.mo[i].offset) motor.mo[i].offset -= step;
		}
		return 1;
	} else {
		for (j = 0; j < 4; j++) gpio_set_value(motor.mo[i].pin[j], 0);
	}
	return 0;

}


enum hrtimer_restart motor_timer_callback(struct hrtimer *timer) {
	//这里使用 motor_step_time_share 是为了避免两个点机同时运转造成过大的功耗
	int ret = motor_step_time_share(0,1);
	if(g_asyn_run){
		ret |= motor_step_time_share(1,1);
	}else{
		if(ret != 1){
			ret |= motor_step_time_share(1,1);
		}
	}
	if((motor.turn_status == 1)&&(ret == 0)){
		motor_step_time_share(1,0);
	}
	if(ret != motor.turn_status)
		motor.turn_status = ret;
	
	hrtimer_forward(timer, timer->base->get_time(), motor.kt);
	return HRTIMER_RESTART;
}

static void motor_dev_init(void) {
	unsigned int i, j;
	motor.posi_inited = 0;
	motor.turn_status = 0;
	// struct init
	for (i = 0; i < 2; i++) {
		motor.mo[i].cycle_idx = 0;
		motor.mo[i].posi = 0;
		motor.mo[i].max_posi = 0;
		motor.mo[i].offset = 0;
		motor.mo[i].dir = 0;
	}
	
	motor.mo[0].pin = mpinA;
	motor.mo[1].pin = mpinB;
	// gpio init
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 4; j++) {
			gpio_request(motor.mo[i].pin[j], NULL);
			gpio_direction_output(motor.mo[i].pin[j], 0);
		}
	}

	// timer init
	hrtimer_init(&motor.timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	motor.kt =
		ktime_set(motor_Timer_inv / 1000000, (motor_Timer_inv % 1000000) * 1000);
	motor.timer.function = motor_timer_callback;
	hrtimer_start(&motor.timer, motor.kt, HRTIMER_MODE_REL);
	// mutex init
	mutex_init(&motor.mutex);
}

static void motor_dev_deinit(void) {
	unsigned int i, j;
	hrtimer_cancel(&motor.timer);
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 4; j++) {
			gpio_set_value(motor.mo[i].pin[j], 0);
			gpio_free(motor.mo[i].pin[j]);
		}
	}
	mutex_destroy(&motor.mutex);
}

#define mmax(x, y) ((x) > (y) ? (x) : (y))
#define align4(x) (((x) << 2) >> 2)
static int motor_posi_init(unsigned int max_angle) {
	int i;
	if(g_centre_h < 0){
		g_centre_h = max_angle & 0xffff;
	}
	if(g_centre_v < 0){
		g_centre_v = (max_angle >> 16) & 0xffff;
	}
	printk("into motor_posi_init\n");
	motor.posi_inited = MOTOR_NOT_INIT;
	msleep(100);  // ensure timer not change the value of motor
	for (i = 0; i < 2; i++) {
		motor.mo[i].cycle_idx = 0;
		motor.mo[i].max_posi =
			Angle2Step((max_angle >> (i ? 16 : 0)) & 0xffff) >> 1;
		motor.mo[i].posi = -motor.mo[i].max_posi;
		motor.mo[i].offset = motor.mo[i].max_posi << 1;
		motor.mo[i].dir = 0;
		printk("mo[%d] max_posi=%d,posi=%d,offset=%d\n", i, motor.mo[i].max_posi,
				motor.mo[i].posi, motor.mo[i].offset);
	}
	motor.posi_inited = MOTOR_INITTING;
	do{
		msleep(100);
	}while (motor.turn_status); //等待电机转完。
	
	for (i = 0; i < 2; i++)
		printk("[%d] off[%d],pos[%d]\n", i, motor.mo[i].offset, motor.mo[i].posi);
	motor.posi_inited = MOTOR_NOT_INIT;
	msleep(100);  // ensure timer not change the value of motor
	
	int tmp_centre_h = Angle2Step(g_centre_h);
	int tmp_centre_v = Angle2Step(g_centre_v);

	motor.mo[0].offset = -tmp_centre_h;
	motor.mo[1].offset = -tmp_centre_v;
	printk("0:off[%d],pos[%d];1:off[%d],pos[%d]\n", motor.mo[0].offset,motor.mo[0].posi,
	motor.mo[1].offset,motor.mo[1].posi);

	motor.posi_inited = MOTOR_INITTING;
	do{
		msleep(100);
	}while (motor.turn_status);
	for (i = 0; i < 2; i++)
		printk("[%d] off[%d],pos[%d]\n", i, motor.mo[i].offset,
				motor.mo[i].posi);
	motor.posi_inited = MOTOR_INITED;
	return 0;
}

static int motor_posi_init_stats(void) { return motor.posi_inited; }

static int motor_set_angle(int idx, int angle) {
	int ret = -1;
	mutex_lock(&motor.mutex);
	if (motor.posi_inited == MOTOR_INITED) {
		motor.mo[idx].offset = Angle2Step(angle);
		ret = 0;
	}
	mutex_unlock(&motor.mutex);
	return ret;
}
// step = angle / 5.625 * 64
// angle = step * 5.625 / 64
static int motor_get_angle(int idx) { return Step2Angle(motor.mo[idx].posi); }


static int motor_set_speed(int angle)
{
	int ret = -1;
	mutex_lock(&motor.mutex);
	if((angle >=0) && (angle <= 100)){
		motor_speed = (100 - angle)+10;
		motor_Timer_inv = MOTOR_STEP_ANGLE * motor_speed / MOTOR_GEAR_RATIO;
		motor.kt =ktime_set(motor_Timer_inv / 1000000, (motor_Timer_inv % 1000000) * 1000);
		ret = 0;
	}
	mutex_unlock(&motor.mutex);
	return ret;
}

static int motor_get_speed(void)
{
	int ret = -1;
	mutex_lock(&motor.mutex);
	ret = (100 - motor_speed)+10;
	mutex_unlock(&motor.mutex);
	return ret;
}

static long motor_drv_ioctl(struct file *node, unsigned int cmd,
		unsigned long arg) {
	int ret = -1;
	int param = arg;

	switch (cmd) {
		case MOTOR_IOCTL_INIT:
			ret = motor_posi_init((unsigned int)param);
			break;
		case MOTOR_IOCTL_INIT_STA:
			ret = motor_posi_init_stats();
			break;
		case MOTOR_IOCTL_SET_MA:
			ret = motor_set_angle(0, param);
			break;
		case MOTOR_IOCTL_GET_MA:
			ret = motor_get_angle(0);
			copy_to_user((void __user *)arg, (void *) &ret, sizeof(int));
			break;
		case MOTOR_IOCTL_SET_MB:
			ret = motor_set_angle(1, param);
			break;
		case MOTOR_IOCTL_GET_MB:
			ret = motor_get_angle(1);
			copy_to_user((void __user *)arg, (void *) &ret, sizeof(int));
			break;
		case MOTOR_IOCTL_SET_SPEED:
			ret = motor_set_speed(param);
			break;
		case MOTOR_IOCTL_GET_SPEED:
			ret = motor_get_speed();
			break;  
		default:
			printk("error cmd:%08x\n", cmd);
			ret = -1;
	}
	return ret;
}

static int motor_drv_open(struct inode *inode, struct file *file) { return 0; }

static int motor_drv_close(struct inode *inode, struct file *file) { return 0; }

static struct file_operations motor_drv_fops = {
	.owner = THIS_MODULE,
	.open = motor_drv_open,
	.release = motor_drv_close,
	.unlocked_ioctl = motor_drv_ioctl};

static int motor_drv_init(void) {
	motor_dev_init();
	motor.major = register_chrdev(0, "motor_drv", &motor_drv_fops);
	motor.mclass = class_create(THIS_MODULE, "motor_drv");
	motor.mdevice =
		device_create(motor.mclass, NULL, MKDEV(motor.major, 0), NULL, "motor");
	printk("motor drive is insmod!!\n");
	return 0;
}

static void motor_drv_exit(void) {
	unregister_chrdev(motor.major, "motor_drv");
	device_unregister(motor.mdevice);
	class_destroy(motor.mclass);
	motor_dev_deinit();
	printk("motor drive is rmmod!!\n");
}

module_init(motor_drv_init);
module_exit(motor_drv_exit);
MODULE_DESCRIPTION("Motors Driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("cvitek");
