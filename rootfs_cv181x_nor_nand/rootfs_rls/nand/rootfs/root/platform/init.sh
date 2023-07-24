#!/bin/sh
PLATFORM=/root/platform
export PATH=${PATH}:${PLATFORM}

a_rootfs=`cat /proc/cmdline  | awk -F '=' '{print $2}' | awk '{print $1}'`

#ubiattach /dev/ubi_ctrl -m 8
#if [ $? != 0  ]; then
  #echo 'ubiattach failed, Try ubiformat and ubimkvol'
	#ubiformat -y /dev/mtd8
	#ubiattach /dev/ubi_ctrl -m 8
	#ubimkvol /dev/ubi1 -N CFG -m
#fi

ubiattach /dev/ubi_ctrl -m 7
if [ $? != 0  ]; then
  echo 'ubiattach failed, Try ubiformat and ubimkvol'
	ubiformat -y /dev/mtd7
	ubiattach /dev/ubi_ctrl -m 7
	ubimkvol /dev/ubi1 -N CFG -m
fi

sleep 1
if [ ! -c /dev/ubi1_0 ]; then
	mdev -s
fi
mount -t ubifs -o sync /dev/ubi1_0 /root/configs
if [ $? != 0  ]; then
	echo 'Mount /root/configs failed, Try formatting and remounting'
	ubimkvol /dev/ubi1 -N CFG -m
	sleep 1
	mount -t ubifs -o sync /dev/ubi1_0  /root/configs
fi

#ubiattach -m 7 -d 2 /dev/ubi_ctrl
#mount -t ubifs -o sync /dev/ubi2_0 /root/data

ubiattach -m 3 -d 3 /dev/ubi_ctrl
ubiblock -c /dev/ubi3_0
ubiattach -m 6 -d 6 /dev/ubi_ctrl
ubiblock -c /dev/ubi6_0

if [ ${a_rootfs} != "ROOTFS2" ]; then
	echo "/dev/mtd3" > /tmp/eapil_app_mtd
else
	echo "/dev/mtd6" > /tmp/eapil_app_mtd
fi

echo ${a_rootfs}
if [ ${a_rootfs} != "ROOTFS2" ]; then
	if [ -b /dev/ubiblock3_0 ]; then
		mount -t squashfs /dev/ubiblock3_0 /root/firmware
	else
		mount -t squashfs /dev/ubiblock6_0 /root/firmware
	fi
   # mount -t squashfs /dev/mtdblock3 /root/firmware
else
	if [ -b /dev/ubiblock6_0 ]; then
		mount -t squashfs /dev/ubiblock6_0 /root/firmware
	else
		mount -t squashfs /dev/ubiblock3_0 /root/firmware
	fi
fi

sleep 1

mount /dev/mmcblk0p1 /mnt/sdcard -o errors=continue
mount -o remount,rw /mnt/sdcard
if [ -f /mnt/sdcard/rom.bin ]; then
${PLATFORM}/ota_update 1 /mnt/sdcard/rom.bin
fi

firmware_init.sh
