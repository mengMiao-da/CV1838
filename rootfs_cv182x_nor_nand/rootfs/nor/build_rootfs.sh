rm ./rootfs.bin
mksquashfs rootfs ./rootfs.bin -b 64K -comp xz
