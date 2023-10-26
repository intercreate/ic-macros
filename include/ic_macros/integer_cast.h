/*
 * Copyright (c) 2023, Intercreate, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdint.h>

#include "ic_macros/ic_assert.h"
#include "zephyr/util.h"

/**
 * @brief Compile-time constant safe cast from one number type to another.
 * @note Causes a compile error if the expr is out of range.
 * @param type The integer type to cast to.
 * @param min The minimum value of type, e.g. 0 or INT<>_MIN.
 * @param max The maximum value of type, e.g. INT<>_MAX.
 * @param expr The expression to cast.
 * @return The expr casted to type: (type) (expr)
 */
#define IC_G_CAST_NUMBER(type, min, max, expr) \
    (type)(expr) + IC_ZERO_OR_COMPILE_ERROR((expr) >= min && (expr) <= max)


/**
 * @brief Safe cast from one number type to another
 * @note The expression will be evaluated once.
 * @param type The integer type to cast to.
 * @param min The minimum value of type, e.g. 0 or INT<>_MIN.
 * @param max The maximum value of type, e.g. INT<>_MAX.
 * @param expr The expression to cast.
 * @return The expr casted to type: (type) (expr)
 */
#define IC_CAST_NUMBER(type, min, max, expr) \
    ({ \
        __auto_type const _IC_CAST_NUMBER_expr_ = (expr); \
        IC_ASSERT(IC_G_IN_RANGE(_IC_CAST_NUMBER_expr_, min, max)); \
        (type) _IC_CAST_NUMBER_expr_; \
    })

/**
 * @brief Safe cast from one number type to another
 * @note The expression will be evaluated once.
 * @param type The integer type to cast to.
 * @param min The minimum value of type, e.g. 0 or INT<>_MIN.
 * @param max The maximum value of type, e.g. INT<>_MAX.
 * @param expr The expression to cast.
 * @return The expr casted to type: (type) (expr)
 */
#define IC_CAST_UNSIGNED(type, _, max, expr) \
    ({ \
        __auto_type const _IC_CAST_NUMBER_expr_ = (expr); \
        IC_ASSERT(_IC_CAST_NUMBER_expr_ <= max); \
        (type) _IC_CAST_NUMBER_expr_; \
    })

/**
 * @brief Safe cast from one number type to another
 * @note The expression will be evaluated once.
 * @param type The integer type to cast to.
 * @param min The minimum value of type, e.g. 0 or INT<>_MIN.
 * @param max The maximum value of type, e.g. INT<>_MAX.
 * @param expr The expression to cast.
 * @return The expr casted to type: (type) (expr)
 */
#define _IC_CAST_NUMBER(type, min, max, expr) \
    _Generic((expr), uint8_t: IC_CAST_UNSIGNED, uint16_t: IC_CAST_UNSIGNED, uint32_t: IC_CAST_UNSIGNED, uint64_t: IC_CAST_UNSIGNED, default: IC_CAST_SIGNED)( \
        type, min, max, expr \
    )

/**
 * @brief Cast the expression after asserting that it is in range.
 * @note The expression will be evaluated once.
 * @param expr The expression to cast.
 * @return The expr casted to type: (uint8_t) (expr)
 */
#define IC_UINT8(expr) IC_CAST_NUMBER(uint8_t, 0, UINT8_MAX, expr)

/**
 * @brief Cast the expression after asserting that it is in range.
 * @note The expression will be evaluated once.
 * @param expr The expression to cast.
 * @return The expr casted to type: (uint16_t) (expr)
 */
#define IC_UINT16(expr) IC_CAST_NUMBER(uint16_t, 0, UINT16_MAX, expr)

/**
 * @brief Cast the expression after asserting that it is in range.
 * @note The expression will be evaluated once.
 * @param expr The expression to cast.
 * @return The expr casted to type: (uint32_t) (expr)
 */
#define IC_UINT32(expr) IC_CAST_NUMBER(uint32_t, 0, UINT32_MAX, expr)

/**
 * @brief Cast the expression after asserting that it is in range.
 * @note The expression will be evaluated once.
 * @param expr The expression to cast.
 * @return The expr casted to type: (uint64_t) (expr)
 */
#define IC_UINT64(expr) IC_CAST_NUMBER(uint64_t, 0, UINT64_MAX, expr)

/**
 * @brief Cast the expression after asserting that it is in range.
 * @note The expression will be evaluated once.
 * @param expr The expression to cast.
 * @return The expr casted to type: (int8_t) (expr)
 */
#define IC_INT8(expr) IC_CAST_NUMBER(int8_t, INT8_MIN, INT8_MAX, expr)

/**
 * @brief Cast the expression after asserting that it is in range.
 * @note The expression will be evaluated once.
 * @param expr The expression to cast.
 * @return The expr casted to type: (int16_t) (expr)
 */
#define IC_INT16(expr) IC_CAST_NUMBER(int16_t, INT16_MIN, INT16_MAX, expr)

/**
 * @brief Cast the expression after asserting that it is in range.
 * @note The expression will be evaluated once.
 * @param expr The expression to cast.
 * @return The expr casted to type: (int32_t) (expr)
 */
#define IC_INT32(expr) IC_CAST_NUMBER(int32_t, INT32_MIN, INT32_MAX, expr)

/**
 * @brief Cast the expression after asserting that it is in range.
 * @note The expression will be evaluated once.
 * @param expr The expression to cast.
 * @return The expr casted to type: (int64_t) (expr)
 */
#define IC_INT64(expr) IC_CAST_NUMBER(int64_t, INT64_MIN, INT64_MAX, expr)

/**
 * @brief Global scope only; cast the expression after asserting that it is in range.
 * @param expr The expression to cast.
 * @return The expr casted to type: (uint8_t) (expr)
 */
#define IC_G_UINT8(expr) IC_G_CAST_NUMBER(uint8_t, 0, UINT8_MAX, expr)

/**
 * @brief Global scope only; cast the expression after asserting that it is in range.
 * @param expr The expression to cast.
 * @return The expr casted to type: (uint16_t) (expr)
 */
#define IC_G_UINT16(expr) IC_G_CAST_NUMBER(uint16_t, 0, UINT16_MAX, expr)

/**
 * @brief Global scope only; cast the expression after asserting that it is in range.
 * @param expr The expression to cast.
 * @return The expr casted to type: (uint32_t) (expr)
 */
#define IC_G_UINT32(expr) IC_G_CAST_NUMBER(uint32_t, 0, UINT32_MAX, expr)

/**
 * @brief Global scope only; cast the expression after asserting that it is in range.
 * @param expr The expression to cast.
 * @return The expr casted to type: (uint64_t) (expr)
 */
#define IC_G_UINT64(expr) IC_G_CAST_NUMBER(uint64_t, 0, UINT64_MAX, expr)

/**
 * @brief Global scope only; cast the expression after asserting that it is in range.
 * @param expr The expression to cast.
 * @return The expr casted to type: (int8_t) (expr)
 */
#define IC_G_INT8(expr) IC_G_CAST_NUMBER(int8_t, INT8_MIN, INT8_MAX, expr)

/**
 * @brief Global scope only; cast the expression after asserting that it is in range.
 * @param expr The expression to cast.
 * @return The expr casted to type: (int16_t) (expr)
 */
#define IC_G_INT16(expr) IC_G_CAST_NUMBER(int16_t, INT16_MIN, INT16_MAX, expr)

/**
 * @brief Global scope only; cast the expression after asserting that it is in range.
 * @param expr The expression to cast.
 * @return The expr casted to type: (int32_t) (expr)
 */
#define IC_G_INT32(expr) IC_G_CAST_NUMBER(int32_t, INT32_MIN, INT32_MAX, expr)

/**
 * @brief Global scope only; cast the expression after asserting that it is in range.
 * @param expr The expression to cast.
 * @return The expr casted to type: (int64_t) (expr)
 */
#define IC_G_INT64(expr) IC_G_CAST_NUMBER(int64_t, INT64_MIN, INT64_MAX, expr)
