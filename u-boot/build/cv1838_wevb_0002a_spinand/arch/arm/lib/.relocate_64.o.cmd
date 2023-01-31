cmd_arch/arm/lib/relocate_64.o := /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/host-tools/gcc/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-gcc -Wp,-MD,arch/arm/lib/.relocate_64.o.d  -nostdinc -isystem /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/host-tools/gcc/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin/../lib/gcc/aarch64-linux-gnu/6.3.1/include -Iinclude  -I/home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include  -I/home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/arch/arm/include  -I/home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/lib/mbedtls-2.13.0/include -include /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/linux/kconfig.h -D__KERNEL__ -D__UBOOT__ -DCVICHIP=cv1838 -DCVIBOARD=wevb_0002a_spinand -DCV1838_WEVB_0002A_SPINAND -DMIPI_PANEL_HX8394 -DMIPI_PANEL_4_LANES -DBOOTLOGO_ISP_RESET -D__ASSEMBLY__ -g -D__ARM__ -fno-pic -mstrict-align -ffunction-sections -fdata-sections -fno-common -ffixed-r9 -fno-common -ffixed-x18 -pipe -march=armv8-a -D__LINUX_ARM_ARCH__=8   -c -o arch/arm/lib/relocate_64.o /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/arch/arm/lib/relocate_64.S

source_arch/arm/lib/relocate_64.o := /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/arch/arm/lib/relocate_64.S

deps_arch/arm/lib/relocate_64.o := \
  /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/asm-offsets.h \
  include/generated/generic-asm-offsets.h \
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
    $(wildcard include/config/arm64.h) \
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
  /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/elf.h \
  /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/linux/linkage.h \
  /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/arch/arm/include/asm/linkage.h \
  /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/arch/arm/include/asm/macro.h \
    $(wildcard include/config/armv8/multientry.h) \
    $(wildcard include/config/armv8/psci.h) \
    $(wildcard include/config/gicv3.h) \
    $(wildcard include/config/gicv2.h) \
  /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/arch/arm/include/asm/system.h \
    $(wildcard include/config/armv7/lpae.h) \
    $(wildcard include/config/cpu/v7.h) \
  /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/common.h \
    $(wildcard include/config/sys/support/64bit/data.h) \
    $(wildcard include/config/panic/hang.h) \
    $(wildcard include/config/env/is/embedded.h) \
    $(wildcard include/config/sys/monitor/base.h) \
    $(wildcard include/config/sys/monitor/len.h) \
    $(wildcard include/config/env/is/in/nvram.h) \
    $(wildcard include/config/auto/complete.h) \
    $(wildcard include/config/cmd/eeprom.h) \
    $(wildcard include/config/spi.h) \
    $(wildcard include/config/sys/i2c/eeprom/addr.h) \
    $(wildcard include/config/sys/def/eeprom/addr.h) \
    $(wildcard include/config/env/eeprom/is/on/i2c.h) \
    $(wildcard include/config/sys/dram/test.h) \
    $(wildcard include/config/arm.h) \
    $(wildcard include/config/tpl/build.h) \
    $(wildcard include/config/tpl/serial/support.h) \
    $(wildcard include/config/spl/serial/support.h) \
    $(wildcard include/config/led/status.h) \
    $(wildcard include/config/show/activity.h) \
    $(wildcard include/config/mp.h) \
    $(wildcard include/config/post.h) \
    $(wildcard include/config/has/post.h) \
    $(wildcard include/config/post/alt/list.h) \
    $(wildcard include/config/post/std/list.h) \
    $(wildcard include/config/init/critical.h) \
    $(wildcard include/config/skip/lowlevel/init.h) \
    $(wildcard include/config/efi/stub.h) \
  /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/linux/compiler.h \
    $(wildcard include/config/sparse/rcu/pointer.h) \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/kasan.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
    $(wildcard include/config/kprobes.h) \
  /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/arch/arm/include/asm/barriers.h \

arch/arm/lib/relocate_64.o: $(deps_arch/arm/lib/relocate_64.o)

$(deps_arch/arm/lib/relocate_64.o):
