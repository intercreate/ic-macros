/*
 * Copyright (c) 2023, Intercreate, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "ic_macros/assert_type.h"
#include "ic_macros/ic_assert.h"
#include "ic_macros/integer_cast.h"
#include "zephyr/util.h"

/**
 * @brief Compile-time constant safe cast from an integer type to an enum.
 * @note Use IC_Z_CAST_ENUM for a runtime variant of this macro.
 * @param type The enum type to cast to.
 * @param min The minimum value of type, e.g. 0 or MY_ENUM_MIN.
 * @param max The maximum value of type, e.g. MY_ENUM_MAX.
 * @param expr The expression to cast.
 * @return The expr casted to type: (type) (expr)
 */
#define IC_CAST_ENUM(type, min, max, expr) \
    ({ \
        IC_BUILD_ASSERT(__typeof__(expr) == type || IC_IS_INT(expr) || IC_IS_UINT(expr)); \
        IC_CAST_NUMBER(type, min, max, expr); \
    })

/**
 * @brief Safe cast from from an integer type to an enum.
 * @note The expression will be evaluated once.
 * @param type The enum type to cast to.
 * @param min The minimum value of type, e.g. 0 or MY_ENUM_MIN.
 * @param max The maximum value of type, e.g. MY_ENUM_MAX.
 * @param expr The expression to cast.
 * @return The expr casted to type: (type) (expr)
 */
#define IC_Z_CAST_ENUM(type, min, max, expr) \
    ({ \
        __auto_type const _IC_Z_CAST_NUMBER_expr_ = IC_REQUIRE_NOT_CONSTANT(expr); \
        IC_BUILD_ASSERT(!IC_IS_FP(_IC_Z_CAST_NUMBER_expr_)); \
        IC_ASSERT(IC_IN_RANGE(_IC_Z_CAST_NUMBER_expr_, min, max)); \
        (type) _IC_Z_CAST_NUMBER_expr_; \
    })
