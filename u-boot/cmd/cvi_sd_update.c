#include <stdlib.h>
#include <common.h>
#include <config.h>
#include <command.h>
#include <fs.h>
#include <part.h>
#include <vsprintf.h>
#include <u-boot/md5.h>
#include <image-sparse.h>
#include <div64.h>
#include <linux/math64.h>
#include <fdt.h>

#ifdef DEBUG
#define pr_debug(fmt, ...) \
	printf(fmt, ##__VA_ARGS__)
#else
#define pr_debug(fmt, ...)
#endif

#define		BIT_WRITE_FIP_BIN	BIT(0)
#define		BIT_WRITE_ROM_PATCH	BIT(1)
#define		BIT_WRITE_BLD		BIT(2)

#define		COMPARE_STRING_LEN	6

//------------------------------------------------------------------------------
//  data type definitions: typedef, struct or class
//------------------------------------------------------------------------------
#define PTR_INC(base, offset) (void *)((uint8_t *)(base) + (offset))

static int do_cvi_update_spinor(uint32_t component, void *addr)
{
	printf("do_bm_update_spinor com 0x%x\n", component);

	return 0;
}

#ifdef CONFIG_NAND_FLASH_CVSNFC
extern int do_cvi_update_spinand(uint32_t component, void *addr);
#endif

static int do_cvi_sd_update(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	char *addr;
	uint32_t component = 0;

	if (argc != 4) {
		printf("Usage:\n%s\n", cmdtp->usage);
		return 1;
	}

	addr = (char *)simple_strtol(argv[1], NULL, 16);

	if (!addr) {
		printf("Usage:\n%s\n", cmdtp->usage);
		return 1;
	}

	printf("addr %p\n", addr);

	if (!strncmp(argv[3], "fip", COMPARE_STRING_LEN)) {
		printf("fip.bin\n");
		component |= BIT_WRITE_FIP_BIN;

	} else if (!strncmp(argv[3], "patch", COMPARE_STRING_LEN)) {
		printf("patch\n");
		component |= BIT_WRITE_ROM_PATCH;
	} else if (!strncmp(argv[3], "all", COMPARE_STRING_LEN)) {
		printf("all\n");
		component |= BIT_WRITE_FIP_BIN | BIT_WRITE_ROM_PATCH | BIT_WRITE_BLD;
	} else {
		printf("Usage:\n%s\n", cmdtp->usage);
		return 1;
	}

	if (!strncmp(argv[2], "spinor", COMPARE_STRING_LEN)) {
		do_cvi_update_spinor(component, addr);
	} else if (!strncmp(argv[2], "spinand", COMPARE_STRING_LEN)) {
#ifdef CONFIG_NAND_FLASH_CVSNFC
		do_cvi_update_spinand(component, addr);
#endif
	} else {
		printf("Usage:\n%s\n", cmdtp->usage);
		return 1;
	}

	return 0;
}

U_BOOT_CMD(
	cvi_sd_update, 4, 0, do_cvi_sd_update,
	"cvi_sd_update - write images to SPI NOR/SPI NAND\n",
	"cvi_sd_update addr dev_type img_type  - Print a report\n"
	"addr     : data memory address\n"
	"dev_type : spinor/spinand\n"
	"img_type : fip/patch/all\n"
);
