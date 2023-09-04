#!/bin/sh
rm  rootfs.bin
rm  rootfs/root/platform/build_date.txt
echo `date` > rootfs/root/platform/build_date.txt
mksquashfs rootfs ./rootfs.bin -b 256k -comp xz -all-root



#python3 ./tool/mkubiimg.py --ubionly ./tool/partition_spinand_page_2k.xml ROOTFS ./rootfs.su rootfs.bin -b 131072 -p 2048

#python3 /home/tfh/work/CVITEK/sdk/BSP/v2.1.1.15_source/build/tools/common/image_tool/raw2cimg.py ./rootfs.spinand ./ ./partition_spinand_page_2k.xml
