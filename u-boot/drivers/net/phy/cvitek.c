/*
 * CVITEK PHY drivers
 *
 * SPDX-License-Identifier:	GPL-2.0+
 *
 * Copyright 2020 CVITEK, Inc.
 */

#include <config.h>
#include <common.h>
#include <linux/bitops.h>
#include <phy.h>

#define CVI_ETH_PHY_MII_CTL			0
#define CVI_ETH_MMD_ACCESS_CTL		13
#define CVI_ETH_MMD_ACCESS_DATA		14
#define CVI_ETH_PHY_ADC_CTRL		16
#define CVI_ETH_AUTO_CALIBRATE		16
#define CVI_ETH_PHY_APS				18
#define CVI_ETH_PHY_LB_CTL			18
#define CVI_ETH_PHY_AFE_TX			20
#define CVI_ETH_PHY_AFE_DRV2		21
#define CVI_ETH_PHY_CP				23
#define CVI_ETH_PHY_ADC_OP_BIAS		24
#define CVI_ETH_PHY_RX_SIGNAL		25
#define CVI_ETH_PHY_2_MISC			28
#define CVI_ETH_PHY_TXDATA_CTRL		24
#define CVI_ETH_PHY_PAGE_SEL		31

#define CVI_ETH_DEV_ADDR_7		7
#define CVI_ETH_EEE_ADV			60

#define CVI_ETH_PHY_PAGE_0		0x0000
#define CVI_ETH_PHY_PAGE_1		0x0100
#define CVI_ETH_PHY_PAGE_2		0x0200
#define CVI_ETH_PHY_PAGE_3		0x0300
#define CVI_ETH_PHY_PAGE_6		0x0600
#define CVI_ETH_PHY_PAGE_8		0x0800
#define CVI_ETH_PHY_PAGE_9		0x0900

//#define CVI_ETH_PHY_LOOPBACK
#define LOOPBACK_XMII2MAC		0x8000
#define LOOPBACK_PCS2MAC		0x2000
#define LOOPBACK_PMA2MAC		0x1000
#define LOOPBACK_RMII2PHY		0x0080

static void cvi18xx_mdio_w(struct phy_device *phydev, int dev_addr, int reg_addr, int val)
{
	phy_write(phydev, MDIO_DEVAD_NONE, CVI_ETH_MMD_ACCESS_CTL, dev_addr);
	phy_write(phydev, MDIO_DEVAD_NONE, CVI_ETH_MMD_ACCESS_DATA, reg_addr);
	phy_write(phydev, MDIO_DEVAD_NONE, CVI_ETH_MMD_ACCESS_CTL, (1 << 14) | dev_addr);
	phy_write(phydev, MDIO_DEVAD_NONE, CVI_ETH_MMD_ACCESS_DATA, val);
}

#if defined(CVI_ETH_PHY_LOOPBACK)
static int cvi18xx_set_phy_loopback(struct phy_device *phydev, int mode)
{
	phy_write(phydev, MDIO_DEVAD_NONE, CVI_ETH_PHY_PAGE_SEL, CVI_ETH_PHY_PAGE_0);
	switch (mode) {
	case LOOPBACK_XMII2MAC:
		phy_write(phydev, MDIO_DEVAD_NONE, CVI_ETH_PHY_LB_CTL, LOOPBACK_XMII2MAC);
		break;
	case LOOPBACK_PCS2MAC:
		phy_write(phydev, MDIO_DEVAD_NONE, CVI_ETH_PHY_LB_CTL, LOOPBACK_PCS2MAC);
		break;
	case LOOPBACK_PMA2MAC:
		phy_write(phydev, MDIO_DEVAD_NONE, CVI_ETH_PHY_LB_CTL, LOOPBACK_PMA2MAC);
		break;
	case LOOPBACK_RMII2PHY:
		phy_write(phydev, MDIO_DEVAD_NONE, CVI_ETH_PHY_LB_CTL, LOOPBACK_RMII2PHY);
		break;
	default:
		printf("wrong loopback mode\n");
		break;
	}
	return 0;
}
#endif

/* CVITEK cvi18xx */
static int cvi18xx_config(struct phy_device *phydev)
{
	phy_reset(phydev);

	/* switch to page 1 */
	phy_write(phydev, MDIO_DEVAD_NONE, CVI_ETH_PHY_PAGE_SEL, CVI_ETH_PHY_PAGE_1);
	/* Disable APS */
	phy_write(phydev, MDIO_DEVAD_NONE, CVI_ETH_PHY_APS, 0x4824);
	/* switch to page 2 */
	phy_write(phydev, MDIO_DEVAD_NONE, CVI_ETH_PHY_PAGE_SEL, CVI_ETH_PHY_PAGE_2);
	/* PHYAFE TRX optimization */
	phy_write(phydev, MDIO_DEVAD_NONE, CVI_ETH_PHY_TXDATA_CTRL, 0x0000);
	/* switch to page 6 */
	phy_write(phydev, MDIO_DEVAD_NONE, CVI_ETH_PHY_PAGE_SEL, CVI_ETH_PHY_PAGE_6);
	/* PHYAFE ADC optimization */
	phy_write(phydev, MDIO_DEVAD_NONE, CVI_ETH_PHY_ADC_CTRL, 0x555b);
	/* PHYAFE TX optimization */
	phy_write(phydev, MDIO_DEVAD_NONE, CVI_ETH_PHY_AFE_TX, 0x508f);
	/* enable a_CLKSELIN to avoid CRC error and increase  10M/100M amplitude*/
	phy_write(phydev, MDIO_DEVAD_NONE, CVI_ETH_PHY_AFE_DRV2, 0x3030);
	/* PHYAFE CP current optimization */
	phy_write(phydev, MDIO_DEVAD_NONE, CVI_ETH_PHY_CP, 0x0575);
	/* PHYAFE ADC OP BIAS optimization */
	phy_write(phydev, MDIO_DEVAD_NONE, CVI_ETH_PHY_ADC_OP_BIAS, 0x0000);
	/* PHYAFE RX signal detector level optimization */
	phy_write(phydev, MDIO_DEVAD_NONE, CVI_ETH_PHY_RX_SIGNAL, 0x0408);
	/* Enable PD control optimization */
	phy_write(phydev, MDIO_DEVAD_NONE, CVI_ETH_PHY_2_MISC, 0x8880);

	/* switch to page 8 */
	phy_write(phydev, MDIO_DEVAD_NONE, CVI_ETH_PHY_PAGE_SEL, CVI_ETH_PHY_PAGE_8);
	/* Stop auto-calibrate */
	phy_write(phydev, MDIO_DEVAD_NONE, CVI_ETH_AUTO_CALIBRATE, 0x0844);

	/* switch back to page 0 */
	phy_write(phydev, MDIO_DEVAD_NONE, CVI_ETH_PHY_PAGE_SEL, CVI_ETH_PHY_PAGE_0);

	cvi18xx_mdio_w(phydev, CVI_ETH_DEV_ADDR_7, CVI_ETH_EEE_ADV, 0x0);

	genphy_config(phydev);

#if defined(CVI_ETH_PHY_LOOPBACK)
	cvi18xx_set_phy_loopback(phydev, LOOPBACK_PCS2MAC);
#endif

	return 0;
}

static int cvi18xx_parse_status(struct phy_device *phydev)
{
	int mii_reg;

	mii_reg = phy_read(phydev, MDIO_DEVAD_NONE, MII_BMSR);

	if (mii_reg & (BMSR_100FULL | BMSR_100HALF))
		phydev->speed = SPEED_100;
	else
		phydev->speed = SPEED_10;

	if (mii_reg & (BMSR_10FULL | BMSR_100FULL))
		phydev->duplex = DUPLEX_FULL;
	else
		phydev->duplex = DUPLEX_HALF;

	return 0;
}

static int cvi18xx_startup(struct phy_device *phydev)
{
	int ret;

	/* Read the Status (2x to make sure link is right) */
	ret = genphy_update_link(phydev);
	if (ret)
		return ret;

	return cvi18xx_parse_status(phydev);
}

/* Support for CVI1835 PHYs */
static struct phy_driver CVI18XX_driver = {
	.name = "CVITEK CVI18XX",
	.uid = 0x00441400,
	.mask = 0xffffffff,
	.features = PHY_BASIC_FEATURES,
	.config = &cvi18xx_config,
	.startup = &cvi18xx_startup,
	.shutdown = &genphy_shutdown,
};

int phy_cvitek_init(void)
{
	phy_register(&CVI18XX_driver);

	return 0;
}
