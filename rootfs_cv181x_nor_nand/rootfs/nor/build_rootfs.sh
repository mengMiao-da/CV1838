rm ./rootfs.bin
mksquashfs rootfs ./rootfs.bin -root-owned -comp xz
