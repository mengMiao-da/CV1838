#!/bin/sh
PLATFORM=/root/platform
export PATH=${PATH}:${PLATFORM}

a_rootfs=`cat /proc/cmdline | awk -F ' ' '{print $2}' | awk -F '=' '{print $2}'`

ubiattach /dev/ubi_ctrl -m 9
if [ $? != 0  ]; then
	ubiformat -y /dev/mtd9
	ubiattach /dev/ubi_ctrl -m 9
	ubimkvol /dev/ubi1 -N CFG -m
fi

if [ ! -c /dev/ubi1_0 ]; then
	mdev -s
fi
mount -t ubifs -o sync /dev/ubi1_0 /root/configs
if [ $? != 0  ]; then
	echo 'Mount /root/configs failed, Try formatting and remounting'
	ubimkvol /dev/ubi1 -N CFG -m
	mount -t ubifs -o sync /dev/ubi1_0  /root/configs
fi

if [ ${a_rootfs} != "ROOTFS2" ]; then
	echo "/dev/mtd4" > /tmp/eapil_app_mtd
else
	echo "/dev/mtd7" > /tmp/eapil_app_mtd
fi

echo ${a_rootfs}
if [ ${a_rootfs} != "ROOTFS2" ]; then
	mount -t squashfs /dev/mtdblock4 /root/firmware
else
	mount -t squashfs /dev/mtdblock7 /root/firmware
fi

sleep 2

mount /dev/mmcblk0p1 /mnt/sdcard -o errors=continue
mount -o remount,rw /mnt/sdcard
if [ -f /mnt/sdcard/rom.bin ]; then
${PLATFORM}/ota_update 0 /mnt/sdcard/rom.bin
fi

appinit.sh
