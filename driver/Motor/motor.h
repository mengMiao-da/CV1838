//
// Created by simon on 20-5-3.
//

#ifndef MOTOR_MOTOR_H
#define MOTOR_MOTOR_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define GPIO_PA(n) 	(480+n)
#define GPIO_PB(n)	(448+n)
#define GPIO_PC(n) 	(416+n)
#define GPIO_PD(n) 	(404+n)
#define GPIO_PWR(n) (377+n)

#define MOTOR_IOCTL_BASE 'M'

typedef enum MOTOR_IOCTL_E
{
    IOC_NR_MOTOR_INIT = 0,
    IOC_NR_MOTOR_INIT_STA,
    IOC_NR_MOTOR_SET_MA,
    IOC_NR_MOTOR_GET_MA,
    IOC_NR_MOTOR_SET_MB,
    IOC_NR_MOTOR_GET_MB,
    IOC_NR_MOTOR_SET_SPEED,
    IOC_NR_MOTOR_GET_SPEED
}MOTOR_IOCTL_E;

#define MOTOR_IOCTL_INIT            _IOW(MOTOR_IOCTL_BASE, IOC_NR_MOTOR_INIT, int)
#define MOTOR_IOCTL_INIT_STA        _IOR(MOTOR_IOCTL_BASE, IOC_NR_MOTOR_INIT_STA, int)
#define MOTOR_IOCTL_SET_MA          _IOW(MOTOR_IOCTL_BASE, IOC_NR_MOTOR_SET_MA, int)
#define MOTOR_IOCTL_GET_MA          _IOR(MOTOR_IOCTL_BASE, IOC_NR_MOTOR_GET_MA, int)
#define MOTOR_IOCTL_SET_MB          _IOW(MOTOR_IOCTL_BASE, IOC_NR_MOTOR_SET_MB, int)
#define MOTOR_IOCTL_GET_MB          _IOR(MOTOR_IOCTL_BASE, IOC_NR_MOTOR_GET_MB, int)
#define MOTOR_IOCTL_SET_SPEED       _IOR(MOTOR_IOCTL_BASE, IOC_NR_MOTOR_SET_SPEED, int)
#define MOTOR_IOCTL_GET_SPEED       _IOR(MOTOR_IOCTL_BASE, IOC_NR_MOTOR_GET_SPEED, int)



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif //MOTOR_MOTOR_H
