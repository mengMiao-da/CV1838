#the absolute path
LINUX_KERNEL_PATH:=/home/tfh/work/chip/Cvitek/sdk/CV180X/t4.0.1_source/linux_5.10/build/cv180zb_wdmb_0008a_spinor
#complie object

all:
	make ARCH=riscv CROSS_COMPILE=riscv64-unknown-linux-musl- -C $(LINUX_KERNEL_PATH) M=$(shell pwd) modules
obj-m +=motor.o

clean:
	@rm -rf *.o *~ .depend .*.cmd  *.mod.c .tmp_versions *.ko *.symvers modules.order
