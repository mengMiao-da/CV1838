/*
 * Copyright (C) Cvitek Co., Ltd. 2019-2021. All rights reserved.
 *
 * File Name: cvi_panel_diffs.h
 * Description:
 */

#ifndef __CVI_PANEL_DIFFS_H__
#define __CVI_PANEL_DIFFS_H__

#ifdef I80_PANEL_ST7789V
#define CVI_JPEG ""
#define START_VO "startvo 0 65536 0;"
#define LOGO_POS_INFO " 736 0 0 240 320;"
#else
#define CVI_JPEG "cvi_jpeg " LOGO_READ_ADDR " " LOGO_RESERVED_ADDR " " LOGOSIZE ";"
#define START_VO "startvo 0 8192 0;"

#ifdef MIPI_PANEL_ICN9707
#define LOGO_POS_INFO " 128 170 740 127 447;"
#elif MIPI_PANEL_ST7701
#define LOGO_POS_INFO " 128 176 176 127 447;"
#else
#define LOGO_POS_INFO " 512 104 568 512 144;"
#endif

#endif

#define START_VL "startvl 0 " LOGO_READ_ADDR " " LOGO_RESERVED_ADDR " " LOGO_POS_INFO ";"
#define SET_VO_BG "setvobg 0 0xffffffff;"

#endif
