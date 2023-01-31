	.arch armv8-a
	.file	"asm-offsets.c"
// GNU C11 (Linaro GCC 6.3-2017.05) version 6.3.1 20170404 (aarch64-linux-gnu)
//	compiled by GNU C version 4.8.4, GMP version 6.1.0, MPFR version 3.1.4, MPC version 1.0.3, isl version none
// GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
// 传递的选项：  -nostdinc -I include
// -I /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include
// -I /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/arch/arm/include
// -I /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/lib/mbedtls-2.13.0/include
// -I /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/.
// -I . -imultiarch aarch64-linux-gnu
// -iprefix /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/host-tools/gcc/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin/../lib/gcc/aarch64-linux-gnu/6.3.1/
// -isysroot /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/host-tools/gcc/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin/../aarch64-linux-gnu/libc
// -D __KERNEL__ -D __UBOOT__ -D CVICHIP=cv1838
// -D CVIBOARD=wevb_0002a_spinand -D CV1838_WEVB_0002A_SPINAND
// -D MIPI_PANEL_HX8394 -D MIPI_PANEL_4_LANES -D BOOTLOGO_ISP_RESET
// -D CONFIG_NAND_SUPPORT -D SPINAND_SQSH -D __ARM__
// -D __LINUX_ARM_ARCH__=8 -D DO_DEPS_ONLY -D KBUILD_STR(s)=#s
// -D KBUILD_BASENAME=KBUILD_STR(asm_offsets)
// -D KBUILD_MODNAME=KBUILD_STR(asm_offsets)
// -isystem /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/host-tools/gcc/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin/../lib/gcc/aarch64-linux-gnu/6.3.1/include
// -include /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/linux/kconfig.h
// -MD arch/arm/lib/.asm-offsets.s.d
// /home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/arch/arm/lib/asm-offsets.c
// -mstrict-align -march=armv8-a -mlittle-endian -mabi=lp64
// -auxbase-strip arch/arm/lib/asm-offsets.s -g -Os -Wall
// -Wstrict-prototypes -Wno-unused-value -Wno-unused-but-set-variable
// -Wno-format-security -Wno-format-nonliteral -Werror=date-time
// -fno-builtin -ffreestanding -fno-stack-protector
// -fno-delete-null-pointer-checks -fstack-usage -fno-pic
// -ffunction-sections -fdata-sections -ffixed-r9 -fno-common -ffixed-x18
// -fverbose-asm
// 启用的选项：  -faggressive-loop-optimizations -falign-functions
// -falign-jumps -falign-labels -falign-loops -fauto-inc-dec
// -fbranch-count-reg -fcaller-saves -fchkp-check-incomplete-type
// -fchkp-check-read -fchkp-check-write -fchkp-instrument-calls
// -fchkp-narrow-bounds -fchkp-optimize -fchkp-store-bounds
// -fchkp-use-static-bounds -fchkp-use-static-const-bounds
// -fchkp-use-wrappers -fcombine-stack-adjustments -fcompare-elim
// -fcprop-registers -fcrossjumping -fcse-follow-jumps -fdata-sections
// -fdefer-pop -fdevirtualize -fdevirtualize-speculatively -fdwarf2-cfi-asm
// -fearly-inlining -feliminate-unused-debug-types
// -fexpensive-optimizations -fforward-propagate -ffunction-cse
// -ffunction-sections -fgcse -fgcse-lm -fgnu-runtime -fgnu-unique
// -fguess-branch-probability -fhoist-adjacent-loads -fident
// -fif-conversion -fif-conversion2 -findirect-inlining -finline
// -finline-atomics -finline-functions -finline-functions-called-once
// -finline-small-functions -fipa-cp -fipa-cp-alignment -fipa-icf
// -fipa-icf-functions -fipa-icf-variables -fipa-profile -fipa-pure-const
// -fipa-ra -fipa-reference -fipa-sra -fira-hoist-pressure
// -fira-share-save-slots -fira-share-spill-slots
// -fisolate-erroneous-paths-dereference -fivopts -fkeep-static-consts
// -fleading-underscore -flifetime-dse -flra-remat -flto-odr-type-merging
// -fmath-errno -fmerge-constants -fmerge-debug-strings
// -fmove-loop-invariants -fomit-frame-pointer -foptimize-sibling-calls
// -fpartial-inlining -fpeephole -fpeephole2 -fplt -fprefetch-loop-arrays
// -free -freg-struct-return -freorder-blocks -freorder-functions
// -frerun-cse-after-loop -fsched-critical-path-heuristic
// -fsched-dep-count-heuristic -fsched-group-heuristic -fsched-interblock
// -fsched-last-insn-heuristic -fsched-pressure -fsched-rank-heuristic
// -fsched-spec -fsched-spec-insn-heuristic -fsched-stalled-insns-dep
// -fschedule-fusion -fschedule-insns2 -fsection-anchors
// -fsemantic-interposition -fshow-column -fshrink-wrap -fsigned-zeros
// -fsplit-ivs-in-unroller -fsplit-wide-types -fssa-backprop -fssa-phiopt
// -fstdarg-opt -fstrict-aliasing -fstrict-overflow
// -fstrict-volatile-bitfields -fsync-libcalls -fthread-jumps
// -ftoplevel-reorder -ftrapping-math -ftree-bit-ccp
// -ftree-builtin-call-dce -ftree-ccp -ftree-ch -ftree-coalesce-vars
// -ftree-copy-prop -ftree-cselim -ftree-dce -ftree-dominator-opts
// -ftree-dse -ftree-forwprop -ftree-fre -ftree-loop-if-convert
// -ftree-loop-im -ftree-loop-ivcanon -ftree-loop-optimize
// -ftree-parallelize-loops= -ftree-phiprop -ftree-pre -ftree-pta
// -ftree-reassoc -ftree-scev-cprop -ftree-sink -ftree-slsr -ftree-sra
// -ftree-switch-conversion -ftree-tail-merge -ftree-ter -ftree-vrp
// -funit-at-a-time -fvar-tracking -fvar-tracking-assignments -fverbose-asm
// -fzero-initialized-in-bss -mfix-cortex-a53-835769
// -mfix-cortex-a53-843419 -mglibc -mlittle-endian
// -momit-leaf-frame-pointer -mpc-relative-literal-loads -mstrict-align

	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.section	.text.startup.main,"ax",@progbits
	.align	2
	.global	main
	.type	main, %function
main:
.LFB196:
	.file 1 "/home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/arch/arm/lib/asm-offsets.c"
	.loc 1 25 0
	.cfi_startproc
	.loc 1 202 0
#APP
// 202 "/home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/arch/arm/lib/asm-offsets.c" 1
	
.ascii "->ARM_SMCCC_RES_X0_OFFS 0 offsetof(struct arm_smccc_res, a0)"	//
// 0 "" 2
	.loc 1 203 0
// 203 "/home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/arch/arm/lib/asm-offsets.c" 1
	
.ascii "->ARM_SMCCC_RES_X2_OFFS 16 offsetof(struct arm_smccc_res, a2)"	//
// 0 "" 2
	.loc 1 204 0
// 204 "/home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/arch/arm/lib/asm-offsets.c" 1
	
.ascii "->ARM_SMCCC_QUIRK_ID_OFFS 0 offsetof(struct arm_smccc_quirk, id)"	//
// 0 "" 2
	.loc 1 205 0
// 205 "/home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/arch/arm/lib/asm-offsets.c" 1
	
.ascii "->ARM_SMCCC_QUIRK_STATE_OFFS 8 offsetof(struct arm_smccc_quirk, state)"	//
// 0 "" 2
	.loc 1 208 0
#NO_APP
	mov	w0, 0	//,
	ret
	.cfi_endproc
.LFE196:
	.size	main, .-main
	.text
.Letext0:
	.file 2 "/home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/common.h"
	.file 3 "/home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/arch/arm/include/asm/types.h"
	.file 4 "/home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/linux/types.h"
	.file 5 "/home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/errno.h"
	.file 6 "/home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/linux/string.h"
	.file 7 "/home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/ide.h"
	.file 8 "/home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/part.h"
	.file 9 "/home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/efi.h"
	.file 10 "/home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/flash.h"
	.file 11 "/home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/lmb.h"
	.file 12 "/home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/asm-generic/u-boot.h"
	.file 13 "/home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/arch/arm/include/asm/u-boot-arm.h"
	.file 14 "/home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/../lib/libfdt/fdt.h"
	.file 15 "/home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/libfdt_env.h"
	.file 16 "/home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/image.h"
	.file 17 "/home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/u-boot/sha1.h"
	.file 18 "/home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/u-boot/sha256.h"
	.file 19 "/home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/net.h"
	.file 20 "/home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/include/environment.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0xb28
	.2byte	0x4
	.4byte	.Ldebug_abbrev0
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF181
	.byte	0xc
	.4byte	.LASF182
	.4byte	.LASF183
	.4byte	.Ldebug_ranges0+0
	.8byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.4byte	.LASF4
	.byte	0x2
	.byte	0xd
	.4byte	0x34
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.4byte	.LASF0
	.uleb128 0x4
	.4byte	0x34
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.4byte	.LASF1
	.uleb128 0x3
	.byte	0x2
	.byte	0x7
	.4byte	.LASF2
	.uleb128 0x5
	.4byte	.LASF21
	.byte	0x5
	.byte	0xc
	.4byte	0x59
	.uleb128 0x6
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.4byte	.LASF3
	.uleb128 0x2
	.4byte	.LASF5
	.byte	0x3
	.byte	0xc
	.4byte	0x34
	.uleb128 0x3
	.byte	0x2
	.byte	0x5
	.4byte	.LASF6
	.uleb128 0x2
	.4byte	.LASF7
	.byte	0x3
	.byte	0x12
	.4byte	0x84
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.4byte	.LASF8
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.4byte	.LASF9
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.4byte	.LASF10
	.uleb128 0x7
	.string	"u8"
	.byte	0x3
	.byte	0x1f
	.4byte	0x34
	.uleb128 0x4
	.4byte	0x99
	.uleb128 0x7
	.string	"u32"
	.byte	0x3
	.byte	0x25
	.4byte	0x84
	.uleb128 0x2
	.4byte	.LASF11
	.byte	0x3
	.byte	0x31
	.4byte	0x92
	.uleb128 0x2
	.4byte	.LASF12
	.byte	0x3
	.byte	0x32
	.4byte	0x92
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.4byte	.LASF13
	.uleb128 0x8
	.byte	0x8
	.4byte	0xdd
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.4byte	.LASF14
	.uleb128 0x4
	.4byte	0xd6
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.4byte	.LASF15
	.uleb128 0x8
	.byte	0x8
	.4byte	0xd6
	.uleb128 0x2
	.4byte	.LASF16
	.byte	0x4
	.byte	0x57
	.4byte	0x47
	.uleb128 0x2
	.4byte	.LASF17
	.byte	0x4
	.byte	0x59
	.4byte	0x40
	.uleb128 0x2
	.4byte	.LASF18
	.byte	0x4
	.byte	0x67
	.4byte	0x67
	.uleb128 0x4
	.4byte	0x105
	.uleb128 0x2
	.4byte	.LASF19
	.byte	0x4
	.byte	0x69
	.4byte	0x79
	.uleb128 0x2
	.4byte	.LASF20
	.byte	0x4
	.byte	0x95
	.4byte	0x79
	.uleb128 0x5
	.4byte	.LASF22
	.byte	0x6
	.byte	0xb
	.4byte	0xe9
	.uleb128 0x9
	.byte	0x8
	.uleb128 0xa
	.4byte	0xfa
	.4byte	0x143
	.uleb128 0xb
	.byte	0
	.uleb128 0x5
	.4byte	.LASF23
	.byte	0x7
	.byte	0x10
	.4byte	0x138
	.uleb128 0xc
	.4byte	.LASF26
	.byte	0x10
	.byte	0x8
	.byte	0xd
	.4byte	0x173
	.uleb128 0xd
	.4byte	.LASF24
	.byte	0x8
	.byte	0xe
	.4byte	0xe9
	.byte	0
	.uleb128 0xd
	.4byte	.LASF25
	.byte	0x8
	.byte	0xf
	.4byte	0x18c
	.byte	0x8
	.byte	0
	.uleb128 0x4
	.4byte	0x14e
	.uleb128 0xe
	.4byte	0x59
	.4byte	0x18c
	.uleb128 0xf
	.4byte	0x59
	.uleb128 0xf
	.4byte	0x59
	.byte	0
	.uleb128 0x8
	.byte	0x8
	.4byte	0x178
	.uleb128 0xa
	.4byte	0x173
	.4byte	0x19d
	.uleb128 0xb
	.byte	0
	.uleb128 0x4
	.4byte	0x192
	.uleb128 0x5
	.4byte	.LASF26
	.byte	0x8
	.byte	0xba
	.4byte	0x19d
	.uleb128 0x3
	.byte	0x1
	.byte	0x2
	.4byte	.LASF27
	.uleb128 0xa
	.4byte	0xd6
	.4byte	0x1bf
	.uleb128 0xb
	.byte	0
	.uleb128 0x10
	.4byte	.LASF28
	.byte	0x9
	.2byte	0x124
	.4byte	0x1b4
	.uleb128 0x10
	.4byte	.LASF29
	.byte	0x9
	.2byte	0x127
	.4byte	0x1b4
	.uleb128 0x10
	.4byte	.LASF30
	.byte	0x9
	.2byte	0x127
	.4byte	0x1b4
	.uleb128 0x11
	.2byte	0x1218
	.byte	0xa
	.byte	0x13
	.4byte	0x22a
	.uleb128 0xd
	.4byte	.LASF31
	.byte	0xa
	.byte	0x14
	.4byte	0xfa
	.byte	0
	.uleb128 0xd
	.4byte	.LASF32
	.byte	0xa
	.byte	0x15
	.4byte	0xef
	.byte	0x8
	.uleb128 0xd
	.4byte	.LASF33
	.byte	0xa
	.byte	0x16
	.4byte	0xfa
	.byte	0x10
	.uleb128 0xd
	.4byte	.LASF34
	.byte	0xa
	.byte	0x17
	.4byte	0x22a
	.byte	0x18
	.uleb128 0x12
	.4byte	.LASF35
	.byte	0xa
	.byte	0x18
	.4byte	0x23b
	.2byte	0x1018
	.byte	0
	.uleb128 0xa
	.4byte	0xfa
	.4byte	0x23b
	.uleb128 0x13
	.4byte	0xc9
	.2byte	0x1ff
	.byte	0
	.uleb128 0xa
	.4byte	0x29
	.4byte	0x24c
	.uleb128 0x13
	.4byte	0xc9
	.2byte	0x1ff
	.byte	0
	.uleb128 0x2
	.4byte	.LASF36
	.byte	0xa
	.byte	0x32
	.4byte	0x1e3
	.uleb128 0xa
	.4byte	0x24c
	.4byte	0x262
	.uleb128 0xb
	.byte	0
	.uleb128 0x5
	.4byte	.LASF37
	.byte	0xa
	.byte	0x34
	.4byte	0x257
	.uleb128 0x3
	.byte	0x10
	.byte	0x4
	.4byte	.LASF38
	.uleb128 0xc
	.4byte	.LASF39
	.byte	0x10
	.byte	0xb
	.byte	0x10
	.4byte	0x299
	.uleb128 0xd
	.4byte	.LASF40
	.byte	0xb
	.byte	0x11
	.4byte	0xb3
	.byte	0
	.uleb128 0xd
	.4byte	.LASF31
	.byte	0xb
	.byte	0x12
	.4byte	0xbe
	.byte	0x8
	.byte	0
	.uleb128 0xc
	.4byte	.LASF41
	.byte	0xa0
	.byte	0xb
	.byte	0x15
	.4byte	0x2ca
	.uleb128 0x14
	.string	"cnt"
	.byte	0xb
	.byte	0x16
	.4byte	0x40
	.byte	0
	.uleb128 0xd
	.4byte	.LASF31
	.byte	0xb
	.byte	0x17
	.4byte	0xbe
	.byte	0x8
	.uleb128 0xd
	.4byte	.LASF42
	.byte	0xb
	.byte	0x18
	.4byte	0x2ca
	.byte	0x10
	.byte	0
	.uleb128 0xa
	.4byte	0x274
	.4byte	0x2da
	.uleb128 0x15
	.4byte	0xc9
	.byte	0x8
	.byte	0
	.uleb128 0x16
	.string	"lmb"
	.2byte	0x140
	.byte	0xb
	.byte	0x1b
	.4byte	0x300
	.uleb128 0xd
	.4byte	.LASF43
	.byte	0xb
	.byte	0x1c
	.4byte	0x299
	.byte	0
	.uleb128 0xd
	.4byte	.LASF44
	.byte	0xb
	.byte	0x1d
	.4byte	0x299
	.byte	0xa0
	.byte	0
	.uleb128 0x17
	.string	"lmb"
	.byte	0xb
	.byte	0x20
	.4byte	0x2da
	.uleb128 0x18
	.byte	0x10
	.byte	0xc
	.byte	0x5a
	.4byte	0x32c
	.uleb128 0xd
	.4byte	.LASF34
	.byte	0xc
	.byte	0x5b
	.4byte	0xb3
	.byte	0
	.uleb128 0xd
	.4byte	.LASF31
	.byte	0xc
	.byte	0x5c
	.4byte	0xbe
	.byte	0x8
	.byte	0
	.uleb128 0xc
	.4byte	.LASF45
	.byte	0x98
	.byte	0xc
	.byte	0x1b
	.4byte	0x41d
	.uleb128 0xd
	.4byte	.LASF46
	.byte	0xc
	.byte	0x1c
	.4byte	0x40
	.byte	0
	.uleb128 0xd
	.4byte	.LASF47
	.byte	0xc
	.byte	0x1d
	.4byte	0xbe
	.byte	0x8
	.uleb128 0xd
	.4byte	.LASF48
	.byte	0xc
	.byte	0x1e
	.4byte	0x40
	.byte	0x10
	.uleb128 0xd
	.4byte	.LASF49
	.byte	0xc
	.byte	0x1f
	.4byte	0x40
	.byte	0x18
	.uleb128 0xd
	.4byte	.LASF50
	.byte	0xc
	.byte	0x20
	.4byte	0x40
	.byte	0x20
	.uleb128 0xd
	.4byte	.LASF51
	.byte	0xc
	.byte	0x21
	.4byte	0x40
	.byte	0x28
	.uleb128 0xd
	.4byte	.LASF52
	.byte	0xc
	.byte	0x22
	.4byte	0x40
	.byte	0x30
	.uleb128 0xd
	.4byte	.LASF53
	.byte	0xc
	.byte	0x24
	.4byte	0x40
	.byte	0x38
	.uleb128 0xd
	.4byte	.LASF54
	.byte	0xc
	.byte	0x25
	.4byte	0x40
	.byte	0x40
	.uleb128 0xd
	.4byte	.LASF55
	.byte	0xc
	.byte	0x26
	.4byte	0x40
	.byte	0x48
	.uleb128 0xd
	.4byte	.LASF56
	.byte	0xc
	.byte	0x31
	.4byte	0x40
	.byte	0x50
	.uleb128 0xd
	.4byte	.LASF57
	.byte	0xc
	.byte	0x32
	.4byte	0x40
	.byte	0x58
	.uleb128 0xd
	.4byte	.LASF58
	.byte	0xc
	.byte	0x33
	.4byte	0x41d
	.byte	0x60
	.uleb128 0xd
	.4byte	.LASF59
	.byte	0xc
	.byte	0x34
	.4byte	0x47
	.byte	0x66
	.uleb128 0xd
	.4byte	.LASF60
	.byte	0xc
	.byte	0x35
	.4byte	0x40
	.byte	0x68
	.uleb128 0xd
	.4byte	.LASF61
	.byte	0xc
	.byte	0x36
	.4byte	0x40
	.byte	0x70
	.uleb128 0xd
	.4byte	.LASF62
	.byte	0xc
	.byte	0x57
	.4byte	0xfa
	.byte	0x78
	.uleb128 0xd
	.4byte	.LASF63
	.byte	0xc
	.byte	0x58
	.4byte	0xfa
	.byte	0x80
	.uleb128 0xd
	.4byte	.LASF64
	.byte	0xc
	.byte	0x5d
	.4byte	0x42d
	.byte	0x88
	.byte	0
	.uleb128 0xa
	.4byte	0x34
	.4byte	0x42d
	.uleb128 0x15
	.4byte	0xc9
	.byte	0x5
	.byte	0
	.uleb128 0xa
	.4byte	0x30b
	.4byte	0x43d
	.uleb128 0x15
	.4byte	0xc9
	.byte	0
	.byte	0
	.uleb128 0x2
	.4byte	.LASF65
	.byte	0xc
	.byte	0x5f
	.4byte	0x32c
	.uleb128 0x5
	.4byte	.LASF66
	.byte	0xd
	.byte	0x13
	.4byte	0xfa
	.uleb128 0x5
	.4byte	.LASF67
	.byte	0xd
	.byte	0x14
	.4byte	0xfa
	.uleb128 0x5
	.4byte	.LASF68
	.byte	0xd
	.byte	0x15
	.4byte	0xfa
	.uleb128 0x5
	.4byte	.LASF69
	.byte	0xd
	.byte	0x16
	.4byte	0xfa
	.uleb128 0x5
	.4byte	.LASF70
	.byte	0xd
	.byte	0x17
	.4byte	0xfa
	.uleb128 0x5
	.4byte	.LASF71
	.byte	0xd
	.byte	0x18
	.4byte	0xfa
	.uleb128 0x5
	.4byte	.LASF72
	.byte	0xd
	.byte	0x19
	.4byte	0xfa
	.uleb128 0xc
	.4byte	.LASF73
	.byte	0x28
	.byte	0xe
	.byte	0xd
	.4byte	0x51a
	.uleb128 0xd
	.4byte	.LASF74
	.byte	0xe
	.byte	0xe
	.4byte	0x52b
	.byte	0
	.uleb128 0xd
	.4byte	.LASF75
	.byte	0xe
	.byte	0xf
	.4byte	0x52b
	.byte	0x4
	.uleb128 0xd
	.4byte	.LASF76
	.byte	0xe
	.byte	0x10
	.4byte	0x52b
	.byte	0x8
	.uleb128 0xd
	.4byte	.LASF77
	.byte	0xe
	.byte	0x11
	.4byte	0x52b
	.byte	0xc
	.uleb128 0xd
	.4byte	.LASF78
	.byte	0xe
	.byte	0x12
	.4byte	0x52b
	.byte	0x10
	.uleb128 0xd
	.4byte	.LASF79
	.byte	0xe
	.byte	0x13
	.4byte	0x52b
	.byte	0x14
	.uleb128 0xd
	.4byte	.LASF80
	.byte	0xe
	.byte	0x14
	.4byte	0x52b
	.byte	0x18
	.uleb128 0xd
	.4byte	.LASF81
	.byte	0xe
	.byte	0x17
	.4byte	0x52b
	.byte	0x1c
	.uleb128 0xd
	.4byte	.LASF82
	.byte	0xe
	.byte	0x1a
	.4byte	0x52b
	.byte	0x20
	.uleb128 0xd
	.4byte	.LASF83
	.byte	0xe
	.byte	0x1d
	.4byte	0x52b
	.byte	0x24
	.byte	0
	.uleb128 0x5
	.4byte	.LASF84
	.byte	0xf
	.byte	0xf
	.4byte	0x525
	.uleb128 0x8
	.byte	0x8
	.4byte	0x495
	.uleb128 0x2
	.4byte	.LASF85
	.byte	0xf
	.byte	0x12
	.4byte	0x120
	.uleb128 0x19
	.4byte	.LASF86
	.byte	0x40
	.byte	0x10
	.2byte	0x12f
	.4byte	0x5e0
	.uleb128 0x1a
	.4byte	.LASF87
	.byte	0x10
	.2byte	0x130
	.4byte	0x120
	.byte	0
	.uleb128 0x1a
	.4byte	.LASF88
	.byte	0x10
	.2byte	0x131
	.4byte	0x120
	.byte	0x4
	.uleb128 0x1a
	.4byte	.LASF89
	.byte	0x10
	.2byte	0x132
	.4byte	0x120
	.byte	0x8
	.uleb128 0x1a
	.4byte	.LASF90
	.byte	0x10
	.2byte	0x133
	.4byte	0x120
	.byte	0xc
	.uleb128 0x1a
	.4byte	.LASF91
	.byte	0x10
	.2byte	0x134
	.4byte	0x120
	.byte	0x10
	.uleb128 0x1a
	.4byte	.LASF92
	.byte	0x10
	.2byte	0x135
	.4byte	0x120
	.byte	0x14
	.uleb128 0x1a
	.4byte	.LASF93
	.byte	0x10
	.2byte	0x136
	.4byte	0x120
	.byte	0x18
	.uleb128 0x1a
	.4byte	.LASF94
	.byte	0x10
	.2byte	0x137
	.4byte	0x105
	.byte	0x1c
	.uleb128 0x1a
	.4byte	.LASF95
	.byte	0x10
	.2byte	0x138
	.4byte	0x105
	.byte	0x1d
	.uleb128 0x1a
	.4byte	.LASF96
	.byte	0x10
	.2byte	0x139
	.4byte	0x105
	.byte	0x1e
	.uleb128 0x1a
	.4byte	.LASF97
	.byte	0x10
	.2byte	0x13a
	.4byte	0x105
	.byte	0x1f
	.uleb128 0x1a
	.4byte	.LASF98
	.byte	0x10
	.2byte	0x13b
	.4byte	0x5e0
	.byte	0x20
	.byte	0
	.uleb128 0xa
	.4byte	0x105
	.4byte	0x5f0
	.uleb128 0x15
	.4byte	0xc9
	.byte	0x1f
	.byte	0
	.uleb128 0x1b
	.4byte	.LASF99
	.byte	0x10
	.2byte	0x13c
	.4byte	0x536
	.uleb128 0x19
	.4byte	.LASF100
	.byte	0x30
	.byte	0x10
	.2byte	0x13e
	.4byte	0x67e
	.uleb128 0x1a
	.4byte	.LASF34
	.byte	0x10
	.2byte	0x13f
	.4byte	0xfa
	.byte	0
	.uleb128 0x1c
	.string	"end"
	.byte	0x10
	.2byte	0x13f
	.4byte	0xfa
	.byte	0x8
	.uleb128 0x1a
	.4byte	.LASF101
	.byte	0x10
	.2byte	0x140
	.4byte	0xfa
	.byte	0x10
	.uleb128 0x1a
	.4byte	.LASF102
	.byte	0x10
	.2byte	0x140
	.4byte	0xfa
	.byte	0x18
	.uleb128 0x1a
	.4byte	.LASF103
	.byte	0x10
	.2byte	0x141
	.4byte	0xfa
	.byte	0x20
	.uleb128 0x1a
	.4byte	.LASF104
	.byte	0x10
	.2byte	0x142
	.4byte	0x105
	.byte	0x28
	.uleb128 0x1a
	.4byte	.LASF105
	.byte	0x10
	.2byte	0x142
	.4byte	0x105
	.byte	0x29
	.uleb128 0x1c
	.string	"os"
	.byte	0x10
	.2byte	0x142
	.4byte	0x105
	.byte	0x2a
	.uleb128 0x1a
	.4byte	.LASF106
	.byte	0x10
	.2byte	0x143
	.4byte	0x105
	.byte	0x2b
	.byte	0
	.uleb128 0x1b
	.4byte	.LASF107
	.byte	0x10
	.2byte	0x144
	.4byte	0x5fc
	.uleb128 0x1d
	.4byte	.LASF108
	.2byte	0x280
	.byte	0x10
	.2byte	0x14a
	.4byte	0x827
	.uleb128 0x1a
	.4byte	.LASF109
	.byte	0x10
	.2byte	0x150
	.4byte	0x827
	.byte	0
	.uleb128 0x1a
	.4byte	.LASF110
	.byte	0x10
	.2byte	0x151
	.4byte	0x5f0
	.byte	0x8
	.uleb128 0x1a
	.4byte	.LASF111
	.byte	0x10
	.2byte	0x152
	.4byte	0xfa
	.byte	0x48
	.uleb128 0x1a
	.4byte	.LASF112
	.byte	0x10
	.2byte	0x155
	.4byte	0xd0
	.byte	0x50
	.uleb128 0x1a
	.4byte	.LASF113
	.byte	0x10
	.2byte	0x157
	.4byte	0x136
	.byte	0x58
	.uleb128 0x1a
	.4byte	.LASF114
	.byte	0x10
	.2byte	0x158
	.4byte	0xd0
	.byte	0x60
	.uleb128 0x1a
	.4byte	.LASF115
	.byte	0x10
	.2byte	0x159
	.4byte	0x59
	.byte	0x68
	.uleb128 0x1a
	.4byte	.LASF116
	.byte	0x10
	.2byte	0x15b
	.4byte	0x136
	.byte	0x70
	.uleb128 0x1a
	.4byte	.LASF117
	.byte	0x10
	.2byte	0x15c
	.4byte	0xd0
	.byte	0x78
	.uleb128 0x1a
	.4byte	.LASF118
	.byte	0x10
	.2byte	0x15d
	.4byte	0x59
	.byte	0x80
	.uleb128 0x1a
	.4byte	.LASF119
	.byte	0x10
	.2byte	0x15f
	.4byte	0x136
	.byte	0x88
	.uleb128 0x1a
	.4byte	.LASF120
	.byte	0x10
	.2byte	0x160
	.4byte	0xd0
	.byte	0x90
	.uleb128 0x1a
	.4byte	.LASF121
	.byte	0x10
	.2byte	0x161
	.4byte	0x59
	.byte	0x98
	.uleb128 0x1a
	.4byte	.LASF122
	.byte	0x10
	.2byte	0x163
	.4byte	0x136
	.byte	0xa0
	.uleb128 0x1a
	.4byte	.LASF123
	.byte	0x10
	.2byte	0x164
	.4byte	0xd0
	.byte	0xa8
	.uleb128 0x1a
	.4byte	.LASF124
	.byte	0x10
	.2byte	0x165
	.4byte	0x59
	.byte	0xb0
	.uleb128 0x1c
	.string	"os"
	.byte	0x10
	.2byte	0x169
	.4byte	0x67e
	.byte	0xb8
	.uleb128 0x1c
	.string	"ep"
	.byte	0x10
	.2byte	0x16a
	.4byte	0xfa
	.byte	0xe8
	.uleb128 0x1a
	.4byte	.LASF125
	.byte	0x10
	.2byte	0x16c
	.4byte	0xfa
	.byte	0xf0
	.uleb128 0x1a
	.4byte	.LASF126
	.byte	0x10
	.2byte	0x16c
	.4byte	0xfa
	.byte	0xf8
	.uleb128 0x1e
	.4byte	.LASF127
	.byte	0x10
	.2byte	0x16e
	.4byte	0xe9
	.2byte	0x100
	.uleb128 0x1e
	.4byte	.LASF128
	.byte	0x10
	.2byte	0x16f
	.4byte	0xfa
	.2byte	0x108
	.uleb128 0x1e
	.4byte	.LASF129
	.byte	0x10
	.2byte	0x171
	.4byte	0xfa
	.2byte	0x110
	.uleb128 0x1e
	.4byte	.LASF130
	.byte	0x10
	.2byte	0x172
	.4byte	0xfa
	.2byte	0x118
	.uleb128 0x1e
	.4byte	.LASF131
	.byte	0x10
	.2byte	0x173
	.4byte	0xfa
	.2byte	0x120
	.uleb128 0x1e
	.4byte	.LASF132
	.byte	0x10
	.2byte	0x174
	.4byte	0xfa
	.2byte	0x128
	.uleb128 0x1f
	.string	"kbd"
	.byte	0x10
	.2byte	0x175
	.4byte	0x82d
	.2byte	0x130
	.uleb128 0x1e
	.4byte	.LASF133
	.byte	0x10
	.2byte	0x178
	.4byte	0x59
	.2byte	0x138
	.uleb128 0x1e
	.4byte	.LASF134
	.byte	0x10
	.2byte	0x185
	.4byte	0x59
	.2byte	0x13c
	.uleb128 0x1f
	.string	"lmb"
	.byte	0x10
	.2byte	0x188
	.4byte	0x2da
	.2byte	0x140
	.byte	0
	.uleb128 0x8
	.byte	0x8
	.4byte	0x5f0
	.uleb128 0x8
	.byte	0x8
	.4byte	0x43d
	.uleb128 0x1b
	.4byte	.LASF135
	.byte	0x10
	.2byte	0x18a
	.4byte	0x68a
	.uleb128 0x10
	.4byte	.LASF136
	.byte	0x10
	.2byte	0x18c
	.4byte	0x833
	.uleb128 0xa
	.4byte	0x110
	.4byte	0x856
	.uleb128 0xb
	.byte	0
	.uleb128 0x4
	.4byte	0x84b
	.uleb128 0x5
	.4byte	.LASF137
	.byte	0x11
	.byte	0x1a
	.4byte	0x856
	.uleb128 0x5
	.4byte	.LASF138
	.byte	0x12
	.byte	0x7
	.4byte	0x856
	.uleb128 0xa
	.4byte	0xd6
	.4byte	0x881
	.uleb128 0x15
	.4byte	0xc9
	.byte	0x1f
	.byte	0
	.uleb128 0x5
	.4byte	.LASF139
	.byte	0x2
	.byte	0xd8
	.4byte	0xfa
	.uleb128 0xa
	.4byte	0x99
	.4byte	0x897
	.uleb128 0xb
	.byte	0
	.uleb128 0x5
	.4byte	.LASF140
	.byte	0x2
	.byte	0xda
	.4byte	0x88c
	.uleb128 0x10
	.4byte	.LASF141
	.byte	0x2
	.2byte	0x127
	.4byte	0xfa
	.uleb128 0x10
	.4byte	.LASF142
	.byte	0x2
	.2byte	0x128
	.4byte	0xfa
	.uleb128 0x10
	.4byte	.LASF143
	.byte	0x2
	.2byte	0x129
	.4byte	0xfa
	.uleb128 0xc
	.4byte	.LASF144
	.byte	0x4
	.byte	0x13
	.byte	0x2e
	.4byte	0x8df
	.uleb128 0xd
	.4byte	.LASF145
	.byte	0x13
	.byte	0x2f
	.4byte	0x120
	.byte	0
	.byte	0
	.uleb128 0x8
	.byte	0x8
	.4byte	0x29
	.uleb128 0xa
	.4byte	0x99
	.4byte	0x8f5
	.uleb128 0x15
	.4byte	0xc9
	.byte	0x5
	.byte	0
	.uleb128 0x10
	.4byte	.LASF146
	.byte	0x13
	.2byte	0x1fd
	.4byte	0x8c6
	.uleb128 0x10
	.4byte	.LASF147
	.byte	0x13
	.2byte	0x1fe
	.4byte	0x8c6
	.uleb128 0x10
	.4byte	.LASF148
	.byte	0x13
	.2byte	0x200
	.4byte	0x8c6
	.uleb128 0x10
	.4byte	.LASF149
	.byte	0x13
	.2byte	0x205
	.4byte	0x871
	.uleb128 0x10
	.4byte	.LASF150
	.byte	0x13
	.2byte	0x206
	.4byte	0x871
	.uleb128 0xa
	.4byte	0xd6
	.4byte	0x941
	.uleb128 0x15
	.4byte	0xc9
	.byte	0x3f
	.byte	0
	.uleb128 0x10
	.4byte	.LASF151
	.byte	0x13
	.2byte	0x207
	.4byte	0x931
	.uleb128 0x10
	.4byte	.LASF152
	.byte	0x13
	.2byte	0x209
	.4byte	0x8e5
	.uleb128 0x10
	.4byte	.LASF153
	.byte	0x13
	.2byte	0x20a
	.4byte	0x8e5
	.uleb128 0x10
	.4byte	.LASF154
	.byte	0x13
	.2byte	0x20b
	.4byte	0x8c6
	.uleb128 0x10
	.4byte	.LASF155
	.byte	0x13
	.2byte	0x20c
	.4byte	0x8c6
	.uleb128 0x10
	.4byte	.LASF156
	.byte	0x13
	.2byte	0x20d
	.4byte	0x8df
	.uleb128 0xa
	.4byte	0x8df
	.4byte	0x999
	.uleb128 0x15
	.4byte	0xc9
	.byte	0x3
	.byte	0
	.uleb128 0x10
	.4byte	.LASF157
	.byte	0x13
	.2byte	0x20e
	.4byte	0x989
	.uleb128 0x10
	.4byte	.LASF158
	.byte	0x13
	.2byte	0x20f
	.4byte	0x8df
	.uleb128 0x10
	.4byte	.LASF159
	.byte	0x13
	.2byte	0x210
	.4byte	0x59
	.uleb128 0xa
	.4byte	0xa3
	.4byte	0x9cd
	.uleb128 0x15
	.4byte	0xc9
	.byte	0x5
	.byte	0
	.uleb128 0x4
	.4byte	0x9bd
	.uleb128 0x10
	.4byte	.LASF160
	.byte	0x13
	.2byte	0x211
	.4byte	0x9cd
	.uleb128 0x10
	.4byte	.LASF161
	.byte	0x13
	.2byte	0x212
	.4byte	0x9cd
	.uleb128 0x10
	.4byte	.LASF162
	.byte	0x13
	.2byte	0x216
	.4byte	0xef
	.uleb128 0x10
	.4byte	.LASF163
	.byte	0x13
	.2byte	0x217
	.4byte	0xef
	.uleb128 0x10
	.4byte	.LASF164
	.byte	0x13
	.2byte	0x219
	.4byte	0x59
	.uleb128 0xa
	.4byte	0xd6
	.4byte	0xa1f
	.uleb128 0x13
	.4byte	0xc9
	.2byte	0x3ff
	.byte	0
	.uleb128 0x10
	.4byte	.LASF165
	.byte	0x13
	.2byte	0x220
	.4byte	0xa0e
	.uleb128 0x10
	.4byte	.LASF166
	.byte	0x13
	.2byte	0x222
	.4byte	0xa8
	.uleb128 0x10
	.4byte	.LASF167
	.byte	0x13
	.2byte	0x224
	.4byte	0xa8
	.uleb128 0x10
	.4byte	.LASF168
	.byte	0x13
	.2byte	0x22c
	.4byte	0x8c6
	.uleb128 0x20
	.4byte	.LASF184
	.byte	0x4
	.4byte	0x84
	.byte	0x13
	.2byte	0x282
	.4byte	0xa79
	.uleb128 0x21
	.4byte	.LASF169
	.byte	0
	.uleb128 0x21
	.4byte	.LASF170
	.byte	0x1
	.uleb128 0x21
	.4byte	.LASF171
	.byte	0x2
	.uleb128 0x21
	.4byte	.LASF172
	.byte	0x3
	.byte	0
	.uleb128 0x10
	.4byte	.LASF173
	.byte	0x13
	.2byte	0x288
	.4byte	0xa4f
	.uleb128 0x5
	.4byte	.LASF174
	.byte	0x14
	.byte	0x93
	.4byte	0xe9
	.uleb128 0x22
	.4byte	.LASF175
	.4byte	0x20000
	.byte	0x14
	.byte	0x9d
	.4byte	0xac4
	.uleb128 0x14
	.string	"crc"
	.byte	0x14
	.byte	0x9e
	.4byte	0x115
	.byte	0
	.uleb128 0xd
	.4byte	.LASF176
	.byte	0x14
	.byte	0xa0
	.4byte	0x34
	.byte	0x4
	.uleb128 0xd
	.4byte	.LASF177
	.byte	0x14
	.byte	0xa2
	.4byte	0xac4
	.byte	0x5
	.byte	0
	.uleb128 0xa
	.4byte	0x34
	.4byte	0xad7
	.uleb128 0x23
	.4byte	0xc9
	.4byte	0x1fffa
	.byte	0
	.uleb128 0x2
	.4byte	.LASF178
	.byte	0x14
	.byte	0xa3
	.4byte	0xa90
	.uleb128 0xa
	.4byte	0x3b
	.4byte	0xaed
	.uleb128 0xb
	.byte	0
	.uleb128 0x4
	.4byte	0xae2
	.uleb128 0x5
	.4byte	.LASF179
	.byte	0x14
	.byte	0xae
	.4byte	0xaed
	.uleb128 0x5
	.4byte	.LASF180
	.byte	0x14
	.byte	0xaf
	.4byte	0xb08
	.uleb128 0x8
	.byte	0x8
	.4byte	0xad7
	.uleb128 0x24
	.4byte	.LASF185
	.byte	0x1
	.byte	0x18
	.4byte	0x59
	.8byte	.LFB196
	.8byte	.LFE196-.LFB196
	.uleb128 0x1
	.byte	0x9c
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x21
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0x5
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0xb
	.uleb128 0x5
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0x5
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x20
	.uleb128 0x4
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x21
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x22
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0x6
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x23
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x24
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",@progbits
	.4byte	0x2c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x8
	.byte	0
	.2byte	0
	.2byte	0
	.8byte	.LFB196
	.8byte	.LFE196-.LFB196
	.8byte	0
	.8byte	0
	.section	.debug_ranges,"",@progbits
.Ldebug_ranges0:
	.8byte	.LFB196
	.8byte	.LFE196
	.8byte	0
	.8byte	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF112:
	.string	"fit_uname_cfg"
.LASF114:
	.string	"fit_uname_os"
.LASF17:
	.string	"ulong"
.LASF63:
	.string	"bi_boot_params"
.LASF146:
	.string	"net_gateway"
.LASF172:
	.string	"NETLOOP_FAIL"
.LASF47:
	.string	"bi_memsize"
.LASF115:
	.string	"fit_noffset_os"
.LASF91:
	.string	"ih_load"
.LASF138:
	.string	"sha256_der_prefix"
.LASF170:
	.string	"NETLOOP_RESTART"
.LASF105:
	.string	"type"
.LASF104:
	.string	"comp"
.LASF25:
	.string	"select_hwpart"
.LASF67:
	.string	"FIQ_STACK_START"
.LASF75:
	.string	"totalsize"
.LASF161:
	.string	"net_null_ethaddr"
.LASF10:
	.string	"long long unsigned int"
.LASF80:
	.string	"last_comp_version"
.LASF39:
	.string	"lmb_property"
.LASF150:
	.string	"net_hostname"
.LASF9:
	.string	"long long int"
.LASF3:
	.string	"signed char"
.LASF87:
	.string	"ih_magic"
.LASF62:
	.string	"bi_arch_number"
.LASF109:
	.string	"legacy_hdr_os"
.LASF130:
	.string	"initrd_end"
.LASF108:
	.string	"bootm_headers"
.LASF136:
	.string	"images"
.LASF134:
	.string	"state"
.LASF15:
	.string	"long int"
.LASF20:
	.string	"__be32"
.LASF178:
	.string	"env_t"
.LASF120:
	.string	"fit_uname_fdt"
.LASF71:
	.string	"_datarelro_start_ofs"
.LASF23:
	.string	"ide_bus_offset"
.LASF107:
	.string	"image_info_t"
.LASF148:
	.string	"net_dns_server"
.LASF162:
	.string	"net_our_vlan"
.LASF28:
	.string	"image_base"
.LASF32:
	.string	"sector_count"
.LASF171:
	.string	"NETLOOP_SUCCESS"
.LASF159:
	.string	"net_rx_packet_len"
.LASF133:
	.string	"verify"
.LASF29:
	.string	"_binary_u_boot_bin_start"
.LASF113:
	.string	"fit_hdr_os"
.LASF167:
	.string	"net_boot_file_expected_size_in_blocks"
.LASF147:
	.string	"net_netmask"
.LASF182:
	.string	"/home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/arch/arm/lib/asm-offsets.c"
.LASF127:
	.string	"ft_addr"
.LASF141:
	.string	"load_addr"
.LASF43:
	.string	"memory"
.LASF163:
	.string	"net_native_vlan"
.LASF72:
	.string	"IRQ_STACK_START_IN"
.LASF8:
	.string	"unsigned int"
.LASF96:
	.string	"ih_type"
.LASF92:
	.string	"ih_ep"
.LASF65:
	.string	"bd_t"
.LASF149:
	.string	"net_nis_domain"
.LASF5:
	.string	"__u8"
.LASF1:
	.string	"long unsigned int"
.LASF7:
	.string	"__u32"
.LASF77:
	.string	"off_dt_strings"
.LASF61:
	.string	"bi_busfreq"
.LASF117:
	.string	"fit_uname_rd"
.LASF24:
	.string	"name"
.LASF93:
	.string	"ih_dcrc"
.LASF177:
	.string	"data"
.LASF56:
	.string	"bi_bootflags"
.LASF31:
	.string	"size"
.LASF2:
	.string	"short unsigned int"
.LASF118:
	.string	"fit_noffset_rd"
.LASF145:
	.string	"s_addr"
.LASF129:
	.string	"initrd_start"
.LASF106:
	.string	"arch"
.LASF110:
	.string	"legacy_hdr_os_copy"
.LASF37:
	.string	"flash_info"
.LASF57:
	.string	"bi_ip_addr"
.LASF100:
	.string	"image_info"
.LASF58:
	.string	"bi_enetaddr"
.LASF184:
	.string	"net_loop_state"
.LASF21:
	.string	"errno"
.LASF35:
	.string	"protect"
.LASF103:
	.string	"load"
.LASF40:
	.string	"base"
.LASF83:
	.string	"size_dt_struct"
.LASF79:
	.string	"version"
.LASF160:
	.string	"net_bcast_ethaddr"
.LASF122:
	.string	"fit_hdr_setup"
.LASF13:
	.string	"sizetype"
.LASF123:
	.string	"fit_uname_setup"
.LASF143:
	.string	"save_size"
.LASF151:
	.string	"net_root_path"
.LASF94:
	.string	"ih_os"
.LASF142:
	.string	"save_addr"
.LASF53:
	.string	"bi_arm_freq"
.LASF76:
	.string	"off_dt_struct"
.LASF175:
	.string	"environment_s"
.LASF45:
	.string	"bd_info"
.LASF16:
	.string	"ushort"
.LASF137:
	.string	"sha1_der_prefix"
.LASF180:
	.string	"env_ptr"
.LASF99:
	.string	"image_header_t"
.LASF135:
	.string	"bootm_headers_t"
.LASF181:
	.ascii	"GNU C"
	.string	"11 6.3.1 20170404 -mstrict-align -march=armv8-a -mlittle-endian -mabi=lp64 -g -Os -fno-builtin -ffreestanding -fno-stack-protector -fno-delete-null-pointer-checks -fstack-usage -fno-pic -ffunction-sections -fdata-sections -ffixed-r9 -fno-common -ffixed-x18"
.LASF44:
	.string	"reserved"
.LASF4:
	.string	"uchar"
.LASF82:
	.string	"size_dt_strings"
.LASF119:
	.string	"fit_hdr_fdt"
.LASF22:
	.string	"___strtok"
.LASF48:
	.string	"bi_flashstart"
.LASF166:
	.string	"net_boot_file_size"
.LASF101:
	.string	"image_start"
.LASF41:
	.string	"lmb_region"
.LASF173:
	.string	"net_state"
.LASF97:
	.string	"ih_comp"
.LASF128:
	.string	"ft_len"
.LASF64:
	.string	"bi_dram"
.LASF27:
	.string	"_Bool"
.LASF66:
	.string	"IRQ_STACK_START"
.LASF0:
	.string	"unsigned char"
.LASF90:
	.string	"ih_size"
.LASF155:
	.string	"net_server_ip"
.LASF125:
	.string	"rd_start"
.LASF154:
	.string	"net_ip"
.LASF78:
	.string	"off_mem_rsvmap"
.LASF6:
	.string	"short int"
.LASF74:
	.string	"magic"
.LASF52:
	.string	"bi_sramsize"
.LASF126:
	.string	"rd_end"
.LASF111:
	.string	"legacy_hdr_valid"
.LASF124:
	.string	"fit_noffset_setup"
.LASF158:
	.string	"net_rx_packet"
.LASF140:
	.string	"__dtb_dt_begin"
.LASF54:
	.string	"bi_dsp_freq"
.LASF139:
	.string	"monitor_flash_len"
.LASF153:
	.string	"net_server_ethaddr"
.LASF19:
	.string	"uint32_t"
.LASF69:
	.string	"_datarelrolocal_start_ofs"
.LASF68:
	.string	"_datarel_start_ofs"
.LASF38:
	.string	"long double"
.LASF14:
	.string	"char"
.LASF121:
	.string	"fit_noffset_fdt"
.LASF49:
	.string	"bi_flashsize"
.LASF86:
	.string	"image_header"
.LASF179:
	.string	"default_environment"
.LASF11:
	.string	"phys_addr_t"
.LASF51:
	.string	"bi_sramstart"
.LASF102:
	.string	"image_len"
.LASF183:
	.string	"/home/cx/work/project/CV183X/CV183X_SDK/t2.2.0.1/t2.2.0.1_sourceV2/t2.2.0.1_source/u-boot/build/cv1838_wevb_0002a_spinand"
.LASF33:
	.string	"flash_id"
.LASF89:
	.string	"ih_time"
.LASF73:
	.string	"fdt_header"
.LASF152:
	.string	"net_ethaddr"
.LASF84:
	.string	"working_fdt"
.LASF59:
	.string	"bi_ethspeed"
.LASF26:
	.string	"block_drvr"
.LASF42:
	.string	"region"
.LASF164:
	.string	"net_restart_wrap"
.LASF169:
	.string	"NETLOOP_CONTINUE"
.LASF60:
	.string	"bi_intfreq"
.LASF132:
	.string	"cmdline_end"
.LASF12:
	.string	"phys_size_t"
.LASF36:
	.string	"flash_info_t"
.LASF165:
	.string	"net_boot_file_name"
.LASF88:
	.string	"ih_hcrc"
.LASF174:
	.string	"env_name_spec"
.LASF18:
	.string	"uint8_t"
.LASF116:
	.string	"fit_hdr_rd"
.LASF81:
	.string	"boot_cpuid_phys"
.LASF176:
	.string	"flags"
.LASF168:
	.string	"net_ping_ip"
.LASF157:
	.string	"net_rx_packets"
.LASF98:
	.string	"ih_name"
.LASF55:
	.string	"bi_ddr_freq"
.LASF46:
	.string	"bi_memstart"
.LASF34:
	.string	"start"
.LASF185:
	.string	"main"
.LASF85:
	.string	"fdt32_t"
.LASF30:
	.string	"_binary_u_boot_bin_end"
.LASF95:
	.string	"ih_arch"
.LASF50:
	.string	"bi_flashoffset"
.LASF70:
	.string	"_datarellocal_start_ofs"
.LASF156:
	.string	"net_tx_packet"
.LASF131:
	.string	"cmdline_start"
.LASF144:
	.string	"in_addr"
	.ident	"GCC: (Linaro GCC 6.3-2017.05) 6.3.1 20170404"
	.section	.note.GNU-stack,"",@progbits
