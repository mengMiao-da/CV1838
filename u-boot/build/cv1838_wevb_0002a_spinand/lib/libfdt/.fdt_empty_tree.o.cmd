cmd_lib/libfdt/fdt_empty_tree.o := /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/host-tools/gcc/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-gcc -Wp,-MD,lib/libfdt/.fdt_empty_tree.o.d  -nostdinc -isystem /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/host-tools/gcc/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin/../lib/gcc/aarch64-linux-gnu/6.3.1/include -Iinclude  -I/home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include  -I/home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/arch/arm/include  -I/home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/lib/mbedtls-2.13.0/include -include /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/linux/kconfig.h  -I/home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/lib/libfdt -Ilib/libfdt -D__KERNEL__ -D__UBOOT__ -DCVICHIP=cv1838 -DCVIBOARD=wevb_0002a_spinand -DCV1838_WEVB_0002A_SPINAND -DMIPI_PANEL_HX8394 -DMIPI_PANEL_4_LANES -DBOOTLOGO_ISP_RESET -Wall -Wstrict-prototypes -Wno-unused-value -Wno-unused-but-set-variable -Wno-format-security -fno-builtin -ffreestanding -DCONFIG_NAND_SUPPORT -DSPINAND_SQSH -Os -fno-stack-protector -fno-delete-null-pointer-checks -g -fstack-usage -Wno-format-nonliteral -Werror=date-time -D__ARM__ -fno-pic -mstrict-align -ffunction-sections -fdata-sections -fno-common -ffixed-r9 -fno-common -ffixed-x18 -pipe -march=armv8-a -D__LINUX_ARM_ARCH__=8    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(fdt_empty_tree)"  -D"KBUILD_MODNAME=KBUILD_STR(fdt_empty_tree)" -c -o lib/libfdt/fdt_empty_tree.o /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/lib/libfdt/fdt_empty_tree.c

source_lib/libfdt/fdt_empty_tree.o := /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/lib/libfdt/fdt_empty_tree.c

deps_lib/libfdt/fdt_empty_tree.o := \
  /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/libfdt_env.h \
  /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/compiler.h \
    $(wildcard include/config/use/stdint.h) \
  /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/host-tools/gcc/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/lib/gcc/aarch64-linux-gnu/6.3.1/include/stddef.h \
  /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/linux/string.h \
  /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/linux/types.h \
    $(wildcard include/config/uid16.h) \
  /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/linux/posix_types.h \
  /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/linux/stddef.h \
  /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/arch/arm/include/asm/posix_types.h \
  /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/arch/arm/include/asm/types.h \
    $(wildcard include/config/arm64.h) \
    $(wildcard include/config/phys/64bit.h) \
    $(wildcard include/config/dma/addr/t/64bit.h) \
  /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/host-tools/gcc/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/lib/gcc/aarch64-linux-gnu/6.3.1/include/stdbool.h \
  /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/arch/arm/include/asm/string.h \
    $(wildcard include/config/use/arch/memcpy.h) \
    $(wildcard include/config/use/arch/memset.h) \
  include/config.h \
    $(wildcard include/config/boarddir.h) \
  /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/config_defaults.h \
    $(wildcard include/config/defaults/h/.h) \
    $(wildcard include/config/bootm/linux.h) \
    $(wildcard include/config/bootm/netbsd.h) \
    $(wildcard include/config/bootm/plan9.h) \
    $(wildcard include/config/bootm/rtems.h) \
    $(wildcard include/config/bootm/vxworks.h) \
    $(wildcard include/config/gzip.h) \
    $(wildcard include/config/zlib.h) \
  /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/config_uncmd_spl.h \
    $(wildcard include/config/uncmd/spl/h//.h) \
    $(wildcard include/config/spl/build.h) \
    $(wildcard include/config/spl/dm.h) \
    $(wildcard include/config/dm/serial.h) \
    $(wildcard include/config/dm/gpio.h) \
    $(wildcard include/config/dm/i2c.h) \
    $(wildcard include/config/dm/spi.h) \
    $(wildcard include/config/dm/warn.h) \
    $(wildcard include/config/dm/stdio.h) \
  /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/configs/cv1835-asic.h \
    $(wildcard include/config/armv8/switch/to/el1.h) \
    $(wildcard include/config/remake/elf.h) \
    $(wildcard include/config/support/raw/initrd.h) \
    $(wildcard include/config/sys/text/base.h) \
    $(wildcard include/config/sys/init/sp/addr.h) \
    $(wildcard include/config/sys/sdram/base.h) \
    $(wildcard include/config/sys/bootm/len.h) \
    $(wildcard include/config/sys/load/addr.h) \
    $(wildcard include/config/sys/malloc/len.h) \
    $(wildcard include/config/env/size.h) \
    $(wildcard include/config/sys/noncached/memory.h) \
    $(wildcard include/config/cons/index.h) \
    $(wildcard include/config/sys/ns16550/com1.h) \
    $(wildcard include/config/sys/ns16550/serial.h) \
    $(wildcard include/config/sys/ns16550/reg/size.h) \
    $(wildcard include/config/sys/ns16550/mem32.h) \
    $(wildcard include/config/sys/ns16550/clk.h) \
    $(wildcard include/config/baudrate.h) \
    $(wildcard include/config/menu/show.h) \
    $(wildcard include/config/bootp/bootfilesize.h) \
    $(wildcard include/config/bootp/bootpath.h) \
    $(wildcard include/config/bootp/gateway.h) \
    $(wildcard include/config/bootp/hostname.h) \
    $(wildcard include/config/bootp/pxe.h) \
    $(wildcard include/config/nr/dram/banks.h) \
    $(wildcard include/config/sys/memtest/start.h) \
    $(wildcard include/config/sys/memtest/end.h) \
    $(wildcard include/config/hw/watchdog.h) \
    $(wildcard include/config/designware/watchdog.h) \
    $(wildcard include/config/watchdog/timeout/msecs.h) \
    $(wildcard include/config/skip/ramdisk.h) \
    $(wildcard include/config/spi/flash.h) \
    $(wildcard include/config/cmd/sf.h) \
    $(wildcard include/config/spi/flash/cvsfc.h) \
    $(wildcard include/config/cmd/mtdparts.h) \
    $(wildcard include/config/mtd/device.h) \
    $(wildcard include/config/mtd/partitions.h) \
    $(wildcard include/config/flash/cfi/mtd.h) \
    $(wildcard include/config/sys/max/flash/banks.h) \
    $(wildcard include/config/spi/flash/mtd.h) \
    $(wildcard include/config/nand/support.h) \
    $(wildcard include/config/env/is/in/nand.h) \
    $(wildcard include/config/cmd/nand.h) \
    $(wildcard include/config/sys/max/nand/device.h) \
    $(wildcard include/config/nand/flash/cvsnfc.h) \
    $(wildcard include/config/sys/max/nand/chips.h) \
    $(wildcard include/config/sys/nand/self/init.h) \
    $(wildcard include/config/rbtree.h) \
    $(wildcard include/config/lzo.h) \
    $(wildcard include/config/cmd/ubi.h) \
    $(wildcard include/config/cmd/ubifs.h) \
    $(wildcard include/config/mtd/ubi/wl/threshold.h) \
    $(wildcard include/config/mtd/ubi/beb/limit.h) \
    $(wildcard include/config/sys/nand/max/chips.h) \
    $(wildcard include/config/sys/nand/base.h) \
    $(wildcard include/config/cvsnfc/max/chip.h) \
    $(wildcard include/config/cvsnfc/reg/base/address.h) \
    $(wildcard include/config/cvsnfc/buffer/base/address.h) \
    $(wildcard include/config/cvsnfc/hardware/pagesize/ecc.h) \
    $(wildcard include/config/sys/nand/base/list.h) \
    $(wildcard include/config/bootlogo.h) \
    $(wildcard include/config/bootcommand.h) \
    $(wildcard include/config/nfsbootcommand.h) \
    $(wildcard include/config/rambootcommand.h) \
    $(wildcard include/config/mmcbootcommand.h) \
    $(wildcard include/config/usbbootcommand.h) \
    $(wildcard include/config/nandbootcommand.h) \
    $(wildcard include/config/emmcbootcommand.h) \
    $(wildcard include/config/ipaddr.h) \
    $(wildcard include/config/netmask.h) \
    $(wildcard include/config/gatewayip.h) \
    $(wildcard include/config/serverip.h) \
    $(wildcard include/config/hostname.h) \
    $(wildcard include/config/rootpath.h) \
    $(wildcard include/config/sys/cbsize.h) \
    $(wildcard include/config/sys/pbsize.h) \
    $(wildcard include/config/sys/prompt.h) \
    $(wildcard include/config/sys/bargsize.h) \
    $(wildcard include/config/cmdline/editing.h) \
    $(wildcard include/config/sys/maxargs.h) \
    $(wildcard include/config/env/addr.h) \
    $(wildcard include/config/env/sect/size.h) \
    $(wildcard include/config/fat/write.h) \
    $(wildcard include/config/env/overwrite.h) \
    $(wildcard include/config/mmc/hs200/support.h) \
    $(wildcard include/config/mmc/supports/tuning.h) \
    $(wildcard include/config/cmd/fastboot.h) \
    $(wildcard include/config/fastboot.h) \
    $(wildcard include/config/fastboot/flash.h) \
    $(wildcard include/config/udp/function/fastboot.h) \
    $(wildcard include/config/fastboot/flash/mmc/dev.h) \
    $(wildcard include/config/fastboot/buf/addr.h) \
    $(wildcard include/config/fastboot/buf/size.h) \
    $(wildcard include/config/extra/env/settings.h) \
  /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/cvipart.h \
    $(wildcard include/config/env/offset.h) \
    $(wildcard include/config/env/offset/redund.h) \
    $(wildcard include/config/sys/redundand/environment.h) \
  /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/cvi_panels/cvi_panel_diffs.h \
  /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/arch/arm/include/asm/config.h \
    $(wildcard include/config/h/.h) \
    $(wildcard include/config/lmb.h) \
    $(wildcard include/config/sys/boot/ramdisk/high.h) \
    $(wildcard include/config/static/rela.h) \
    $(wildcard include/config/arch/ls1021a.h) \
    $(wildcard include/config/cpu/pxa27x.h) \
    $(wildcard include/config/cpu/monahans.h) \
    $(wildcard include/config/cpu/pxa25x.h) \
    $(wildcard include/config/fsl/layerscape.h) \
  /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/config_fallbacks.h \
    $(wildcard include/config/fallbacks/h.h) \
    $(wildcard include/config/spl.h) \
    $(wildcard include/config/spl/pad/to.h) \
    $(wildcard include/config/spl/max/size.h) \
    $(wildcard include/config/sys/baudrate/table.h) \
    $(wildcard include/config/env/is/in/fat.h) \
    $(wildcard include/config/fs/fat.h) \
    $(wildcard include/config/cmd/ext4.h) \
    $(wildcard include/config/cmd/ext2.h) \
    $(wildcard include/config/fs/ext4.h) \
    $(wildcard include/config/cmd/ext4/write.h) \
    $(wildcard include/config/ext4/write.h) \
    $(wildcard include/config/ide.h) \
    $(wildcard include/config/cmd/sata.h) \
    $(wildcard include/config/scsi.h) \
    $(wildcard include/config/cmd/usb.h) \
    $(wildcard include/config/cmd/part.h) \
    $(wildcard include/config/cmd/gpt.h) \
    $(wildcard include/config/mmc.h) \
    $(wildcard include/config/systemace.h) \
    $(wildcard include/config/sandbox.h) \
    $(wildcard include/config/partition/uuids.h) \
    $(wildcard include/config/efi/partition.h) \
    $(wildcard include/config/random/uuid.h) \
    $(wildcard include/config/cmd/uuid.h) \
    $(wildcard include/config/lib/uuid.h) \
    $(wildcard include/config/lib/rand.h) \
    $(wildcard include/config/lib/hw/rand.h) \
    $(wildcard include/config/fit/signature.h) \
    $(wildcard include/config/image/format/legacy.h) \
    $(wildcard include/config/disable/image/legacy.h) \
    $(wildcard include/config/sys/i2c.h) \
    $(wildcard include/config/cmdline.h) \
    $(wildcard include/config/sys/longhelp.h) \
  /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/linux/linux_string.h \
  /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/arch/arm/include/asm/byteorder.h \
  /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/linux/byteorder/little_endian.h \
  /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/linux/compiler.h \
    $(wildcard include/config/sparse/rcu/pointer.h) \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/kasan.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
    $(wildcard include/config/kprobes.h) \
  /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/linux/compiler-gcc.h \
    $(wildcard include/config/arch/supports/optimized/inlining.h) \
    $(wildcard include/config/optimize/inlining.h) \
    $(wildcard include/config/gcov/kernel.h) \
    $(wildcard include/config/arch/use/builtin/bswap.h) \
  /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/linux/byteorder/swab.h \
  /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/linux/byteorder/generic.h \
  /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/linux/types.h \
  /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/vsprintf.h \
    $(wildcard include/config/panic/hang.h) \
  /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/host-tools/gcc/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/lib/gcc/aarch64-linux-gnu/6.3.1/include/stdarg.h \
  /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/fdt.h \
  /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/../lib/libfdt/fdt.h \
  /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/libfdt.h \
  /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/../lib/libfdt/libfdt.h \
  /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/lib/libfdt/libfdt_internal.h \

lib/libfdt/fdt_empty_tree.o: $(deps_lib/libfdt/fdt_empty_tree.o)

$(deps_lib/libfdt/fdt_empty_tree.o):
