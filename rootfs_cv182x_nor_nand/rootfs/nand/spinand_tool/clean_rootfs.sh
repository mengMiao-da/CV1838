#!/bin/bash

SYSTEM_DIR=$1
rm -f $SYSTEM_DIR/bin/bash
rm -f $SYSTEM_DIR/sbin/e2*
rm -f $SYSTEM_DIR/usr/sbin/blkid
rm -f $SYSTEM_DIR/usr/sbin/sgdisk
rm -f $SYSTEM_DIR/sbin/badblocks 
rm -f $SYSTEM_DIR/sbin/dumpe2fs 
rm -f $SYSTEM_DIR/sbin/e4crypt 
rm -f $SYSTEM_DIR/sbin/init-overlay 
rm -f $SYSTEM_DIR/sbin/tune2fs
#rm -f $SYSTEM_DIR/usr/sbin/ubiformat
rm -f $SYSTEM_DIR/usr/lib/libfastjson.so*
rm -f $SYSTEM_DIR/usr/lib/libext2fs.so*
rm -f $SYSTEM_DIR/usr/lib/libe2p.so*
rm -f $SYSTEM_DIR/usr/lib/libestr.so*
rm -f $SYSTEM_DIR/usr/lib/libhistory.so*
# rm -f $SYSTEM_DIR/usr/lib/libncurses.so*
rm -f $SYSTEM_DIR/usr/lib/libpopt.so*
rm -f $SYSTEM_DIR/usr/lib/libreadline.so*
rm -f $SYSTEM_DIR/mnt/system/usr/lib/libz*
rm -f $SYSTEM_DIR/mnt/system/lib/libz*

rm -f $SYSTEM_DIR/usr/bin/gator*
rm -f $SYSTEM_DIR/usr/bin/gdbserver
rm -f $SYSTEM_DIR/usr/sbin/sshd*
rm -f $SYSTEM_DIR/usr/sbin/rsyslogd
rm -f $SYSTEM_DIR/sbin/syslogd

#rm -f $SYSTEM_DIR/mnt/system/usr/lib/3rd/libini.so*
rm -f $SYSTEM_DIR/mnt/system/usr/lib/3rd/libnanomsg.so*
rm -f $SYSTEM_DIR/mnt/system/usr/lib/3rd/libmp3lame.so*
rm -f $SYSTEM_DIR/mnt/system/usr/lib/3rd/libcvi_mp3enc.so*
#rm -f $SYSTEM_DIR/mnt/system/usr/lib/3rd/libmad.so.0*

#rm -f $SYSTEM_DIR/mnt/system/usr/lib/3rd/libtinyalsa.so
rm -f $SYSTEM_DIR/mnt/system/usr/lib/3rd/libopencv*
rm -f $SYSTEM_DIR/mnt/system/usr/lib/libopencv*
rm -f $SYSTEM_DIR/mnt/system/usr/lib/libgst*
rm -f $SYSTEM_DIR/mnt/system/usr/lib/libg*
rm -f $SYSTEM_DIR/mnt/system/usr/lib/gstreamer-1.0/libgst*
#rm -f $SYSTEM_DIR/mnt/system/usr/lib/libcviai*
#rm -f $SYSTEM_DIR/mnt/system/usr/lib/libcvi_ispd.so*
#rm -f $SYSTEM_DIR/mnt/system/usr/lib/libboost_system.so*
#rm -f $SYSTEM_DIR/mnt/system/usr/lib/libraw_replay.so*
rm -rf $SYSTEM_DIR/mnt/system/usr/lib/gio
rm -rf $SYSTEM_DIR/mnt/system/usr/lib/glib*

rm -rf $SYSTEM_DIR/mnt/system/usr/lib/gstreamer-1.0*
rm -rf $SYSTEM_DIR/mnt/system/usr/lib/cmake
rm -f $SYSTEM_DIR/mnt/system/usr/lib/libcvi_RES1.so
rm -f $SYSTEM_DIR/mnt/system/usr/lib/libaacdec2.so
rm -f $SYSTEM_DIR/mnt/system/usr/lib/libaacenc2.so
rm -f $SYSTEM_DIR/mnt/system/usr/lib/libdnvqe.so
rm -f $SYSTEM_DIR/mnt/system/usr/lib/libcvi_RES.so
rm -f $SYSTEM_DIR/mnt/system/usr/lib/libcvi_ssp2.so
#rm -f $SYSTEM_DIR/mnt/system/usr/lib/libcipher.so
rm -f $SYSTEM_DIR/mnt/system/usr/lib/libinih.so*
rm -f $SYSTEM_DIR/mnt/system/usr/lib/libINIReader.so*
rm -f $SYSTEM_DIR/mnt/system/usr/lib/libanl*
rm -f $SYSTEM_DIR/mnt/system/usr/lib/libjpeg.*
rm -f $SYSTEM_DIR/mnt/system/usr/lib/libsqlite3*
rm -f $SYSTEM_DIR/mnt/system/usr/lib/libavcodec.so*
rm -f $SYSTEM_DIR/mnt/system/usr/lib/libavformat.so*
rm -f $SYSTEM_DIR/mnt/system/usr/lib/libavutil.so*
rm -f $SYSTEM_DIR/mnt/system/usr/lib/libnsl*
rm -f $SYSTEM_DIR/mnt/system/usr/lib/libcvi_mp3enc.so*
rm -f $SYSTEM_DIR/mnt/system/usr/lib/libsns_gc4653.so*
rm -f $SYSTEM_DIR/mnt/system/usr/lib/libmipi_tx*
rm -rf $SYSTEM_DIR/mnt/system/usr/lib/libffi*
rm -rf $SYSTEM_DIR/mnt/system/usr/lib/*.a
rm -rf $SYSTEM_DIR/mnt/system/usr/lib/libtinyalsa.so
rm -f $SYSTEM_DIR/mnt/system/usr/lib/libcviai_evaluation*

rm -f $SYSTEM_DIR/mnt/system/lib/3rd/libnanomsg.so*
rm -f $SYSTEM_DIR/mnt/system/lib/3rd/libmp3lame.so*
rm -f $SYSTEM_DIR/mnt/system/lib/3rd/libopencv*
#rm -f $SYSTEM_DIR/mnt/system/lib/3rd/libmad.so.0*
rm -f $SYSTEM_DIR/mnt/system/lib/libopencv*
# rm -f $SYSTEM_DIR/mnt/system/lib/libcvi_rtsp.so
#rm -f $SYSTEM_DIR/mnt/system/lib/libcvikernel.so
rm -f $SYSTEM_DIR/mnt/system/lib/*.a
rm -f $SYSTEM_DIR/mnt/system/lib/libgst*
rm -f $SYSTEM_DIR/mnt/system/lib/libg*
rm -f $SYSTEM_DIR/mnt/system/lib/gstreamer-1.0/libgst*
rm -f $SYSTEM_DIR/mnt/system/lib/libraw_replay.so*
rm -rf $SYSTEM_DIR/mnt/system/lib/gio
rm -rf $SYSTEM_DIR/mnt/system/lib/glib*
rm -rf $SYSTEM_DIR/mnt/system/lib/gstreamer-1.0*
rm -rf $SYSTEM_DIR/mnt/system/usr/libexec*
rm -rf $SYSTEM_DIR/mnt/system/usr/bin
rm -rf $SYSTEM_DIR/usr/share/alsa
rm -f $SYSTEM_DIR/mnt/system/lib/libcvi_RES.so
rm -f $SYSTEM_DIR/mnt/system/lib/libcvi_ssp2.so
#rm -f $SYSTEM_DIR/mnt/system/lib/libcipher.so
rm -f $SYSTEM_DIR/mnt/system/lib/libinih.so*
rm -f $SYSTEM_DIR/mnt/system/lib/libINIReader.so*
rm -f $SYSTEM_DIR/mnt/system/lib/libanl*
rm -f $SYSTEM_DIR/mnt/system/lib/libjpeg.so*
rm -f $SYSTEM_DIR/mnt/system/lib/libsqlite3*
rm -f $SYSTEM_DIR/mnt/system/lib/libavcodec.so*
rm -f $SYSTEM_DIR/mnt/system/lib/libavformat.so*
rm -f $SYSTEM_DIR/mnt/system/lib/libavutil.so*
rm -f $SYSTEM_DIR/mnt/system/lib/libnsl*
rm -f $SYSTEM_DIR/mnt/system/lib/libnanomsg.so*
rm -f $SYSTEM_DIR/mnt/system/lib/libmp3lame.so*
#rm -f $SYSTEM_DIR/mnt/system/lib/libboost_system.so*
#rm -f $SYSTEM_DIR/mnt/system/lib/libcvi_ispd.so*
rm -f $SYSTEM_DIR/mnt/system/lib/libsns_gc4653.so*
rm -f $SYSTEM_DIR/mnt/system/lib/libsns_f23.so*
rm -f $SYSTEM_DIR/mnt/system/lib/libsns_f25.so*
rm -f $SYSTEM_DIR/mnt/system/lib/libsns_f35.so*
rm -f $SYSTEM_DIR/mnt/system/lib/libsns_gc2053_1l.so*
rm -f $SYSTEM_DIR/mnt/system/lib/libsns_gc2093.so*
rm -f $SYSTEM_DIR/mnt/system/lib/libsns_os08a20.so*
rm -f $SYSTEM_DIR/mnt/system/lib/libsns_imx3*.so*
rm -f $SYSTEM_DIR/mnt/system/lib/libsns_n5.so*
rm -f $SYSTEM_DIR/mnt/system/lib/libsns_n6.so*
rm -f $SYSTEM_DIR/mnt/system/lib/libsns_sc*.so*
rm -f $SYSTEM_DIR/mnt/system/lib/libcviai_evaluation*
rm -f $SYSTEM_DIR/mnt/system/lib/libcvi_ivs_tpu*
rm -f $SYSTEM_DIR/mnt/system/lib/libcvi_mp3enc.so*
rm -f $SYSTEM_DIR/mnt/system/lib/3rd/libnanomsg*
rm -rf $SYSTEM_DIR/mnt/system/lib/libffi*
rm -rf $SYSTEM_DIR/mnt/system/lib/cmake*
rm -f $SYSTEM_DIR/mnt/system/lib/libmipi_tx*
#rm -rf $SYSTEM_DIR/mnt/system/lib/libcvitracer.so


rm -f $SYSTEM_DIR/mnt/system/ko/cvi_mipi_tx*
rm -f $SYSTEM_DIR/mnt/system/ko/ts_gslX680*
rm -f $SYSTEM_DIR/mnt/system/ko/cvi_wiegand_gpio*
rm -f $SYSTEM_DIR/mnt/system/ko/cvi_fb*
rm -f $SYSTEM_DIR/mnt/system/ko/cfbcopyarea*
rm -f $SYSTEM_DIR/mnt/system/ko/cfbfillrect*
rm -f $SYSTEM_DIR/mnt/system/ko/cfbimgblt*
rm -f $SYSTEM_DIR/mnt/system/ko/cvi_wiegand*
rm -f $SYSTEM_DIR/mnt/system/ko/3rd/cvi_wiegand_gpio*
rm -f $SYSTEM_DIR/mnt/system/ko/3rd/ts_gslX680*
rm -f $SYSTEM_DIR/mnt/system/ko/3rd/bcm*
rm -f $SYSTEM_DIR/mnt/system/ko/3rd/fw_bcm*
rm -f $SYSTEM_DIR/mnt/system/ko/3rd/clm*
rm -f $SYSTEM_DIR/mnt/system/ko/3rd/nvram*
rm -f $SYSTEM_DIR/mnt/system/ko/3rd/config*
#rm -f $SYSTEM_DIR/mnt/system/ko/cv182x_wdt.ko
rm -f $SYSTEM_DIR/mnt/system/ko/cv182x_mon.ko
rm -f $SYSTEM_DIR/mnt/system/ko/cv183x_rtc.ko
#rm -f $SYSTEM_DIR/mnt/system/ko/configfs.ko
rm -f $SYSTEM_DIR/mnt/system/ko/cvi_usb_f_cvg.ko
#rm -f $SYSTEM_DIR/mnt/system/ko/cv182x_saradc.ko
rm -f $SYSTEM_DIR/mnt/system/ko/cv182x_pwm.ko
rm -f $SYSTEM_DIR/mnt/system/ko/ts_gslX680*
rm -f $SYSTEM_DIR/mnt/system/ko/cvi_wiegand_gpio*

rm -rf $SYSTEM_DIR/arm64*
rm -rf $SYSTEM_DIR/mnt/system/usr/libexec*
rm -rf $SYSTEM_DIR/mnt/system/usr/bin
rm -rf $SYSTEM_DIR/usr/share/alsa
rm -rf $SYSTEM_DIR/usr/www/
#rm -rf $SYSTEM_DIR/usr/bin/cvi_pinmux*
#rm -rf $SYSTEM_DIR/usr/bin/i2c_read*
#rm -rf $SYSTEM_DIR/usr/bin/i2c_write*
#rm -rf $SYSTEM_DIR/usr/bin/scp*
rm -rf $SYSTEM_DIR/usr/bin/fscryptctl*
#rm -rf $SYSTEM_DIR/usr/bin/ldd*
rm -rf $SYSTEM_DIR/usr/local/sshd_config*

rm -rf $SYSTEM_DIR/lib/*.a

if [ $SDK_VER != "uclibc" ]
then
    rm -f $SYSTEM_DIR/mnt/system/data/install/lib/libcvi_protobuf.so*
    rm -f $SYSTEM_DIR/mnt/system/data/install/lib/libprotobuf-lite.so*
    #glibc ramdisk(rootfs/common_arm/usr/lib/) has libz.so*
    rm -f $SYSTEM_DIR/mnt/system/lib/libz*
    #glibc ramdisk(rootfs/common_arm/usr/lib/) has libcrypto.so and libssl.so
    rm -f $SYSTEM_DIR/mnt/system/data/install/lib/libcrypto.so*
    rm -f $SYSTEM_DIR/mnt/system/data/install/lib/libssl.so*
    rm -f $SYSTEM_DIR/mnt/system/lib/libssl*
    rm -f $SYSTEM_DIR/mnt/system/lib/libcrypto*
else
    #save /mnt/system/lib/ openssl lib; need by ntpdate/wpa_supplicant
    #del /mnt/system/data/install/lib/ openssl lib;
    rm -f $SYSTEM_DIR/mnt/system/data/install/lib/libssl*
    rm -f $SYSTEM_DIR/mnt/system/data/install/lib/libcrypto*
		if [ $STORAGE_TYPE != "spinand" ]
		then
    #del unuse mtd-utils
	    rm -f $SYSTEM_DIR/usr/sbin/{ubi*,ftl_*,doc*,nand*}
	    rm -f $SYSTEM_DIR/usr/sbin/{flash_otp*,flash_*lock,flashcp}
	    rm -f $SYSTEM_DIR/usr/sbin/{rfd*,recv_image,serve_image,nftl*,mkfs*}
	    rm -f $SYSTEM_DIR/usr/sbin/{mtdpart,lsmtd}
    fi
fi

rm -rf $SYSTEM_DIR/usr/lib/rsyslog

du -sh $SYSTEM_DIR/* |sort -rh
du -sh $SYSTEM_DIR/mnt/* |sort -rh
du -sh $SYSTEM_DIR/mnt/system/* |sort -rh
du -sh $SYSTEM_DIR/mnt/system/lib/*  |sort -rh
du -sh $SYSTEM_DIR/mnt/system/data/install/* |sort -rh
du -sh $SYSTEM_DIR/usr/* |sort -rh


