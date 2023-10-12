/*
 * Copyright (c) 2023, Intercreate, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif


#define _IC_DO_PRAGMA(x) _Pragma(#x)

/** @brief Print a diagnostic build message while compiling. */
#define IC_BUILD_MESSAGE(msg) _IC_DO_PRAGMA(message("Build message - " #msg))

#ifdef __cplusplus
}
#endif
