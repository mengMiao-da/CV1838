cmd_u-boot := /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/host-tools/gcc/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-ld.bfd   -pie  --gc-sections -Bstatic  --no-dynamic-linker -Ttext 0x108000000 -o u-boot -T u-boot.lds arch/arm/cpu/armv8/start.o --start-group  arch/arm/cpu/built-in.o  arch/arm/cpu/armv8/built-in.o  arch/arm/lib/built-in.o  board/cvitek/cv1835/built-in.o  cmd/built-in.o  common/built-in.o  disk/built-in.o  drivers/built-in.o  drivers/dma/built-in.o  drivers/gpio/built-in.o  drivers/i2c/built-in.o  drivers/mtd/built-in.o  drivers/mtd/nand/built-in.o  drivers/mtd/onenand/built-in.o  drivers/mtd/spi/built-in.o  drivers/mtd/ubi/built-in.o  drivers/net/built-in.o  drivers/net/phy/built-in.o  drivers/pci/built-in.o  drivers/power/built-in.o  drivers/power/battery/built-in.o  drivers/power/domain/built-in.o  drivers/power/fuel_gauge/built-in.o  drivers/power/mfd/built-in.o  drivers/power/pmic/built-in.o  drivers/power/regulator/built-in.o  drivers/serial/built-in.o  drivers/spi/built-in.o  drivers/usb/common/built-in.o  drivers/usb/dwc3/built-in.o  drivers/usb/emul/built-in.o  drivers/usb/eth/built-in.o  drivers/usb/gadget/built-in.o  drivers/usb/gadget/udc/built-in.o  drivers/usb/host/built-in.o  drivers/usb/musb-new/built-in.o  drivers/usb/musb/built-in.o  drivers/usb/phy/built-in.o  drivers/usb/ulpi/built-in.o  fs/built-in.o  lib/built-in.o  net/built-in.o  test/built-in.o  test/dm/built-in.o --end-group -L /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/host-tools/gcc/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin/../lib/gcc/aarch64-linux-gnu/6.3.1 -lgcc -Map u-boot.map
