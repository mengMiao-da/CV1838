/*
 * Copyright (c) 2015-2016, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __PLATFORM_DEF_H__
#define __PLATFORM_DEF_H__

#include <common.h>

#if defined(CONFIG_TARGET_CVITEK_CV1835)
#include <../../../board/cvitek/cv1835/cv1835_reg.h>
#elif defined(CONFIG_TARGET_CVITEK_CV1822)
#include <../../../board/cvitek/cv1822/cv1822_reg.h>
#else
#error "use cvi_utask at wrong platform"
#endif

#define DISABLE_DCACHE

#endif /* __PLATFORM_DEF_H__ */
