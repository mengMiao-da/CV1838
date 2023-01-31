/*
 * Copyright (C) 2014 Marek Vasut <marex@denx.de>
 *
 * Command for en/de-crypting block of memory with AES-128-CBC cipher.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <command.h>
#include <environment.h>
#include <uboot_aes.h>
#include <malloc.h>
#include <asm/byteorder.h>
#include <linux/compiler.h>

#ifdef CONFIG_FIT
#include <fdt.h>
#endif

#ifdef UBOOT_VBOOT
#include "mbedtls/aes.h"
#endif

DECLARE_GLOBAL_DATA_PTR;

/**
 * do_aes() - Handle the "aes" command-line command
 * @cmdtp:	Command data struct pointer
 * @flag:	Command flag
 * @argc:	Command-line argument count
 * @argv:	Array of command-line arguments
 *
 * Returns zero on success, CMD_RET_USAGE in case of misuse and negative
 * on error.
 */
static int do_aes(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
	uintptr_t key_addr, src_addr, dst_addr, len;
	uint8_t *key_ptr, *src_ptr, *dst_ptr;
	uint8_t key_exp[AES_EXPAND_KEY_LENGTH];
	uint32_t aes_blocks;
	int enc;

	if (argc != 6)
		return CMD_RET_USAGE;

	if (!strncmp(argv[1], "enc", 3))
		enc = 1;
	else if (!strncmp(argv[1], "dec", 3))
		enc = 0;
	else
		return CMD_RET_USAGE;

	key_addr = simple_strtoul(argv[2], NULL, 16);
	src_addr = simple_strtoul(argv[3], NULL, 16);
	dst_addr = simple_strtoul(argv[4], NULL, 16);
	len = simple_strtoul(argv[5], NULL, 16);

	key_ptr = (uint8_t *)key_addr;
	src_ptr = (uint8_t *)src_addr;
	dst_ptr = (uint8_t *)dst_addr;

	/* First we expand the key. */
	aes_expand_key(key_ptr, key_exp);

	/* Calculate the number of AES blocks to encrypt. */
	aes_blocks = DIV_ROUND_UP(len, AES_KEY_LENGTH);

	if (enc)
		aes_cbc_encrypt_blocks(key_exp, src_ptr, dst_ptr, aes_blocks);
	else
		aes_cbc_decrypt_blocks(key_exp, src_ptr, dst_ptr, aes_blocks);

	return 0;
}

#if defined(CONFIG_FIT) && defined(UBOOT_VBOOT)
/**
 * do_aes() - Handle the "aes" command-line command
 * @cmdtp:	Command data struct pointer
 * @flag:	Command flag
 * @argc:	Command-line argument count
 * @argv:	Array of command-line arguments
 *
 * Returns zero on success, CMD_RET_USAGE in case of misuse and negative
 * on error.
 */

static void debug_print_vector(const char *name, u32 num_bytes, const u8 *data)
{
#ifdef DEBUG
	printf("%s [%d] @0x%08lx: ", name, num_bytes, (uintptr_t)data);
	print_buffer(0, data, 1, num_bytes, 16);
#endif
}

static const uint8_t *get_reeos_ek_from_fdt(int *plen)
{
	const void *fdt_blob = gd_fdt_blob();
	int ienc_node = 0;
	int len = 0;
	const uint8_t *ek = NULL;

	ienc_node = fdt_subnode_offset(fdt_blob, 0, "itb_encryption");
	if (ienc_node < 0) {
		debug("%s: No itb_encryption node found: %s\n", __func__,
		      fdt_strerror(ienc_node));
		return NULL;
	}

	ek = (uint8_t *)fdt_getprop(fdt_blob, ienc_node, "reeos_ek", &len);
	debug("%s: ek=%d bytes\n", __func__, len);
	if (!ek)
		return NULL;

	debug_print_vector("ek", 16, (void *)ek);

	if (plen)
		*plen = len;

	return ek;
}

static int do_aes_itb(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
	uintptr_t key_addr, src_addr, dst_addr;
	const uint8_t *key_ptr;
	uint8_t *src_ptr, *dst_ptr;

	mbedtls_aes_context aes;
	int use_fdt_key = 0;
	int fdt_key_len = 0;
	struct fdt_header *fh;
	uint32_t magic = 0;
	uint32_t totalsize = 0;
	uint32_t aes_blocks = 0;
	int ret = 0;

	unsigned char iv[16] = { 0 };

	ulong base = get_timer(0);

	if (argc != 5)
		return CMD_RET_USAGE;

	if (!strncmp(argv[1], "dec_fdt_key", 7))
		use_fdt_key = 1;
	else
		return CMD_RET_USAGE;

	key_addr = simple_strtoul(argv[2], NULL, 16);
	src_addr = simple_strtoul(argv[3], NULL, 16);
	dst_addr = simple_strtoul(argv[4], NULL, 16);

	src_ptr = (uint8_t *)src_addr;
	dst_ptr = (uint8_t *)dst_addr;

	debug("%s: key_addr=%lu use_fdt_key=%d\n", argv[0], key_addr,
	      use_fdt_key);

	if (use_fdt_key) {
		key_ptr = get_reeos_ek_from_fdt(&fdt_key_len);
		if (ret) {
			debug("%s: can't find reeos_ek\n", argv[0]);
			return CMD_RET_FAILURE;
		}

		if (fdt_key_len != AES_KEY_LENGTH) {
			debug("%s: fdt_key must be %d bytes but is %d bytes\n",
			      argv[0], AES_KEY_LENGTH, fdt_key_len);
			return CMD_RET_FAILURE;
		}
	} else {
		key_ptr = (uint8_t *)key_addr;
	}

	debug_print_vector("key", 16, key_ptr);
	debug_print_vector("src_ptr", 32, src_ptr);

	/* Decrypt the first block to get magic and totalsize */
	debug("%s: %lums elapsed\n", argv[0], get_timer(base));
	mbedtls_aes_init(&aes);
	mbedtls_aes_setkey_dec(&aes, key_ptr, 128);
	ret = mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_DECRYPT, AES_KEY_LENGTH,
				    iv, (unsigned char *)src_ptr,
				    (unsigned char *)dst_ptr);
	if (ret) {
		debug("%s: ret=%d\n", argv[0], ret);
		return ret;
	}

	/* Check FDT */
	fh = (struct fdt_header *)dst_ptr;
	totalsize = htonl(fh->totalsize);
	magic = htonl(fh->magic);
	printf("%s: magic=0x%08x totalsize=%u\n", argv[0], magic, totalsize);

	if (magic != FDT_MAGIC) {
		printf("%s: magic is not correct\n", argv[0]);
		return CMD_RET_FAILURE;
	}
	debug("%s: %lums elapsed\n", argv[0], get_timer(base));

	/* Calculate the number of AES blocks to encrypt. */
	aes_blocks = DIV_ROUND_UP(totalsize, AES_KEY_LENGTH);

	/* Decrypt .itb */
	src_ptr += AES_KEY_LENGTH;
	dst_ptr += AES_KEY_LENGTH;
	ret = mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_DECRYPT,
				    (aes_blocks - 1) * AES_KEY_LENGTH, iv,
				    (unsigned char *)src_ptr,
				    (unsigned char *)dst_ptr);

	debug("%s: %lums elapsed\n", argv[0], get_timer(base));
	debug_print_vector("dst_ptr", 32, dst_ptr);
	debug("%s: ret=%d\n", argv[0], ret);

	return ret;
}
#endif /* CONFIG_FIT && UBOOT_VBOOT */

/***************************************************/
#ifdef CONFIG_SYS_LONGHELP
static char aes_help_text[] =
	"enc key src dst len - Encrypt block of data $len bytes long\n"
	"                          at address $src using a key at address\n"
	"                          $key and store the result at address\n"
	"                          $dst. The $len size must be multiple of\n"
	"                          16 bytes and $key must be 16 bytes long.\n"
	"aes dec key src dst len - Decrypt block of data $len bytes long\n"
	"                          at address $src using a key at address\n"
	"                          $key and store the result at address\n"
	"                          $dst. The $len size must be multiple of\n"
	"                          16 bytes and $key must be 16 bytes long.";

#if defined(CONFIG_FIT) && defined(UBOOT_VBOOT)
static char aes_itb_help_text[] =
	"dec key src dst - Decrypt .itb\n";
#endif
#endif

U_BOOT_CMD(
	aes, 6, 1, do_aes,
	"AES 128 CBC encryption",
	aes_help_text
);

#if defined(CONFIG_FIT) && defined(UBOOT_VBOOT)
U_BOOT_CMD(
	aes_itb, 5, 1, do_aes_itb,
	"AES 128 CBC encryption for ITB",
	aes_itb_help_text
);
#endif
