#!/bin/sh
PLATFORM=/root/platform
export PATH=${PATH}:${PLATFORM}
mount -t jffs2 /dev/mtdblock5 /root/configs

if [ -f /root/configs/updating ]; then
        echo "activate plan b"
	mount -t squashfs /dev/mtdblock4 /root/firmware
else
	mount -t squashfs /dev/mtdblock3 /root/firmware
fi
mount /dev/mmcblk0p1 /mnt/sdcard -o errors=continue
mount -o remount,rw /mnt/sdcard
if [ -f /mnt/sdcard/rom.bin ]; then
${PLATFORM}/ota_update 0 /mnt/sdcard/rom.bin
fi

firmware_init.sh
