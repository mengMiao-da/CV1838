#include <common.h>
#include <command.h>
#include <stdlib.h>
#include <stdarg.h>
#include <malloc.h>
#include <linux/arm-smccc.h>
#include <cvi_efuse.h>

#define EFUSE_DEBUG 0

#define OPTEE_SMC_CALL_CV_EFUSE_READ 0x03000006
#define OPTEE_SMC_CALL_CV_EFUSE_WRITE 0x03000007

enum CVI_EFUSE_LOCK_WRITE_E {
	CVI_EFUSE_LOCK_WRITE_HASH0_PUBLIC = CVI_EFUSE_OTHERS + 1,
	CVI_EFUSE_LOCK_WRITE_LOADER_EK,
	CVI_EFUSE_LOCK_WRITE_DEVICE_EK,
	CVI_EFUSE_LOCK_WRITE_LAST
};

#define _cc_trace(fmt, ...) __trace("", __FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)
#define _cc_error(fmt, ...) __trace("ERROR:", __FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)

#if EFUSE_DEBUG
static int __trace(const char *prefix, const char *path, const char *func, int lineno, const char *fmt, ...)
{
	va_list ap;
	int ret;

	printf("[%s%s:%s:%d] ", prefix, path, func, lineno);
	if (!fmt || fmt[0] == '\0') {
		ret = printf("\n");
	} else {
		va_start(ap, fmt);
		ret = vprintf(fmt, ap);
		va_end(ap);
	}

	return ret;
}
#else
static int __trace(const char *prefix, const char *path, const char *func, int lineno, const char *fmt, ...)
{
	return 0;
}
#endif

static int hex2bytes(const char *hex, unsigned char *buf, int buf_size)
{
	int i, total = 0;
	char tmp[3];

	memset(buf, 0, buf_size);

	for (i = 0; i < buf_size; i++) {
		if (!hex[0] || !hex[1])
			break;

		tmp[0] = hex[0];
		tmp[1] = hex[1];
		tmp[2] = '\0';

		buf[i] = simple_strtoul(tmp, NULL, 16);
		hex += 2;
		total += 1;
	}

	return total;
}

// ===========================================================================
// EFUSE API
// ===========================================================================
static struct _CVI_EFUSE_AREA_S {
	CVI_U32 addr;
	CVI_U32 size;
} cvi_efuse_area[] = { [CVI_EFUSE_AREA_USER] = { 0x40, 40 },
		       [CVI_EFUSE_AREA_DEVICE_ID] = { 0x8c, 8 },
		       [CVI_EFUSE_AREA_HASH0_PUBLIC] = { 0xA8, 32 },
		       [CVI_EFUSE_AREA_LOADER_EK] = { 0xD8, 16 },
		       [CVI_EFUSE_AREA_DEVICE_EK] = { 0xE8, 16 } };

static struct _CVI_EFUSE_LOCK_S {
	CVI_S32 wlock_shift;
	CVI_S32 rlock_shift;
} cvi_efuse_lock[] = { [CVI_EFUSE_LOCK_HASH0_PUBLIC] = { 0, 8 },
		       [CVI_EFUSE_LOCK_LOADER_EK] = { 4, 12 },
		       [CVI_EFUSE_LOCK_DEVICE_EK] = { 6, 14 },
		       [CVI_EFUSE_LOCK_WRITE_HASH0_PUBLIC] = { 0, -1 },
		       [CVI_EFUSE_LOCK_WRITE_LOADER_EK] = { 4, -1 },
		       [CVI_EFUSE_LOCK_WRITE_DEVICE_EK] = { 6, -1 } };

static struct _CVI_EFUSE_USER_S {
	CVI_U32 addr;
	CVI_U32 size;
} cvi_efuse_user[] = {
	{ 0x40, 4 }, { 0x48, 4 }, { 0x50, 4 }, { 0x58, 4 }, { 0x60, 4 },
	{ 0x68, 4 }, { 0x70, 4 }, { 0x78, 4 }, { 0x80, 4 }, { 0x88, 4 },
};

#define CVI_EFUSE_TOTAL_SIZE 0x100

#define CVI_EFUSE_LOCK_ADDR 0xF8
#define CVI_EFUSE_SECURE_CONF_ADDR 0xA0
#define CVI_EFUSE_SCS_ENABLE_SHIFT 0

CVI_S32 CVI_EFUSE_GetSize(enum CVI_EFUSE_AREA_E area, CVI_U32 *size)
{
	if (area >= ARRAY_SIZE(cvi_efuse_area) || cvi_efuse_area[area].size == 0) {
		_cc_error("area (%d) is not found\n", area);
		return CVI_ERR_EFUSE_INVALID_AREA;
	}

	if (size)
		*size = cvi_efuse_area[area].size;

	return 0;
}

static CVI_S32 _CVI_EFUSE_Read(CVI_U32 addr, void *buf, CVI_U32 buf_size)
{
	CVI_S32 ret = -1;
	struct arm_smccc_res res = { 0 };
	struct arm_smccc_quirk quirk = { 0 };

	_cc_trace("addr=0x%02x\n", addr);

	if (!buf)
		return CVI_ERR_EFUSE_INVALID_PARA;

	flush_dcache_all();
	__arm_smccc_smc(OPTEE_SMC_CALL_CV_EFUSE_READ, addr, buf_size, (unsigned long)buf, 0, 0, 0, 0, &res, &quirk);

	ret = res.a0;

	return ret;
}

static CVI_S32 _CVI_EFUSE_Write(CVI_U32 addr, const void *buf, CVI_U32 buf_size)
{
	_cc_trace("addr=0x%02x\n", addr);

	CVI_S32 ret = -1;
	struct arm_smccc_res res = { 0 };
	struct arm_smccc_quirk quirk = { 0 };

	CVI_U32 value;
	CVI_U32 aligned_addr = addr;
	CVI_U32 aligned_size = buf_size;
	void *aligned_buf = NULL;
	int i;

	if (!buf)
		return CVI_ERR_EFUSE_INVALID_PARA;

	if (aligned_addr % 4)
		aligned_addr -= aligned_addr % 4;

	if (aligned_size % 4)
		aligned_size += 4 - aligned_size % 4;

	aligned_buf = malloc(aligned_size);
	memset(aligned_buf, 0, aligned_size);
	memcpy(aligned_buf + (addr - aligned_addr), buf, buf_size);

	for (i = 0; i < aligned_size; i += 4) {
		memcpy(&value, aligned_buf + i, sizeof(value));
		_cc_trace("smc call: 0x%02x=0x%08x\n", addr + i, value);
		__arm_smccc_smc(OPTEE_SMC_CALL_CV_EFUSE_WRITE, addr + i, value, 0, 0, 0, 0, 0, &res, &quirk);
		ret = res.a0;
		if (ret < 0) {
			printf("_CVI_EFUSE_Write error (%d)\n", ret);
			return ret;
		}
	}

	return 0;
}

CVI_S32 CVI_EFUSE_Read(enum CVI_EFUSE_AREA_E area, CVI_U8 *buf, CVI_U32 buf_size)
{
	CVI_U32 user_size = cvi_efuse_area[CVI_EFUSE_AREA_USER].size;
	CVI_U8 user[user_size], *p;
	CVI_S32 ret;
	int i;

	if (area >= ARRAY_SIZE(cvi_efuse_area) || cvi_efuse_area[area].size == 0) {
		_cc_error("area (%d) is not found\n", area);
		return CVI_ERR_EFUSE_INVALID_AREA;
	}

	if (!buf)
		return CVI_ERR_EFUSE_INVALID_PARA;

	memset(buf, 0, buf_size);

	if (buf_size > cvi_efuse_area[area].size)
		buf_size = cvi_efuse_area[area].size;

	if (area != CVI_EFUSE_AREA_USER)
		return _CVI_EFUSE_Read(cvi_efuse_area[area].addr, buf, buf_size);

	memset(user, 0, user_size);

	p = user;
	for (i = 0; i < ARRAY_SIZE(cvi_efuse_user); i++) {
		ret = _CVI_EFUSE_Read(cvi_efuse_user[i].addr, p, cvi_efuse_user[i].size);
		if (ret < 0)
			return ret;
		p += cvi_efuse_user[i].size;
	}

	memcpy(buf, user, buf_size);

	return CVI_SUCCESS;
}

CVI_S32 CVI_EFUSE_Write(enum CVI_EFUSE_AREA_E area, const CVI_U8 *buf, CVI_U32 buf_size)
{
	CVI_U32 user_size = cvi_efuse_area[CVI_EFUSE_AREA_USER].size;
	CVI_U8 user[user_size], *p;
	CVI_S32 ret;
	int i;

	if (area >= ARRAY_SIZE(cvi_efuse_area) || cvi_efuse_area[area].size == 0) {
		_cc_error("area (%d) is not found\n", area);
		return CVI_ERR_EFUSE_INVALID_AREA;
	}
	if (!buf)
		return CVI_ERR_EFUSE_INVALID_PARA;

	if (buf_size > cvi_efuse_area[area].size)
		buf_size = cvi_efuse_area[area].size;

	if (area != CVI_EFUSE_AREA_USER)
		return _CVI_EFUSE_Write(cvi_efuse_area[area].addr, buf, buf_size);

	memset(user, 0, user_size);
	memcpy(user, buf, buf_size);

	p = user;
	for (i = 0; i < ARRAY_SIZE(cvi_efuse_user); i++) {
		ret = _CVI_EFUSE_Write(cvi_efuse_user[i].addr, p, cvi_efuse_user[i].size);
		if (ret < 0)
			return ret;
		p += cvi_efuse_user[i].size;
	}

	return CVI_SUCCESS;
}

CVI_S32 CVI_EFUSE_EnableSecureBoot(void)
{
	CVI_U32 value = 0x3 << CVI_EFUSE_SCS_ENABLE_SHIFT;

	return _CVI_EFUSE_Write(CVI_EFUSE_SECURE_CONF_ADDR, &value, sizeof(value));
}

CVI_S32 CVI_EFUSE_IsSecureBootEnabled(void)
{
	CVI_U32 value = 0;
	CVI_S32 ret = 0;

	ret = _CVI_EFUSE_Read(CVI_EFUSE_SECURE_CONF_ADDR, &value, sizeof(value));
	_cc_trace("ret=%d value=%u\n", ret, value);
	if (ret < 0)
		return ret;

	value &= 0x3 << CVI_EFUSE_SCS_ENABLE_SHIFT;
	return !!value;
}

CVI_S32 CVI_EFUSE_Lock(enum CVI_EFUSE_LOCK_E lock)
{
	CVI_U32 value = 0;
	CVI_U32 ret = 0;

	if (lock >= ARRAY_SIZE(cvi_efuse_lock)) {
		_cc_error("lock (%d) is not found\n", lock);
		return CVI_ERR_EFUSE_INVALID_AREA;
	}

	value = 0x3 << cvi_efuse_lock[lock].wlock_shift;
	ret = _CVI_EFUSE_Write(CVI_EFUSE_LOCK_ADDR, &value, sizeof(value));
	if (ret < 0)
		return ret;

	if (cvi_efuse_lock[lock].rlock_shift >= 0) {
		value = 0x3 << cvi_efuse_lock[lock].rlock_shift;
		ret = _CVI_EFUSE_Write(CVI_EFUSE_LOCK_ADDR, &value, sizeof(value));
	}

	return ret;
}

CVI_S32 CVI_EFUSE_IsLocked(enum CVI_EFUSE_LOCK_E lock)
{
	CVI_S32 ret = 0;
	CVI_U32 value = 0;

	if (lock >= ARRAY_SIZE(cvi_efuse_lock)) {
		_cc_error("lock (%d) is not found\n", lock);
		return CVI_ERR_EFUSE_INVALID_AREA;
	}

	ret = _CVI_EFUSE_Read(CVI_EFUSE_LOCK_ADDR, &value, sizeof(value));
	_cc_trace("ret=%d value=%u\n", ret, value);
	if (ret < 0)
		return ret;

	value &= 0x3 << cvi_efuse_lock[lock].wlock_shift;
	return !!value;
}

CVI_S32 CVI_EFUSE_LockWrite(enum CVI_EFUSE_LOCK_E lock)
{
	CVI_U32 value = 0;
	CVI_S32 ret = 0;

	if (lock >= ARRAY_SIZE(cvi_efuse_lock)) {
		_cc_error("lock (%d) is not found\n", lock);
		return CVI_ERR_EFUSE_INVALID_AREA;
	}

	value = 0x3 << cvi_efuse_lock[lock].wlock_shift;
	ret = _CVI_EFUSE_Write(CVI_EFUSE_LOCK_ADDR, &value, sizeof(value));
	return ret;
}

CVI_S32 CVI_EFUSE_IsWriteLocked(enum CVI_EFUSE_LOCK_E lock)
{
	CVI_S32 ret = 0;
	CVI_U32 value = 0;

	if (lock >= ARRAY_SIZE(cvi_efuse_lock)) {
		_cc_error("lock (%d) is not found\n", lock);
		return CVI_ERR_EFUSE_INVALID_AREA;
	}

	ret = _CVI_EFUSE_Read(CVI_EFUSE_LOCK_ADDR, &value, sizeof(value));
	_cc_trace("ret=%d value=%u\n", ret, value);
	if (ret < 0)
		return ret;

	value &= 0x3 << cvi_efuse_lock[lock].wlock_shift;
	return !!value;
}

static const char *const efuse_index[] = {
	[CVI_EFUSE_AREA_USER] = "USER",
	[CVI_EFUSE_AREA_DEVICE_ID] = "DEVICE_ID",
	[CVI_EFUSE_AREA_HASH0_PUBLIC] = "HASH0_PUBLIC",
	[CVI_EFUSE_AREA_LOADER_EK] = "LOADER_EK",
	[CVI_EFUSE_AREA_DEVICE_EK] = "DEVICE_EK",
	[CVI_EFUSE_LOCK_HASH0_PUBLIC] = "LOCK_HASH0_PUBLIC",
	[CVI_EFUSE_LOCK_LOADER_EK] = "LOCK_LOADER_EK",
	[CVI_EFUSE_LOCK_DEVICE_EK] = "LOCK_DEVICE_EK",
	[CVI_EFUSE_LOCK_WRITE_HASH0_PUBLIC] = "LOCK_WRITE_HASH0_PUBLIC",
	[CVI_EFUSE_LOCK_WRITE_LOADER_EK] = "LOCK_WRITE_LOADER_EK",
	[CVI_EFUSE_LOCK_WRITE_DEVICE_EK] = "LOCK_WRITE_DEVICE_EK",
	[CVI_EFUSE_SECUREBOOT] = "SECUREBOOT",
};

static int find_efuse_by_name(const char *name)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(efuse_index); i++) {
		if (!efuse_index[i])
			continue;

		if (!strcmp(name, efuse_index[i]))
			return i;
	}

	return -1;
}

static int do_efuser(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
	int idx;
	int ret;
	unsigned int size;
	unsigned char buf[128];

	if (argc != 2)
		return CMD_RET_USAGE;

	_cc_trace("Read eFuse: %s\n", argv[1]);
	idx = find_efuse_by_name(argv[1]);
	if (idx < 0)
		return CMD_RET_USAGE;

	_cc_trace("idx=%d %s\n", idx, efuse_index[idx]);

	if (idx < CVI_EFUSE_AREA_LAST) {
		if (CVI_EFUSE_GetSize(idx, &size) < 0)
			return CMD_RET_FAILURE;

		_cc_trace("size=%d\n", size);

		if (CVI_EFUSE_Read(idx, buf, size) < 0)
			return CMD_RET_FAILURE;

		print_buffer(0, buf, 1, size, 0);
		return 0;
	} else if (idx < CVI_EFUSE_LOCK_LAST) {
		ret = CVI_EFUSE_IsLocked(idx);
		printf("%s is %s locked\n", efuse_index[idx], ret ? "" : "not");
		return 0;
	} else if (idx < CVI_EFUSE_LOCK_WRITE_LAST) {
		ret = CVI_EFUSE_IsWriteLocked(idx);
		printf("%s is %s write_locked\n", efuse_index[idx], ret ? "" : "not");
		return 0;
	} else if (idx == CVI_EFUSE_SECUREBOOT) {
		ret = CVI_EFUSE_IsSecureBootEnabled();
		printf("Secure Boot is %s\n", ret ? "enabled" : "disabled");
		return 0;
	}

	return CMD_RET_FAILURE;
}

static int do_efusew(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
	int idx;
	int ret;
	unsigned int size;
	unsigned char buf[128] = { 0 };

	_cc_trace("argc=%d\n", argc);

	if (argc != 2 && argc != 3)
		return CMD_RET_USAGE;

	_cc_trace("Write eFuse: %s=%s\n", argv[1], argv[2]);
	idx = find_efuse_by_name(argv[1]);
	if (idx < 0)
		return CMD_RET_USAGE;

	_cc_trace("idx=%d %s\n", idx, efuse_index[idx]);
	printf("Write eFuse %s(%d) with:\n", efuse_index[idx], idx);

	if (idx < CVI_EFUSE_AREA_LAST) {
		if (argc != 3)
			return CMD_RET_USAGE;

		size = hex2bytes(argv[2], buf, sizeof(buf));
		if (size <= 0)
			return CMD_RET_USAGE;

		print_buffer(0, buf, 1, size, 0);

		if (CVI_EFUSE_GetSize(idx, &size) < 0)
			return CMD_RET_FAILURE;

		_cc_trace("size=%d\n", size);

		ret = CVI_EFUSE_Write(idx, buf, size);
		if (ret < 0) {
			printf("Failed to write %s\n", efuse_index[idx]);
			return CMD_RET_FAILURE;
		}

		return 0;

	} else if (idx < CVI_EFUSE_LOCK_LAST) {
		if (CVI_EFUSE_Lock(idx) < 0) {
			printf("Failed to lock %s\n", efuse_index[idx]);
			return CMD_RET_FAILURE;
		}

		printf("%s is locked\n", efuse_index[idx]);
		return 0;
	} else if (idx < CVI_EFUSE_LOCK_WRITE_LAST) {
		if (CVI_EFUSE_LockWrite(idx) < 0) {
			printf("Failed to lock write %s\n", efuse_index[idx]);
			return CMD_RET_FAILURE;
		}

		printf("%s is locked\n", efuse_index[idx]);
		return 0;


	} else if (idx == CVI_EFUSE_SECUREBOOT) {
		ret = CVI_EFUSE_EnableSecureBoot();
		printf("Enabled Secure Boot is %s\n", ret >= 0 ? "success" : "failed");
		return 0;
	}

	return CMD_RET_FAILURE;
}

U_BOOT_CMD(efuser, 9, 1, do_efuser, "Read efuse",
	   "[args..]\n"
	   "    - args ...");

U_BOOT_CMD(efusew, 9, 1, do_efusew, "Write efuse",
	   "[args..]\n"
	   "    - args ...");

static int do_smc(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
	int i;
	unsigned long a[64] = { 0 };
	struct arm_smccc_res res = { 0 };
	struct arm_smccc_quirk quirk = { 0 };

	printf("%s: argc=%d\n", __func__, argc);

	for (i = 0; i < argc - 1; i++) {
		char *p = argv[i + 1];

		a[i] = simple_strtoul(p, NULL, 0);
		printf("%d: 0x%08lx\n", i, a[i]);
	}

	flush_dcache_all();

	printf("%s: call\n", __func__);
	__arm_smccc_smc(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], &res, &quirk);

	printf("%s: res=0x%08lx 0x%08lx 0x%08lx 0x%08lx\n", __func__, res.a0, res.a1, res.a2, res.a3);
	return 0;
}

U_BOOT_CMD(smc, 9, 1, do_smc, "smc args to TEE",
	   "[args..]\n"
	   "    - args ...");
