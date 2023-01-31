cmd_fs/ubifs/crc16.o := /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/host-tools/gcc/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-gcc -Wp,-MD,fs/ubifs/.crc16.o.d  -nostdinc -isystem /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/host-tools/gcc/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin/../lib/gcc/aarch64-linux-gnu/6.3.1/include -Iinclude  -I/home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include  -I/home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/arch/arm/include  -I/home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/lib/mbedtls-2.13.0/include -include /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/linux/kconfig.h  -I/home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/fs/ubifs -Ifs/ubifs -D__KERNEL__ -D__UBOOT__ -DCVICHIP=cv1838 -DCVIBOARD=wevb_0002a_spinand -DCV1838_WEVB_0002A_SPINAND -DMIPI_PANEL_HX8394 -DMIPI_PANEL_4_LANES -DBOOTLOGO_ISP_RESET -Wall -Wstrict-prototypes -Wno-unused-value -Wno-unused-but-set-variable -Wno-format-security -fno-builtin -ffreestanding -DCONFIG_NAND_SUPPORT -DSPINAND_SQSH -Os -fno-stack-protector -fno-delete-null-pointer-checks -g -fstack-usage -Wno-format-nonliteral -Werror=date-time -D__ARM__ -fno-pic -mstrict-align -ffunction-sections -fdata-sections -fno-common -ffixed-r9 -fno-common -ffixed-x18 -pipe -march=armv8-a -D__LINUX_ARM_ARCH__=8    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(crc16)"  -D"KBUILD_MODNAME=KBUILD_STR(crc16)" -c -o fs/ubifs/crc16.o /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/fs/ubifs/crc16.c

source_fs/ubifs/crc16.o := /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/fs/ubifs/crc16.c

deps_fs/ubifs/crc16.o := \
  /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/linux/types.h \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/use/stdint.h) \
  /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/linux/posix_types.h \
  /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/linux/stddef.h \
  /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/arch/arm/include/asm/posix_types.h \
  /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/arch/arm/include/asm/types.h \
    $(wildcard include/config/arm64.h) \
    $(wildcard include/config/phys/64bit.h) \
    $(wildcard include/config/dma/addr/t/64bit.h) \
  /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/host-tools/gcc/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/lib/gcc/aarch64-linux-gnu/6.3.1/include/stdbool.h \
  /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/fs/ubifs/crc16.h \

fs/ubifs/crc16.o: $(deps_fs/ubifs/crc16.o)

$(deps_fs/ubifs/crc16.o):
