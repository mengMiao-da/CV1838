#!/bin/sh
rm rootfs.su rootfs.bin
rm  rootfs/root/platform/build_date.txt
echo `date` > rootfs/root/platform/build_date.txt
mksquashfs rootfs ./rootfs.su -root-owned -comp xz

#python3 ~/work/chip/Cvitek/sdk/BSP/v2.1.1.27_source_nand/build/tools/common/spinand_tool/mkubiimg.py --ubionly partition_spinand_page_2k.xml ROOTFS ./rootfs.su rootfs.bin -b 131072 -p 2048

python3 ./spinand_tool/mkubiimg.py --ubionly partition_spinand_page_2k.xml ROOTFS ./rootfs.su rootfs.bin -b 131072 -p 2048
