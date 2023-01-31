#!/bin/sh
rm rootfs.su rootfs.bin
rm  rootfs/root/platform/build_date.txt
echo `date` > rootfs/root/platform/build_date.txt
mksquashfs rootfs ./rootfs.su -root-owned -comp xz

python3 /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_source/build/tools/common/spinand_tool/mkubiimg.py --ubionly partition_spinand_page_2k.xml ROOTFS ./rootfs.su rootfs.bin -b 131072 -p 2048

#python3 /home/tfh/work/CVITEK/sdk/BSP/v2.1.1.15_source/build/tools/common/image_tool/raw2cimg.py ./rootfs.spinand ./ ./partition_spinand_page_2k.xml
