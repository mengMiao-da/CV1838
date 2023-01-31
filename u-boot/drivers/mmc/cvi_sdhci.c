/*
 * Copyright (C) 2016 Socionext Inc.
 *   Author: Masahiro Yamada <yamada.masahiro@socionext.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <dm.h>
#include <linux/io.h>
#include <linux/iopoll.h>
#include <linux/sizes.h>
#include <libfdt.h>
#include <reset.h>
#include <mmc.h>
#include <sdhci.h>

#ifdef DEBUG
#define pr_debug(fmt, ...) \
	printf(fmt, ##__VA_ARGS__)
#else
#define pr_debug(fmt, ...)
#endif

struct cvi_sdhci_plat {
	struct mmc_config cfg;
	struct mmc mmc;
};

struct cvi_sdhci_host {
	struct sdhci_host host;
	int pll_index;
	int pll_reg;
	int has_phy;
	int is_64_addressing;
	int reset_tx_rx_phy;
	uint32_t mmc_init_freq;
	uint32_t mmc_trans_freq;
	struct reset_ctl reset_ctl;
};

#ifdef CONFIG_TARGET_CVITEK_CV1822
void cvi_emmc_pad_setting(void)
{
	mmio_clrsetbits_32(REG_EMMC_CLK_PAD_REG, REG_EMMC_PAD_CLR_MASK, REG_EMMC_CLK_PAD_VALUE << REG_EMMC_PAD_SHIFT);

	mmio_clrsetbits_32(REG_EMMC_RSTN_PAD_REG, REG_EMMC_PAD_CLR_MASK, REG_EMMC_RSTN_PAD_VALUE << REG_EMMC_PAD_SHIFT);

	mmio_clrsetbits_32(REG_EMMC_CMD_PAD_REG, REG_EMMC_PAD_CLR_MASK, REG_EMMC_CMD_PAD_VALUE << REG_EMMC_PAD_SHIFT);

	mmio_clrsetbits_32(REG_EMMC_DAT1_PAD_REG, REG_EMMC_PAD_CLR_MASK, REG_EMMC_DAT1_PAD_VALUE << REG_EMMC_PAD_SHIFT);

	mmio_clrsetbits_32(REG_EMMC_DAT0_PAD_REG, REG_EMMC_PAD_CLR_MASK, REG_EMMC_DAT0_PAD_VALUE << REG_EMMC_PAD_SHIFT);

	mmio_clrsetbits_32(REG_EMMC_DAT2_PAD_REG, REG_EMMC_PAD_CLR_MASK, REG_EMMC_DAT2_PAD_VALUE << REG_EMMC_PAD_SHIFT);

	mmio_clrsetbits_32(REG_EMMC_DAT3_PAD_REG, REG_EMMC_PAD_CLR_MASK, REG_EMMC_DAT3_PAD_VALUE << REG_EMMC_PAD_SHIFT);
}

static void cvi_sdio1_pad_setting(void)
{
	mmio_clrsetbits_32(REG_SDIO1_CLK_PAD_REG, REG_SDIO1_PAD_CLR_MASK,
			   REG_SDIO1_CLK_PAD_VALUE << REG_SDIO1_PAD_SHIFT);

	mmio_clrsetbits_32(REG_SDIO1_CMD_PAD_REG, REG_SDIO1_PAD_CLR_MASK,
			   REG_SDIO1_CMD_PAD_VALUE << REG_SDIO1_PAD_SHIFT);

	mmio_clrsetbits_32(REG_SDIO1_DAT1_PAD_REG, REG_SDIO1_PAD_CLR_MASK,
			   REG_SDIO1_DAT1_PAD_VALUE << REG_SDIO1_PAD_SHIFT);

	mmio_clrsetbits_32(REG_SDIO1_DAT0_PAD_REG, REG_SDIO1_PAD_CLR_MASK,
			   REG_SDIO1_DAT0_PAD_VALUE << REG_SDIO1_PAD_SHIFT);

	mmio_clrsetbits_32(REG_SDIO1_DAT2_PAD_REG, REG_SDIO1_PAD_CLR_MASK,
			   REG_SDIO1_DAT2_PAD_VALUE << REG_SDIO1_PAD_SHIFT);

	mmio_clrsetbits_32(REG_SDIO1_DAT3_PAD_REG, REG_SDIO1_PAD_CLR_MASK,
			   REG_SDIO1_DAT3_PAD_VALUE << REG_SDIO1_PAD_SHIFT);
}
#endif

static int cvi_ofdata_to_platdata(struct udevice *dev)
{
	struct cvi_sdhci_host *cvi_host = dev_get_priv(dev);
	struct sdhci_host *host = &cvi_host->host;
	int node = dev_of_offset(dev);
	int rtc_sdio1 = fdtdec_get_uint(gd->fdt_blob, node, "rtc_sdio1", 0);

	host->name = strdup(dev->name);
	host->ioaddr = (void *)devfdt_get_addr(dev);
	host->bus_width = fdtdec_get_int(gd->fdt_blob, node, "bus-width", 4);
	host->index = fdtdec_get_uint(gd->fdt_blob, node, "index", 0);
	host->max_clk = fdtdec_get_uint(gd->fdt_blob, node, "max-frequency", 0);

	cvi_host->mmc_init_freq = fdtdec_get_uint(gd->fdt_blob, node, "mmc_init_freq", 200000);
	cvi_host->mmc_trans_freq = fdtdec_get_uint(gd->fdt_blob, node, "mmc_trans_freq", 0);
	cvi_host->is_64_addressing = fdtdec_get_bool(gd->fdt_blob, node, "64_addressing");
	cvi_host->reset_tx_rx_phy = fdtdec_get_bool(gd->fdt_blob, node, "reset_tx_rx_phy");
	cvi_host->has_phy = fdtdec_get_bool(gd->fdt_blob, node, "has_phy");
	cvi_host->pll_index = fdtdec_get_uint(gd->fdt_blob, node, "pll_index", 0);
	cvi_host->pll_reg = fdtdec_get_uint(gd->fdt_blob, node, "pll_reg", 0);

	if (rtc_sdio1) {
		// set rtc sdio1 related register
		writel(0x1, 0x03000248);
		writel(0x10, 0x0502501c);
		writel(0xfffffffc, 0x05025030);
		//writel(0x0, 0x0502507c);
	}

	if (host->ioaddr == (void *)FDT_ADDR_T_NONE)
		return -EINVAL;

	return 0;
}

static int cvi_sdhci_bind(struct udevice *dev)
{
	struct cvi_sdhci_plat *plat = dev_get_platdata(dev);

	pr_debug("[hq] %s\n", __func__);
	return sdhci_bind(dev, &plat->mmc, &plat->cfg);
}

/* TODO */
static int cvi_sdhci_phy_init(struct cvi_sdhci_host *cvi_host)
{
	struct sdhci_host *host = &cvi_host->host;

	// Asset reset of phy
	sdhci_writel(host, sdhci_readl(host, SDHCI_P_PHY_CNFG) & ~(1 << PHY_CNFG_PHY_RSTN), SDHCI_P_PHY_CNFG);

	// Set PAD_SN PAD_SP
	sdhci_writel(host, (1 << PHY_CNFG_PHY_PWRGOOD) | (0x9 << PHY_CNFG_PAD_SP) | (0x8 << PHY_CNFG_PAD_SN), SDHCI_P_PHY_CNFG);

	// Set CMDPAD
	sdhci_writew(host, (0x2 << PAD_CNFG_RXSEL) | (1 << PAD_CNFG_WEAKPULL_EN) |
			(0x3 << PAD_CNFG_TXSLEW_CTRL_P) | (0x2 << PAD_CNFG_TXSLEW_CTRL_N), SDHCI_P_CMDPAD_CNFG);

	// Set DATAPAD
	sdhci_writew(host, (0x2 << PAD_CNFG_RXSEL) | (1 << PAD_CNFG_WEAKPULL_EN) |
			(0x3 << PAD_CNFG_TXSLEW_CTRL_P) | (0x2 << PAD_CNFG_TXSLEW_CTRL_N), SDHCI_P_DATPAD_CNFG);

	// Set CLKPAD
	sdhci_writew(host, (0x2 << PAD_CNFG_RXSEL) | (0x3 << PAD_CNFG_TXSLEW_CTRL_P) | (0x2 << PAD_CNFG_TXSLEW_CTRL_N),
		     SDHCI_P_CLKPAD_CNFG);

	// Set STB_PAD
	sdhci_writew(host, (0x2 << PAD_CNFG_RXSEL) | (0x2 << PAD_CNFG_WEAKPULL_EN) |
			(0x3 << PAD_CNFG_TXSLEW_CTRL_P) | (0x2 << PAD_CNFG_TXSLEW_CTRL_N), SDHCI_P_STBPAD_CNFG);

	// Set RSTPAD
	sdhci_writew(host, (0x2 << PAD_CNFG_RXSEL) | (1 << PAD_CNFG_WEAKPULL_EN) |
			(0x3 << PAD_CNFG_TXSLEW_CTRL_P) | (0x2 << PAD_CNFG_TXSLEW_CTRL_N), SDHCI_P_RSTNPAD_CNFG);

	// Set SDCLKDL_CNFG, EXTDLY_EN = 1, fix delay
	sdhci_writeb(host, (1 << SDCLKDL_CNFG_EXTDLY_EN), SDHCI_P_SDCLKDL_CNFG);

	// Add 70 * 10 ps = 0.7ns
	sdhci_writeb(host, 0xA, SDHCI_P_SDCLKDL_DC);

	if (host->index == 1) {
		// Set SMPLDL_CNFG, Bypass
		sdhci_writeb(host, (1 << SMPLDL_CNFG_BYPASS_EN), SDHCI_P_SMPLDL_CNFG);
	} else {
		// Set SMPLDL_CNFG, INPSEL_CNFG = 0x2
		sdhci_writeb(host, (0x2 << SMPLDL_CNFG_INPSEL_CNFG), SDHCI_P_SMPLDL_CNFG);
	}

	// Set ATDL_CNFG, tuning clk not use for init
	sdhci_writeb(host, (2 << ATDL_CNFG_INPSEL_CNFG), SDHCI_P_ATDL_CNFG);

	// Deasset reset of phy
	sdhci_writel(host, sdhci_readl(host, SDHCI_P_PHY_CNFG) | (1 << PHY_CNFG_PHY_RSTN), SDHCI_P_PHY_CNFG);

	return 0;
}

#ifdef CONFIG_MMC_HS200_SUPPORT
static void cvi_mmc_set_tap(struct sdhci_host *host, u16 tap)
{
#ifdef CONFIG_TARGET_CVITEK_CV1822
	sdhci_writel(host, 0x0, CVI_SDHCI_VENDOR_MSHC_CTRL_R);
	/* clear_bit(CVI_SDHCI_BIT_CLK_FREE_EN, CVI_SDHCI_VENDOR_MSHC_CTRL_R); */
	tap = (tap << CVI_SDHCI_PHY_RX_DLY_SHIFT) & CVI_SDHCI_PHY_RX_DLY_MASK;
	// sdhci_writel(host, tap, CVI_SDHCI_VENDOR_A_STAT_R);
	sdhci_writel(host, sdhci_readl(host, CVI_SDHCI_PHY_TX_RX_DLY) | tap,
		     CVI_SDHCI_PHY_TX_RX_DLY);
#else
	sdhci_writew(host, 0, CVI_SDHCI_VENDOR_MSHC_CTRL_R);
	sdhci_writew(host, 0x18, CVI_SDHCI_VENDOR_A_CTRL_R);
	sdhci_writew(host, tap, CVI_SDHCI_VENDOR_A_STAT_R);
#endif
}

static void __attribute__((unused)) cvi_sdhci_cvi_1880_reset_after_tuning_pass(struct sdhci_host *host)
{
	pr_debug("tuning pass\n");

	/* Clear BUF_RD_READY intr */
	sdhci_writew(host, sdhci_readw(host, SDHCI_INT_STATUS) & (~(0x1 << 5)),
		     SDHCI_INT_STATUS);

	/* Set SDHCI_SOFTWARE_RESET.SW_RST_DAT = 1 to clear buffered tuning block */
	sdhci_writeb(host, sdhci_readb(host, SDHCI_SOFTWARE_RESET) | (0x1 << 2), SDHCI_SOFTWARE_RESET);

	/* Set SDHCI_SOFTWARE_RESET.SW_RST_CMD = 1	*/
	sdhci_writeb(host, sdhci_readb(host, SDHCI_SOFTWARE_RESET) | (0x1 << 1), SDHCI_SOFTWARE_RESET);

	while (sdhci_readb(host, SDHCI_SOFTWARE_RESET) & 0x3)
	;
}

static inline uint32_t CHECK_MASK_BIT(void *_mask, uint32_t bit)
{
	uint32_t w = bit / 8;
	uint32_t off = bit % 8;

	return ((uint8_t *)_mask)[w] & (1 << off);
}

static inline void SET_MASK_BIT(void *_mask, uint32_t bit)
{
	uint32_t byte = bit / 8;
	uint32_t offset = bit % 8;
	((uint8_t *)_mask)[byte] |= (1 << offset);
}

#define MAX_TUNING_CMD_RETRY_COUNT 50
#define RECORD_COUNT 8
#define TUNE_MAX_PHCODE	128
#define TAP_WINDOW_THLD 20

int cvi_mmc_execute_tuning(struct mmc *mmc, u8 opcode)
{
	struct cvi_sdhci_host *cvi_host = dev_get_priv(mmc->dev);
	struct sdhci_host *host = &cvi_host->host;
	u32 ctl2;
	u16 min = 0;
	u32 norm_stat_en_b, err_stat_en_b;
	u32 norm_signal_en_b;

	int ret;
	int final_tap = -1;
	u32 retry_cnt = 0;

	int tunning_result[4] = {0, 0, 0, 0};
	char pass_start_idx[RECORD_COUNT];
	char pass_width[RECORD_COUNT];
	int cur_idx = 0;

	int h312_result[4] = {0, 0, 0, 0};
	char h312_start_idx[RECORD_COUNT];
	char h312_width[RECORD_COUNT];
	int h312_cur_idx = 0;

	memset(pass_start_idx, -1, RECORD_COUNT);
	memset(pass_width, 0, RECORD_COUNT);
	memset(h312_start_idx, -1, RECORD_COUNT);
	memset(h312_width, 0, RECORD_COUNT);

	sdhci_writel(host, 0, 0x31c); // tx_delay_line setting TBD

	/* For SD tuning command */
	if (opcode == MMC_CMD_SEND_TUNING_BLOCK) {
		// Voltage switching flow (3.3→1.8)
		// Set PWRSW to 1.8V
		// => sd_pwrsw_ctrl (0x030001F4) = 0x0000000B (reg_pwrsw_auto=1,
		// reg_pwrsw_disc=0,  reg_pwrsw_vsel=1(1.8v),  reg_en_pwrsw=1)
		mmio_write_32(0x30001F4, 0xB);
		printf("sd PWRSW 0x%x\n", mmio_read_32(0x30001F4));

		//set SDIO0 PAD to 1.8V mode
		//=>  0x03000018[5:4] = 2'b11  ,( reg_sd0_ms_ow=1. reg_sd0_ms_sw=0) => MS overwrite to 1 (1.8v mode)
		mmio_setbits_32(0x3000018, BIT(4) | BIT(5));
		printf("SDIO0 PAD 0x%x\n", mmio_read_32(0x3000018));

		//wait 1ms
		mdelay(1);
	}

	__attribute__((unused)) u32 reg = 0;

	norm_stat_en_b = sdhci_readw(host, SDHCI_INT_ENABLE);
	err_stat_en_b = sdhci_readw(host, SDHCI_ERR_INT_STATUS_EN);
	norm_signal_en_b = sdhci_readl(host, SDHCI_SIGNAL_ENABLE);

	sdhci_writel(host, 0x0, CVI_SDHCI_VENDOR_MSHC_CTRL_R); // ??

	reg = sdhci_readw(host, SDHCI_ERR_INT_STATUS);
	pr_debug("SDHCI_ERR_INT_STATUS 0x%x\n", reg);

	reg = sdhci_readw(host, SDHCI_HOST_CONTROL2);
	pr_debug("host ctrl2 0x%x\n", reg);
	/* Set Host_CTRL2_R.SAMPLE_CLK_SEL=0 */
	sdhci_writew(host, sdhci_readw(host, SDHCI_HOST_CONTROL2) & (~(0x1 << 7)), SDHCI_HOST_CONTROL2);
	sdhci_writew(host, sdhci_readw(host, SDHCI_HOST_CONTROL2) & (~(0x3 << 4)), SDHCI_HOST_CONTROL2);

	reg = sdhci_readw(host, SDHCI_HOST_CONTROL2);
	pr_debug("host ctrl2 0x%x\n", reg);

#ifndef CONFIG_TARGET_CVITEK_CV1822
	/* Set ATR_CTRL_R.SW_TNE_EN=1 */
	reg = sdhci_readl(host, CVI_SDHCI_VENDOR_A_CTRL_R);
	pr_debug("A ctrl 0x%x\n", reg);
	sdhci_writel(host, sdhci_readl(host, CVI_SDHCI_VENDOR_A_CTRL_R) | (0x1 << 4), CVI_SDHCI_VENDOR_A_CTRL_R);
	reg = sdhci_readl(host, CVI_SDHCI_VENDOR_A_CTRL_R);
	pr_debug("A ctrl 0x%x\n", reg);
#endif
	while (min < TUNE_MAX_PHCODE) {
		retry_cnt = 0;

		cvi_mmc_set_tap(host, min);

retry_tuning:
		ret = mmc_send_tuning(mmc, opcode, NULL);

		if (!ret && retry_cnt < MAX_TUNING_CMD_RETRY_COUNT) {
			retry_cnt++;
			goto retry_tuning;
		}

		int tuning_reg = sdhci_readw(host, 0x312);

		if (ret) {
			SET_MASK_BIT(tunning_result, min);
		}

		if (tuning_reg & BIT(1)) {
			SET_MASK_BIT(h312_result, min);
		}

		min++;
	}

//	dump_hex("tuning result", tunning_result, 16);

	for (int k = 0; k < TUNE_MAX_PHCODE; k++) {
		if (CHECK_MASK_BIT(tunning_result, k) == 0) {
			if (pass_start_idx[cur_idx] == 255)
				pass_start_idx[cur_idx] = k;
			pass_width[cur_idx]++;
		} else {
			if (pass_start_idx[cur_idx] != 255)
				cur_idx++;
		}
		if (cur_idx >= RECORD_COUNT)
			break;
	}

	for (int k = 0; k < RECORD_COUNT; k++) {
		if (pass_width[k])
			printf("%d: tuning S:%d, W:%d\n", k, pass_start_idx[k], pass_width[k]);

		if (pass_width[k] >= TAP_WINDOW_THLD && final_tap == -1) {
			final_tap = pass_start_idx[k] + pass_width[k] / 2;
			printf("final_tap %d\n", final_tap);
			break;
		}
	}

//	dump_hex("h312 result", h312_result, 16);

	for (int k = 0; k < TUNE_MAX_PHCODE; k++) {
		if (CHECK_MASK_BIT(h312_result, k) == 0) {
			if (h312_start_idx[h312_cur_idx] == 255)
				h312_start_idx[h312_cur_idx] = k;
			h312_width[h312_cur_idx]++;
		} else {
			if (h312_start_idx[h312_cur_idx] != 255)
				h312_cur_idx++;
		}

		if (h312_cur_idx >= RECORD_COUNT)
			break;
	}

	for (int k = 0; k < RECORD_COUNT; k++) {
		if (h312_width[k])
			printf("%d: h312 S:%d, W:%d\n", k, h312_start_idx[k], h312_width[k]);
	}

	cvi_mmc_set_tap(host, final_tap);

	sdhci_writeb(host, 0x6, SDHCI_SOFTWARE_RESET);
	while (sdhci_readb(host, SDHCI_SOFTWARE_RESET))
		;

	ctl2 = sdhci_readw(host, SDHCI_HOST_CONTROL2);
	ctl2 &= ~SDHCI_CTRL_EXEC_TUNING;
	sdhci_writew(host, ctl2, SDHCI_HOST_CONTROL2);

	sdhci_writew(host, norm_stat_en_b, SDHCI_INT_ENABLE);
	sdhci_writel(host, norm_signal_en_b, SDHCI_SIGNAL_ENABLE);
	sdhci_writew(host, err_stat_en_b, SDHCI_ERR_INT_STATUS_EN);

	printf("%s finished tuning, code:%d\n", __func__, final_tap);

	return 0;
}
#endif

int cvi_get_cd(struct sdhci_host *host)
{
	u32 reg;

	reg = sdhci_readl(host, SDHCI_PRESENT_STATE);

	if (reg & SDHCI_CARD_PRESENT) {
		sdhci_writeb(host, sdhci_readb(host, SDHCI_POWER_CONTROL) | SDHCI_POWER_ON,
			     SDHCI_POWER_CONTROL);
		return 1;
	} else {
		return 0;
	}
}

static const struct sdhci_ops cvi_sdhci_ops = {
	.get_cd	= cvi_get_cd,
};

#ifdef CONFIG_MMC_SUPPORTS_TUNING
static const struct sdhci_ops cvi_sdhci_emmc_ops = {
	.platform_execute_tuning	= cvi_mmc_execute_tuning,
};
#endif


static int cvi_sdhci_probe(struct udevice *dev)
{
	struct mmc_uclass_priv *upriv = dev_get_uclass_priv(dev);
	struct cvi_sdhci_plat *plat = dev_get_platdata(dev);
	struct cvi_sdhci_host *cvi_host = dev_get_priv(dev);
	struct sdhci_host *host = &cvi_host->host;
	int ret;

	pr_debug("[hq] %s\n", __func__);

	ret = reset_get_by_name(dev, "sdhci", &cvi_host->reset_ctl);
	if (ret) {
		debug("warning: reset_get_by_name failed\n");
	} else {
		// Try to solve 1.8 to 3.3v converter HW issue
		ret = reset_assert(&cvi_host->reset_ctl);
		if (ret) {
			printf("%s failed assert reset\n", __func__);
			return ret;
		}

		ret = reset_deassert(&cvi_host->reset_ctl);
		if (ret) {
			printf("%s failed deassert reset\n", __func__);
			return ret;
		}
	}

	ret = sdhci_setup_cfg(&plat->cfg, host, cvi_host->mmc_trans_freq, cvi_host->mmc_init_freq);

	if (ret)
		return ret;

	upriv->mmc = &plat->mmc;
	host->mmc = &plat->mmc;
	host->mmc->priv = host;
	pr_debug("host %p, mmc %p, priv %p\n", host, host->mmc, host->mmc->priv);

	if (host->index == 1) {
		host->ops = &cvi_sdhci_ops;
	}
#ifdef CONFIG_MMC_SUPPORTS_TUNING
	else if (host->index == 0)
		host->ops = &cvi_sdhci_emmc_ops;
#endif
	else if (host->index > 2) {
		printf("wrong host index!!\n");
		return -ENXIO;
	}

#ifdef CONFIG_TARGET_CVITEK_CV1822
	if (host->index == 2) {
		pr_debug("sdio1 probe\n");
		cvi_sdio1_pad_setting();
		mmio_write_32(0x03000248, 1); // enable rtc2ap_ahb;
	}
#endif
	ret = sdhci_probe(dev);

	if (cvi_host->has_phy) {
		cvi_sdhci_phy_init(cvi_host);
	}

	if (host->max_clk == CV1835_MMC_MAX_CLOCK) {
		// For CV1835, set IP clock to 375Mhz
		pr_debug("For CV1835, set IP clock to 375Mhz\n");
		mmio_write_32(cvi_host->pll_reg, CV1835_MMC_MAX_CLOCK_DIV_VALUE);

		pr_debug("Be sure to switch clock source to PLL\n");
		mmio_clrbits_32(CLOCK_BYPASS_SELECT_REGISTER, BIT(cvi_host->pll_index));
		pr_debug("XTAL->PLL reg = 0x%x\n", mmio_read_32(CLOCK_BYPASS_SELECT_REGISTER));

		pr_debug("eMMC/SD CLK is %d in FPGA_ASIC\n", host->max_clk);
	}

	if (cvi_host->is_64_addressing) {
		sdhci_writew(host, sdhci_readw(host, SDHCI_HOST_CONTROL2)
				| SDHCI_HOST_VER4_ENABLE | SDHCI_HOST_ADDRESSING,
				SDHCI_HOST_CONTROL2);
	}
	sdhci_writew(host, sdhci_readw(host, sdhci_readw(host, SDHCI_VENDOR_SPECIFIC_AREA) +
			SDHCI_EMMC_CTRL_R) | 0x1 << 0,
			sdhci_readw(host, SDHCI_VENDOR_SPECIFIC_AREA) + SDHCI_EMMC_CTRL_R);

	if (cvi_host->reset_tx_rx_phy) {
#ifdef CONFIG_TARGET_CVITEK_CV1822
		/* Default value */
		sdhci_writel(host, 2, CVI_SDHCI_VENDOR_OFFSET);
		sdhci_writel(host, 0x01000100, CVI_SDHCI_PHY_TX_RX_DLY);
		sdhci_writel(host, 00000001, SDHCI_PHY_CONFIG);
#else
		pr_debug("set tx rx src sel to 0 ======================\n");
		sdhci_writel(host, 0, SDHCI_RX_DELAY_LINE);
		sdhci_writel(host, 0, SDHCI_TX_DELAY_LINE);
#endif
	}

	return ret;
}

static const struct udevice_id cvi_sdhci_match[] = {
	{ .compatible = "cvitek,synopsys-sdhc" },
	{ /* sentinel */ }
};

U_BOOT_DRIVER(cvi_sdhci) = {
	.name = "cvi_sdhci",
	.id = UCLASS_MMC,
	.of_match = cvi_sdhci_match,
	.ofdata_to_platdata = cvi_ofdata_to_platdata,
	.bind = cvi_sdhci_bind,
	.probe = cvi_sdhci_probe,
	.priv_auto_alloc_size = sizeof(struct cvi_sdhci_host),
	.platdata_auto_alloc_size = sizeof(struct cvi_sdhci_plat),
	.ops = &sdhci_ops,
};
