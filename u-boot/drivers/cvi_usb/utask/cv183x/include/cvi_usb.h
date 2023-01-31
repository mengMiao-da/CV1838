/*
 * Copyright (c) 2015-2016, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __CVI_USB_H
#define __CVI_USB_H

#define USB_SUPPORT_EFUSE

#define BCD_USB_SS                      0x0310  /* 3.00 version USB*/
#define ID_VENDOR                       0x0559  /* Cadence*/
#define ID_PRODUCT                      0x1001  /* example bulk product*/
#define BCD_DEVICE_SS                   0x0100  /* 0.1*/
#define BCD_USB_HS_ONLY                 0x0201  /* 2.01  Only HS with BOS descriptor */
#define BCD_USB_HS                      0x0210  /* 2.10*/
#define BCD_DEVICE_HS                   0x0200  /* 2.00*/

#define USB_MANUFACTURER_STRING         "CVITEK"
#define USB_PRODUCT_STRING              "USB Com Port"
#define USB_SERIAL_NUMBER_STRING        "123456789ABC" /* should 12 chars long*/

#define BULK_EP_IN 0x81
#define BULK_EP_OUT 0x01
#define BULK_EP_NOTIFY 0x82
#define HEADER_SIZE 8

#define SS_PERIPH_DISABLED_SET BIT(21)
#define HOST_BUS_DROP          BIT(9)
#define DEV_BUS_REQ            (1)
#define INTR_SPI_BASE          32
#define USB_DEV_INTR0          115
/*#define USB_DEV_INTR1          116*/
/*#define USB_IRQ_MODE*/

enum CVI_USB_TOKEN {
	CVI_USB_NONE = 0,
	CVI_USB_INFO,
	CVI_USB_VERBOSE,
	CVI_USB_JUMP,
	CVI_USB_BREAK,
	CVI_USB_KEEP_DL,
	CVI_USB_PRG_CMD,
	CVI_USB_RESET_ARM,
	CVI_USB_TEST_THERMAL_SENSOR,
	CVI_USB_TEST_EMMC,
	CVI_USB_TEST_GET_RESULT,
	CVI_USB_EFUSEW,
	CVI_USB_READ_SN,
	CV_USB_EFUSE_PATCH = 13,
	CVI_USB_EFUSER = 14,
	CV_USB_NONE_FAST = 20,
	CV_USB_JUMP_ACK = 21,
	CVI_USB_REBOOT = 22,
	CVI_USB_RUNTIME = 0x80,
	CVI_USB_S2D = 0x81,
	CVI_USB_D2S = 0x82
};

enum ACK_RESULT {
	ACK_FAIL,
	ACK_PASS,
};

typedef void func(void);

#define USB_BUF_BASE      0x08001000
/*#define USB_BUF_BASE      0x0401E000*/
#define PD_SIZE           4096
#define BUF_SIZE          1024
#define EP0_SIZE          512
#define TRB_SIZE          256
#define CB_SIZE           128
#if defined(USB_SUPPORT_EFUSE)
#define RSP_SIZE          64
#else
#define RSP_SIZE          16
#endif

#define PD_ADDR USB_BUF_BASE
#define BLK_BUF_ADDR  (PD_ADDR + PD_SIZE)       /* 1024*/
#define CMD_BUF_ADDR  (BLK_BUF_ADDR + BUF_SIZE) /* 1024*/
#define TRB_BUF_ADDR  (CMD_BUF_ADDR + BUF_SIZE) /* 256*/
#define CB0_BUF_ADDR  (TRB_BUF_ADDR + TRB_SIZE) /* 128*/
#define CB1_BUF_ADDR  (CB0_BUF_ADDR + CB_SIZE)  /* 128*/
#define CB2_BUF_ADDR  (CB1_BUF_ADDR + CB_SIZE)  /* 128*/
#define EP0_BUF_ADDR  (CB2_BUF_ADDR + CB_SIZE)  /* 512*/
#define RSP_BUF_ADDR  (EP0_BUF_ADDR + EP0_SIZE) /* 16*/
#define ACM_BUF_ADDR  (RSP_BUF_ADDR + RSP_SIZE) /* 128*/

int cvi_usb_polling(void);
void acm_patch_id(unsigned short vid, unsigned short pid);
#endif
