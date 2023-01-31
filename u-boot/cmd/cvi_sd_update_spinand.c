#include <stdlib.h>
#include <common.h>
#include <config.h>
#include <command.h>
#include <fs.h>
#include <part.h>
#include <vsprintf.h>
#include <u-boot/md5.h>
#include <image-sparse.h>
#include <bm_emmc_burn.h>
#include <div64.h>
#include <linux/math64.h>
#include <fdt.h>
#include <linux/log2.h>

#ifdef CONFIG_NAND_FLASH_CVSNFC

#define cvi_assert(expr) do {\
		if (!(expr)) {\
			printf("%s:%d[%s]\n", __FILE__, __LINE__, __func__);\
			while \
				(1);\
		} \
	} while (0)

#include <cvsnfc.h>

//#define CVI_SD_UPDATE_DEBUG

#ifdef CVI_SD_UPDATE_DEBUG
#define pr_debug(fmt, ...) \
	printf(fmt, ##__VA_ARGS__)

#define DEBUG_WRITE 1
#define DEBUG_READ  1
#define DEBUG_ERASE 1
#define DEBUG_CMD_FLOW 1
#else
#define pr_debug(fmt, ...)
#define DEBUG_WRITE 0
#define DEBUG_READ  0
#define DEBUG_ERASE 0
#define DEBUG_CMD_FLOW 0
#endif

#define FORCE_ROM_USE_2K_PAGE
#define PLAT_BM_FIP_MAX_SIZE	0xA0000    // 640KB, Fixed, don't change unless you know it
#define PLAT_BM_FIP_MAX_CHECK_SIZE	0xA0000    // 640KB, Fixed, don't change unless you know it


extern void bbt_dump_buf(char *s, void *buf, int len);

//------------------------------------------------------------------------------
//  data type definitions: typedef, struct or class
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//  constant definitions:
//------------------------------------------------------------------------------

#define SPI_NAND_VECTOR_SIGNATURE DESC_CONV("SPNV")
#define PRODUCTION_FW_SIGNATURE DESC_CONV("PTFM")

#ifdef NANDBOOT_V2
#define SPI_NAND_VECTOR_VERSION (0x18222001)
#else
#define SPI_NAND_VECTOR_VERSION (0x18352101)
#endif

/* system vector related definitions */
#define SPI_NAND_BASE_DATA_BACKUP_COPY (2)

#define SPI_NAND_FIP_DATA_BLOCK_COUNT (8)
#define SPI_NAND_FIP_DATA_BACKUP_COUNT (2)

#define SPI_NAND_BASE_RESERVED_ENTRY (4)
#define MAX_BLOCK_CNT			4096
/* system vector relocated definitions end here */

#define SPI_NAND_SV_RSVD_BLOCK_COUNT (4) // first 4 blocks are reserved for sys base vector
#define SPI_NAND_FIP_RSVD_BLOCK_COUNT (20) // Reserved blocks for FIP.

#define BIT(nr)			(1UL << (nr))

#define NUMBER_PATCH_SET 128

#define PTR_INC(base, offset) (void *)((uint8_t *)(base) + (offset))
#define GET_PG_IDX_IN_BLK(x, y) ((x) % (y))
#define GET_BLK_IDX(x, y) ((x) / (y))

struct _patch_data_t {
	uint32_t reg;
	uint32_t value;
};

struct _spi_nand_info {
	uint16_t id;
	uint16_t page_size;

	uint16_t spare_size;
	uint16_t pages_per_block;

	uint16_t block_cnt; // up to 32k block
	uint8_t pages_per_block_shift;
	uint8_t flags;
#ifdef NANDBOOT_V2
	uint8_t ecc_en_feature_offset;
	uint8_t ecc_en_mask;
	uint8_t ecc_status_offset;
	uint8_t ecc_status_mask;
	uint8_t ecc_status_shift;
	uint8_t ecc_status_valid_val;
#endif
};

struct _spi_nand_base_vector_t {
	uint32_t signature;
	uint32_t version;

	uint16_t spi_nand_vector_blks[SPI_NAND_BASE_DATA_BACKUP_COPY];

	uint16_t fip_bin_blk_cnt;
	uint16_t fip_bin_blks[SPI_NAND_BASE_DATA_BACKUP_COPY][SPI_NAND_FIP_DATA_BLOCK_COUNT];

	uint16_t erase_count; // erase count for sys base block
	uint16_t rsvd_block_count; // how many blocks reserved for spi_nand_vect and fip.bin
	uint32_t spi_nand_vector_length;  // spi_nand vector struct length, must less than a page

	uint8_t spi_nand_base_block_usage[SPI_NAND_BASE_RESERVED_ENTRY];

	struct _spi_nand_info spi_nand_info;

	uint8_t factory_defect_buf[MAX_BLOCK_CNT / 8]; // factory defect block table, up to 512 bytes

	uint32_t bld_size;
	uintptr_t bld_loading_to_addr;

	uint32_t valid_patch_num;
	struct _patch_data_t patch_data[NUMBER_PATCH_SET];
#ifdef NANDBOOT_V2
	uint16_t crc;
#endif
	uint8_t ecc_en_feature_offset;
	uint8_t ecc_en_mask;
	uint8_t ecc_status_offset;
	uint8_t ecc_status_mask;
	uint8_t ecc_status_shift;
	uint8_t ecc_status_valid_val;
};

uint8_t sys_vec_buf[MAX_PAGE_SIZE + MAX_SPARE_SIZE];

struct _spi_nand_base_vector_t *g_spi_nand_sys_vec = (struct _spi_nand_base_vector_t *)sys_vec_buf;
struct _spi_nand_info spinand_info;
static char spi_nand_defect_buf[MAX_BLOCK_CNT / 8];

uint8_t pg_buf[MAX_PAGE_SIZE + MAX_SPARE_SIZE];

extern struct cvsnfc_host *cvsnfc_get_host(void);
extern int cvsnfc_read_page(struct mtd_info *mtd, struct nand_chip *chip,
			    uint8_t *buf, int bytes, int page);
extern int cvsnfc_write_page(struct mtd_info *mtd, struct nand_chip *chip,
			     const uint8_t *buf, int oob_required, int page);
extern int cvsnfc_read_page_raw(struct mtd_info *mtd, struct nand_chip *chip,
				uint8_t *buf, int oob_required, int page);
extern void cvsnfc_ctrl_ecc(struct mtd_info *mtd, bool enable);
extern void cvsnfc_send_cmd_erase(struct cvsnfc_host *host);

uint32_t g_virgin_start;

int spi_nand_flush_vec(void);
void spi_nand_dump_vec(void);

static inline u32 DESC_CONV(char *x)
{
	return ((((((x[0] << 8) | x[1]) << 8) | x[2]) << 8) | x[3]);
}

static inline u32 CHECK_MASK_BIT(void *_mask, u32 bit)
{
	u32 w = bit / 8;
	u32 off = bit % 8;

	return ((u8 *)_mask)[w] & (1 << off);
}

static inline void SET_MASK_BIT(void *_mask, u32 bit)
{
	u32 byte = bit / 8;
	u32 offset = bit % 8;
	((u8 *)_mask)[byte] |= (1 << offset);
}

static int spi_nand_scan_vector(void)
{
	struct _spi_nand_base_vector_t *sv = g_spi_nand_sys_vec;
	struct cvsnfc_host *host = cvsnfc_get_host();
	struct _spi_nand_info *info = &spinand_info;

	memset(pg_buf, 0, MAX_PAGE_SIZE + MAX_SPARE_SIZE);

	cvsnfc_ctrl_ecc(host->mtd, 1);

	for (u16 blk_idx = 0; blk_idx < SPI_NAND_BASE_DATA_BACKUP_COPY; blk_idx++) {
		u32 status;
		u32 blk_id;

		// only check page 0 for each block
		status = cvsnfc_read_page(host->mtd, host->chip, (void *)pg_buf, info->page_size,
					  (blk_idx << info->pages_per_block_shift) + 0);

		if (status < 0) {
			printf("spi_nand_scan_vector read error\n");
			continue;
		} else if (status > 0) {
			printf("blk_idx %d page 0 got ecc corr\n", blk_idx);
		}

		memcpy(sv, pg_buf, sizeof(struct _spi_nand_base_vector_t));

		//Verify the blk_id of SV and FIP are valid
		for (u32 i = 0; i < SPI_NAND_BASE_DATA_BACKUP_COPY; i++) {
			blk_id = sv->spi_nand_vector_blks[i];
			if (blk_id >= SPI_NAND_SV_RSVD_BLOCK_COUNT)
				goto failout;
		}

		for (u32 i = 0; i < SPI_NAND_BASE_DATA_BACKUP_COPY; i++) {
			for (u32 j = 0; j < sv->fip_bin_blk_cnt; j++) {
				blk_id = sv->fip_bin_blks[i][j];
				if (blk_id >= SPI_NAND_FIP_RSVD_BLOCK_COUNT)
					goto failout;
			}
		}

		if (sv->signature == SPI_NAND_VECTOR_SIGNATURE) {
			printf("sv found version 0x%x\n", sv->version);
			spi_nand_adjust_max_freq(host, &sv->signature, &sv->version);
			return 0;
		}
	}

failout:
	printf("Can't find correct system vector!\n");
	return -1;
}

extern void bbt_dump_buf(char *s, void *buf, int len);

static int spi_nand_scan_defect(void)
{
	int status;
	struct _spi_nand_info *info = &spinand_info;
	struct cvsnfc_host *host = cvsnfc_get_host();

	u32 ttl_pg_sz = info->page_size + info->spare_size;

	printf("%s\n", __func__);

	for (u32 blk_id = 0; blk_id < info->block_cnt; blk_id++) {
		uint32_t pg = blk_id << info->pages_per_block_shift;

		host->addr_value[1] = pg;
		cvsnfc_send_cmd_erase(host);

		memset(pg_buf, 0xff, ttl_pg_sz);
		status = cvsnfc_read_page_raw(host->mtd, host->chip, pg_buf, 0, pg);

		if (status) {
			printf("read status %d, ", status);
			cvi_assert(0);
		}

		u8 *mark = (u8 *)(pg_buf + info->page_size);

		if ((*mark != 0xff) || (*pg_buf != 0xff)) {
			printf("\n\nFound bad block %d, ", blk_id);
			printf("bad ");
			printf(" mark : 0x%x, first byte: 0x%x\n\n", *mark, *pg_buf);
			bbt_dump_buf("data:", pg_buf, 16);
			bbt_dump_buf("oob_data:", mark, 16);
			SET_MASK_BIT(spi_nand_defect_buf, blk_id);
		}
	}

	return 0;
}

void get_spi_nand_info(void)
{
	struct cvsnfc_host *host = cvsnfc_get_host();

	spinand_info.id = host->nand_chip_info->id[0] | host->nand_chip_info->id[1] << 8;
	spinand_info.page_size = host->nand_chip_info->pagesize;

	spinand_info.spare_size = host->nand_chip_info->oobsize;
	spinand_info.pages_per_block = host->nand_chip_info->erasesize /
				       host->nand_chip_info->pagesize;

	spinand_info.block_cnt = SPI_NAND_FIP_RSVD_BLOCK_COUNT;
	spinand_info.pages_per_block_shift = ilog2(spinand_info.pages_per_block);

	spinand_info.flags = 0;
#ifdef NANDBOOT_V2
	// TODO: get ecc info form nand_chip_info
	spinand_info.ecc_en_feature_offset = 0xb0;
	spinand_info.ecc_en_mask = 1 << 4;
	spinand_info.ecc_status_offset = 0xc0;
	spinand_info.ecc_status_mask = 0x30;
	spinand_info.ecc_status_shift = 4;
	spinand_info.ecc_status_valid_val = 1;
#else
	g_spi_nand_sys_vec->ecc_en_feature_offset = 0xb0;
	g_spi_nand_sys_vec->ecc_en_mask = 1 << 4;
	g_spi_nand_sys_vec->ecc_status_offset = 0xc0;
	g_spi_nand_sys_vec->ecc_status_mask = 0x30;
	g_spi_nand_sys_vec->ecc_status_shift = 4;
	g_spi_nand_sys_vec->ecc_status_valid_val = 1;
#endif
}

static void fill_spi_nand_patch(void)
{
	struct _spi_nand_base_vector_t *sv = g_spi_nand_sys_vec;
	struct _patch_data_t *patch_set = sv->patch_data;

	sv->valid_patch_num = 0;

	patch_set[0].reg = 0x03000154;
	patch_set[0].value = 0x26;

	patch_set[1].reg = 0xe001000;
	patch_set[1].value = 0xabcdef;

	patch_set[2].reg = 0xe001004;
	patch_set[2].value = 0xafafafef;
}

static int spi_nand_blk_allocator(u32 for_vec)
{
	int blk_idx;
	struct _spi_nand_base_vector_t *sv = g_spi_nand_sys_vec;

//	dump_hex((void *)"sv->spi_nand_base_block_usage", sv->spi_nand_base_block_usage, 4);

	if (for_vec) {
		for (blk_idx = 0; blk_idx < SPI_NAND_SV_RSVD_BLOCK_COUNT; blk_idx++)
			if (CHECK_MASK_BIT(sv->spi_nand_base_block_usage, blk_idx) == 0)
				break;
	} else {
		for (blk_idx = SPI_NAND_SV_RSVD_BLOCK_COUNT; blk_idx < sv->spi_nand_info.block_cnt; blk_idx++)
			if (CHECK_MASK_BIT(sv->spi_nand_base_block_usage, blk_idx) == 0)
				break;
	}

	if (blk_idx == sv->spi_nand_info.block_cnt) {
		printf("error alloc wrong block idx\n");
		return -1;
	}

	SET_MASK_BIT(sv->spi_nand_base_block_usage, blk_idx);

	return blk_idx;
}

int init_spi_nand_vect(void)
{
	struct _spi_nand_base_vector_t *sv = g_spi_nand_sys_vec;
	struct _spi_nand_info *info = &spinand_info;

	u32 i = 0, j = 0;
	int blk_idx = 0;

	memset(sv, 0, MAX_PAGE_SIZE);

	sv->signature = SPI_NAND_VECTOR_SIGNATURE;
	sv->version = SPI_NAND_VECTOR_VERSION;
	sv->erase_count = 1;
	sv->rsvd_block_count = SPI_NAND_FIP_RSVD_BLOCK_COUNT;
	sv->spi_nand_vector_length = sizeof(struct _spi_nand_base_vector_t);
	printf("sv length %d\n", sv->spi_nand_vector_length);

	cvi_assert(sv->spi_nand_vector_length <= info->page_size);
	memcpy(&sv->spi_nand_info, info, sizeof(struct _spi_nand_info));
	memcpy(sv->spi_nand_base_block_usage, spi_nand_defect_buf, SPI_NAND_BASE_RESERVED_ENTRY);
	memcpy(sv->factory_defect_buf, spi_nand_defect_buf, sv->spi_nand_info.block_cnt / 8);

#ifndef NANDBOOT_V2
    // Set spinand info in sv
	get_spi_nand_info();
#endif

#ifdef FORCE_ROM_USE_2K_PAGE
	sv->spi_nand_info.page_size = 2048; // for fip and sys vec use 2k page
#endif

	fill_spi_nand_patch();

	printf("[SPI_NAND][BASE]alloc spi_nand vector blocks\n");

	// Alloc spi_nand vector blk
	for (i = 0; i < SPI_NAND_BASE_DATA_BACKUP_COPY; i++) {
		blk_idx = spi_nand_blk_allocator(1);

		if (blk_idx == -1) {
			printf("[SPI_NAND][BASE] Error: unable to allow new block\n");
			cvi_assert(0);
		}

		sv->spi_nand_vector_blks[i] = blk_idx;
		printf("[SPI_NAND][BASE]spi_nand vector block%d: %d\n", i, blk_idx);
	}

	// Alloc fip.bin blocks
	sv->fip_bin_blk_cnt = (PLAT_BM_FIP_MAX_SIZE - 1) /
						(info->pages_per_block * sv->spi_nand_info.page_size) + 1;//Integer up

	printf("sv->fip_bin_blk_cnt %d, PLAT_BM_FIP_MAX_SIZE %d\n", sv->fip_bin_blk_cnt, PLAT_BM_FIP_MAX_SIZE);

	for (i = 0; i < SPI_NAND_FIP_DATA_BACKUP_COUNT; i++) {
		for (j = 0; j < sv->fip_bin_blk_cnt; j++) {
			blk_idx = spi_nand_blk_allocator(0);

			if (blk_idx == -1) {
				printf("[SPI_NAND][BASE] Error: unable to allow new block\n");
				cvi_assert(0);
			}

			sv->fip_bin_blks[i][j] = blk_idx;
			printf("[SPI_NAND][BASE] alloc fip block [%d][%d]: %d\n", i, j, blk_idx);
		}
	}

#ifndef NANDBOOT_V2
	printf("ecc_en_feature_offset:%d\n", sv->ecc_en_feature_offset);
	printf("ecc_en_mask:0x%x\n", sv->ecc_en_mask);
	printf("ecc_status_offset:0x%x\n", sv->ecc_status_offset);
	printf("ecc_status_mask:0x%x\n", sv->ecc_status_mask);
	printf("ecc_status_shift:%d\n", sv->ecc_status_shift);
	printf("ecc_status_valid_val:%d\n", sv->ecc_status_valid_val);
#endif

	return 0;
}

static void verify_fip_bin(void *buf)
{
	void *src_buf_addr = 0;
	struct _spi_nand_base_vector_t *sv = g_spi_nand_sys_vec;
	struct cvsnfc_host *host = cvsnfc_get_host();
	int status = 0;
	void *buffer;

	buffer = (void *)buf;

	u32 pg_sz = sv->spi_nand_info.page_size;
	u32 ttl_pg_cnt_to_check = PLAT_BM_FIP_MAX_SIZE / pg_sz;
	u32 pg_per_blk = sv->spi_nand_info.pages_per_block;

	printf("%s pg_sz %d ttl_pg_cnt_to_check %d, pg_per_blk %d\n",
	       __func__, pg_sz, ttl_pg_cnt_to_check, pg_per_blk);

	for (u32 i = 0; i < SPI_NAND_BASE_DATA_BACKUP_COPY; i++) {
		for (u32 pg_idx_in_buf = 0; pg_idx_in_buf < ttl_pg_cnt_to_check; pg_idx_in_buf++) {
			u32 pg_idx_in_blk = GET_PG_IDX_IN_BLK(pg_idx_in_buf, pg_per_blk);
			u32 blk_idx = GET_BLK_IDX(pg_idx_in_buf, pg_per_blk);

			u32 offset_in_buf = pg_idx_in_buf * pg_sz;

			u32 blk_id = sv->fip_bin_blks[i][blk_idx];

			src_buf_addr = PTR_INC(buffer, offset_in_buf);

			if (DEBUG_READ)
				printf("Read back fip.bin page idx %d, blk_id %d, src buf addr %p\n",
				       pg_idx_in_blk, blk_id, src_buf_addr);

			status = cvsnfc_read_page(host->mtd, host->chip, (void *)pg_buf, pg_sz,
						  (blk_id << sv->spi_nand_info.pages_per_block_shift) + pg_idx_in_blk);

			if (status < 0) {
				printf("Read failed, please check. STOP!\n");
				cvi_assert(0);
			} else if (status > 0) {
				printf("Read ecc corr page idx %d, blk_id %d\n", pg_idx_in_blk, blk_id);
			}

			if (memcmp(src_buf_addr, pg_buf, pg_sz)) {
				printf("fip read back compare error!\n");
				bbt_dump_buf((void *)"src_buf_addr", src_buf_addr, pg_sz >> 4);
				bbt_dump_buf((void *)"pg_buf", pg_buf, pg_sz >> 4);
				cvi_assert(0);
			}
		}
	}
}

static int update_fip_data(struct cvsnfc_host *host, int *fip_sts, int damaged_blk_cnt)
{
	struct _spi_nand_base_vector_t *sv = g_spi_nand_sys_vec;
	int blk_idx = 0, i = 0, j = 0;
	int alloc_new_blk_num = 0;
	int status = 0, ret = 0;

	printf("%s\n", __func__);

	bbt_dump_buf("sv->factory_defect_buf", sv->spi_nand_base_block_usage, 4);

	for (blk_idx = SPI_NAND_SV_RSVD_BLOCK_COUNT; blk_idx < sv->spi_nand_info.block_cnt; blk_idx++) {
		printf("blk_idx %d is %s\n", blk_idx, !!CHECK_MASK_BIT(sv->spi_nand_base_block_usage, blk_idx) ? "used" : "free");
	}

	printf("fip_bin_blk_cnt 0x%x\n", sv->fip_bin_blk_cnt);
	printf("dump orginal fip blk idx :\n");

	for (i = 0; i < SPI_NAND_BASE_DATA_BACKUP_COPY; i++) {
		for (j = 0; j < SPI_NAND_FIP_DATA_BLOCK_COUNT; j++)
			printf("fip bin blks %d %d 0x%x\n", i, j, sv->fip_bin_blks[i][j]);
	}

	// alloc new blocks for backup fip
	for (i = 0; i < sv->fip_bin_blk_cnt; i++) {

		// if one block is ok, skip it
		if (fip_sts[i] == 0)
			continue;

		blk_idx = spi_nand_blk_allocator(0);

		if (blk_idx == -1) {
			printf("[SPI_NAND][BASE] Error: unable to allow new block\n");
			break;
		}

		sv->fip_bin_blks[0][i] = blk_idx;
		printf("[SPI_NAND][BASE] alloc fip block [0][%d]: %d\n", i, blk_idx);
		alloc_new_blk_num++;
	}

	if (alloc_new_blk_num < damaged_blk_cnt) {
		printf("ERROR: no more free block %d / %d !!\n", alloc_new_blk_num, damaged_blk_cnt);
	}

	printf("Dump new fip blk idx :\n");

	for (i = 0; i < SPI_NAND_BASE_DATA_BACKUP_COPY; i++) {
		for (j = 0; j < SPI_NAND_FIP_DATA_BLOCK_COUNT; j++)
			printf("fip bin blks %d %d 0x%x\n", i, j, sv->fip_bin_blks[i][j]);
	}

	bbt_dump_buf("new sv->factory_defect_buf", sv->spi_nand_base_block_usage, 4);

	// erase first copy fip's blocks
	for (u32 i = 0; i < sv->fip_bin_blk_cnt ; i++) {
		u32 blk_id = sv->fip_bin_blks[0][i];

		cvi_assert(blk_id <= MAX_BLOCK_CNT);

		uint32_t pg = blk_id << sv->spi_nand_info.pages_per_block_shift;

		host->addr_value[1] = pg;
		printf("erase blk %d\n", blk_id);
		cvsnfc_send_cmd_erase(host);

		if (status) {
			printf("erase error\n");
			ret = -1;
			goto bailout;
		}
	}

	// copy data from copy 1 to copy 0
	u32 src_copy_idx = 1;
	u32 dst_copy_idx = 0;
	u32 pg_sz = sv->spi_nand_info.page_size;
	u32 ttl_pg_cnt_to_write = PLAT_BM_FIP_MAX_SIZE / pg_sz;
	u32 pg_per_blk = sv->spi_nand_info.pages_per_block;

	printf("ttl_pg_cnt_to_write %d\n", ttl_pg_cnt_to_write);

	for (u32 pg_idx_in_buf = 0; pg_idx_in_buf < ttl_pg_cnt_to_write; pg_idx_in_buf++) {
		u32 pg_idx_in_blk = GET_PG_IDX_IN_BLK(pg_idx_in_buf, pg_per_blk);
		u32 blk_idx = GET_BLK_IDX(pg_idx_in_buf, pg_per_blk);

//		u32 offset_in_buf = pg_idx_in_buf * pg_sz;

		u32 src_blk_id = sv->fip_bin_blks[src_copy_idx][blk_idx];
		u32 dst_blk_id = sv->fip_bin_blks[dst_copy_idx][blk_idx];

		if (DEBUG_READ)
			printf("Read back fip.bin page idx %d, src_blk_id %d, pg_idx_in_blk %d\n",
			       pg_idx_in_blk, src_blk_id, pg_idx_in_blk);

//			if (pg_idx_in_buf < 5) bbt_dump_buf("read fip data", pg_buf, pg_sz);
		status = cvsnfc_read_page(host->mtd, host->chip, (void *)pg_buf, pg_sz,
					  (src_blk_id << sv->spi_nand_info.pages_per_block_shift) + pg_idx_in_blk);

		if (status < 0) {
			printf("Read failed, please check. STOP!\n");
			ret = -1;
			goto bailout;
		}

		if (DEBUG_WRITE)
			printf("write fip.bin page idx %d, dst_blk_id %d,  pg_idx_in_blk %d\n",
			       pg_idx_in_blk, dst_blk_id, pg_idx_in_blk);

		status = cvsnfc_write_page(host->mtd, host->chip, (void *)pg_buf, 0,
					   (dst_blk_id << sv->spi_nand_info.pages_per_block_shift) + pg_idx_in_blk);

		if (status < 0) {
			printf("write failed, please check. STOP!\n");
			ret = -1;
			goto bailout;
		}
	}

	get_spi_nand_info();
	spi_nand_flush_vec();

bailout:
	return ret;
}

/*
 * check first copy, if corrupted, alloc new blocks
 * and move 2nd copy to new blocks
 */
int check_and_update_fip_bin(void)
{
	struct _spi_nand_base_vector_t *sv = g_spi_nand_sys_vec;
	struct cvsnfc_host *host = cvsnfc_get_host();
	int status = 0;
	int fip_damage = 0;
	int *fip_sts = NULL;
	int damaged_blk_cnt = 0;

	status = spi_nand_scan_vector();

	if (status < 0)
		return 0;

	fip_sts = (int *)malloc(sv->fip_bin_blk_cnt * sizeof(int));

	if (!fip_sts)
		return -1;

	memset(fip_sts, 0, sv->fip_bin_blk_cnt * sizeof(int));

	u32 pg_sz = sv->spi_nand_info.page_size;
	u32 ttl_pg_cnt_to_check = PLAT_BM_FIP_MAX_CHECK_SIZE / pg_sz;
	u32 pg_per_blk = sv->spi_nand_info.pages_per_block;

	if (DEBUG_READ)
		printf("pg_sz %d ttl_pg_cnt_to_check %d, pg_per_blk %d\n", pg_sz, ttl_pg_cnt_to_check, pg_per_blk);

	for (u32 pg_idx_in_buf = 0; pg_idx_in_buf < ttl_pg_cnt_to_check; pg_idx_in_buf++) {
		u32 pg_idx_in_blk = GET_PG_IDX_IN_BLK(pg_idx_in_buf, pg_per_blk);
		u32 blk_idx = GET_BLK_IDX(pg_idx_in_buf, pg_per_blk);

		u16 blk_id = sv->fip_bin_blks[0][blk_idx];

		cvi_assert(blk_id < MAX_BLOCK_CNT);

		if (blk_idx == 0 && pg_idx_in_blk == 0)
			pr_debug("Read fip.bin page idx %d, blk_id %d\n", pg_idx_in_blk, blk_id);

		status = cvsnfc_read_page(host->mtd, host->chip, (void *)pg_buf, pg_sz,
					  (blk_id << sv->spi_nand_info.pages_per_block_shift) + pg_idx_in_blk);

		if (status) {
			printf("Read ECC %s\n", (status < 0) ? "UNCC" : "CORR");
			printf("fip page idx %d, blk_id %d\n", pg_idx_in_blk, blk_id);

			// replace blocks only when UNCORR ECC occur
			if (status < 0) {
				printf("Got UNCORR ECC\n");
				fip_damage = 1;
				// move pg_idx_in_buf to the end of current block
				printf("org pg_idx_in_buf %d\n", pg_idx_in_buf);
				pg_idx_in_buf = rounddown(pg_idx_in_buf, pg_per_blk);
				pg_idx_in_buf += pg_per_blk;
				pg_idx_in_buf--;
				printf("new pg_idx_in_buf %d\n", pg_idx_in_buf);

				fip_sts[blk_idx] = 1;
				damaged_blk_cnt++;
			}
		}
	}

	if (fip_damage) {
		printf("damaged_blk_cnt %d\n", damaged_blk_cnt);
		status = update_fip_data(host, fip_sts, damaged_blk_cnt);
	}

	free(fip_sts);

	return status;
}

#define FIP_BIN_SIGNATURE (0xAA640001)

static int spi_nand_flush_fip_bin(void *buf)
{
	int status = 0;
	void *buffer = (void *)buf;
	void *src_buf_addr = 0;
	struct _spi_nand_base_vector_t *sv = g_spi_nand_sys_vec;
	struct cvsnfc_host *host = cvsnfc_get_host();
	u32 pg_sz = sv->spi_nand_info.page_size;
	u32 ttl_pg_cnt_to_write = PLAT_BM_FIP_MAX_SIZE / pg_sz;
	u32 pg_per_blk = sv->spi_nand_info.pages_per_block;
	u32 *sig = (u32 *)buf;

	cvi_assert(*sig == FIP_BIN_SIGNATURE);

	printf("%s, fip bin pg cnt %d, sig %#x, %#x\n", __func__, sv->fip_bin_blk_cnt, *sig, FIP_BIN_SIGNATURE);
	printf("pg_sz %d ttl_pg_cnt_to_write %d, pg_per_blk %d\n", pg_sz, ttl_pg_cnt_to_write, pg_per_blk);

	for (u32 i = 0; i < SPI_NAND_BASE_DATA_BACKUP_COPY; i++) {

		for (u32 j = 0; j < SPI_NAND_FIP_DATA_BLOCK_COUNT ; j++) {
			u32 blk_id = sv->fip_bin_blks[i][j];

			assert(blk_id <= MAX_BLOCK_CNT);

			if (blk_id == 0) {
				// fip.bin never in block 0, it means empty block slot
				continue;
			}

			if (blk_id >= MAX_BLOCK_CNT) {
				printf("Wrong erase blk id %d\n", blk_id);
				assert(0);
			}

			printf("erase blk id %d\n", blk_id);

			uint32_t pg = blk_id << sv->spi_nand_info.pages_per_block_shift;
			host->addr_value[1] = pg;
			cvsnfc_send_cmd_erase(host);

			if (status) {
				printf("erase error\n");
				return status;
			}
		}

		printf("write %d copy of fip\n", i);


		for (u32 pg_idx_in_buf = 0; pg_idx_in_buf < ttl_pg_cnt_to_write; pg_idx_in_buf++) {
			u32 pg_idx_in_blk = GET_PG_IDX_IN_BLK(pg_idx_in_buf, pg_per_blk);
			u32 blk_idx = GET_BLK_IDX(pg_idx_in_buf, pg_per_blk);

			u32 offset_in_buf = pg_idx_in_buf * pg_sz;

			u32 blk_id = sv->fip_bin_blks[i][blk_idx];

			src_buf_addr = PTR_INC(buffer, offset_in_buf);

			if (DEBUG_WRITE)
				printf("flush fip.bin page idx %d, blk_id %d, src buf addr %p\n",
				       pg_idx_in_blk, blk_id, src_buf_addr);

			status = cvsnfc_write_page(host->mtd, host->chip, (void *)src_buf_addr, 0,
						   (blk_id << sv->spi_nand_info.pages_per_block_shift) + pg_idx_in_blk);

			if (status) {
				printf("Write fail\n");
				return status;
			}
		}
	}

	verify_fip_bin(buf);

	return 0;
}

int spi_nand_flush_vec(void)
{
	int status = 0;
	struct _spi_nand_base_vector_t *sv = g_spi_nand_sys_vec;
	struct _spi_nand_info *info = &spinand_info;
	struct cvsnfc_host *host = cvsnfc_get_host();
	u32 verify_vec_write_fail = 0;

#ifdef NANDBOOT_V2
	sv->crc = crc16_ccitt(0, sv, (uintptr_t)&sv->crc - (uintptr_t)sv);
	printf("[SPI_NAND][BASE] sv->crc:%d\n", sv->crc);
#endif

	spi_nand_dump_vec();

	for (u32 i = 0; i < SPI_NAND_BASE_DATA_BACKUP_COPY; i++) {
		u32 blk_id = sv->spi_nand_vector_blks[i];
		uint32_t pg = blk_id << info->pages_per_block_shift;

		if (DEBUG_ERASE)
			printf("erase blk %d\n", blk_id);

		host->addr_value[1] = pg;
		cvsnfc_send_cmd_erase(host);

		for (u32 j = 0; j < sv->spi_nand_info.pages_per_block; j++) {
			cvsnfc_write_page(host->mtd, host->chip, (void *)sv, 0,
					  (blk_id << info->pages_per_block_shift) + j);

			status = cvsnfc_read_page(host->mtd, host->chip, (void *)pg_buf, info->page_size,
						  (blk_id << info->pages_per_block_shift) + j);

			if (status < 0) {
				printf("spi nand sv read back fail\n");
				verify_vec_write_fail = 1;
				goto bailout;
			}
		}
	}

bailout:
	if (verify_vec_write_fail)
		printf("verify_vec_write_fail\n");
	else
		printf("vec write pass!\n");

	return 0;
}

void spi_nand_dump_vec(void)
{
	u32 i = 0, j = 0;
	struct _spi_nand_base_vector_t *sv = g_spi_nand_sys_vec;

	printf("%s\n", __func__);
	printf("signature: 0x%x\n", sv->signature);
	printf("version 0x%x\n", sv->version);

	for (i = 0; i < SPI_NAND_BASE_DATA_BACKUP_COPY; i++)
		printf("spi_nand_vec_blks 0x%x\n", sv->spi_nand_vector_blks[i]);

	printf("fip_bin_blk_cnt 0x%x\n", sv->fip_bin_blk_cnt);

	for (i = 0; i < SPI_NAND_BASE_DATA_BACKUP_COPY; i++) {
		for (j = 0; j < SPI_NAND_FIP_DATA_BLOCK_COUNT; j++)
			printf("fip bin blks 0x%x\n", sv->fip_bin_blks[i][j]);
	}

	printf("spi nand info block cnt 0x%x\n", sv->spi_nand_info.block_cnt);
	printf("spi nand info id 0x%x\n", sv->spi_nand_info.id);
	printf("spi nand info pages per block 0x%x\n", sv->spi_nand_info.pages_per_block);
	printf("spi nand info pages per block shift 0x%x\n", sv->spi_nand_info.pages_per_block_shift);
	printf("spi nand info page size 0x%x\n", sv->spi_nand_info.page_size);
	printf("spi nand info spare size 0x%x\n", sv->spi_nand_info.spare_size);

	bbt_dump_buf((void *)"spi nand base block usage", sv->spi_nand_base_block_usage, 4);
}

int spi_nand_check_write_vector(void *buf)
{
	int status;

	printf("%s!!\n", __func__);
	get_spi_nand_info();

	status = spi_nand_scan_vector();

	if (status == 0) {
		struct _spi_nand_base_vector_t *sv = g_spi_nand_sys_vec;

		status = spi_nand_flush_fip_bin(buf);

		if (status) {
			printf("flush fip bin failed!, please check!\n");
			return -1;
		}

		sv->erase_count++;
		printf("sv->erase_count %d\n", sv->erase_count);

		if (sv->version != SPI_NAND_VECTOR_VERSION) {
			printf("update sv & fip version to 0x%x\n", SPI_NAND_VECTOR_VERSION);
			sv->version = SPI_NAND_VECTOR_VERSION;
		}

		status = spi_nand_flush_vec();

		if (status) {
			printf("flus vec failed!, please check!\n");
			return -1;
		}
	} else {
		// can't find vec

		status = spi_nand_scan_defect();
		if (status) {
			printf("scan factory error\n");
			return -1;
		}

		status = init_spi_nand_vect();
		if (status) {
			printf("init spi_nand vect error\n");
			return -1;
		}

		status = spi_nand_flush_fip_bin(buf);
		if (status)
			printf("flush fip error\n");

		status = spi_nand_flush_vec();

		if (status) {
			printf("spi_nand_flush_vec failed!");
			return -1;
		}
	}
	return 0;
}

int do_cvi_update_spinand(uint32_t component, void *addr)
{
	printf("do_cvi_update_spinand com 0x%x\n", component);

	spi_nand_check_write_vector(addr);

	return 0;
}

#endif /* CONFIG_NAND_FLASH_CVSNFC */
