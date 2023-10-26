/*
 * Copyright (c) 2023, Intercreate, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "ic_macros/assert_constant.h"

/**
 * @brief Compile-time check if expr is type.
 * @param type The type.
 * @param expr The expression.
 * @return 1 if the expression is of type, else 0.
 * @note This will evaluate the expression once.
 */
#define IC_IS_TYPE(type, expr) __builtin_types_compatible_p(type, __typeof__(expr))

/**
 * @brief Compile-time assertion that expr is type.
 * @param type The expected type.
 * @param expr The expression.
 * @note This will evaluate the expression once.
 */
#define IC_ASSERT_TYPE(type, expr) \
    IC_BUILD_ASSERT(IC_IS_TYPE(type, expr), #expr " is not of type " #type)

/**
 * @brief Compile-time assertion that expr is type returning expr.
 * @param type The expected type.
 * @param expr The expression.
 * @note This requires that the expression is a compile-time constant to prevent
 *       multiple runtime evaluations of the expression.
 */
#define IC_REQUIRE_TYPE(type, expr) \
    ({ \
        IC_REQUIRE_CONSTANT(expr); \
        IC_ASSERT_TYPE(type, expr); \
        expr; \
    })

#define _IC_IS_UINT(expr) \
    (__builtin_types_compatible_p(uint8_t, __typeof__(expr)) \
     || __builtin_types_compatible_p(unsigned char, __typeof__(expr)) \
     || __builtin_types_compatible_p(uint16_t, __typeof__(expr)) \
     || __builtin_types_compatible_p(unsigned short int, __typeof__(expr)) \
     || __builtin_types_compatible_p(uint32_t, __typeof__(expr)) \
     || __builtin_types_compatible_p(unsigned long int, __typeof__(expr)) \
     || __builtin_types_compatible_p(uint64_t, __typeof__(expr)) \
     || __builtin_types_compatible_p(unsigned long long int, __typeof__(expr)))

/**
 * @brief Compile-time constant check if expr is an unsigned integer.
 * @param expr The expression.
 * @note This requires that the expression is a compile-time constant to prevent
 *       multiple runtime evaluations of the expression.
 * @return 1 if expr is an unsigned integer, 0 otherwise.
 */
#define IC_IS_UINT(expr) \
    ({ \
        IC_ASSERT_CONSTANT(expr); \
        _IC_IS_UINT(expr); \
    })

/**
 * @brief Compile-time require expr is an unsigned integer.
 * @param expr The expression.
 * @note Expression is evaluated once and returned after evaluation.
 * @return The evaluated expression.
 */
#define IC_Z_REQUIRE_UINT(expr) \
    ({ \
        __auto_type const _ic_z_is_uint_expr_ = (expr); \
        IC_BUILD_ASSERT(_IC_IS_UINT(_ic_z_is_uint_expr_)); \
        _ic_z_is_uint_expr_; \
    })

/**
 * @brief Compile-time constant require unsigned integer.
 * @param expr The expression.
 * @note This requires that the expression is a compile-time constant to prevent
 *       multiple runtime evaluations of the expression.
 * @return The expression.
 */
#define IC_REQUIRE_UINT(expr) \
    ({ \
        IC_BUILD_ASSERT(IC_IS_UINT(expr), #expr " is not an unsigned integer type"); \
        expr; \
    })

#define _IC_IS_INT(expr) \
    (__builtin_types_compatible_p(int8_t, __typeof__(expr)) \
     || __builtin_types_compatible_p(signed char, __typeof__(expr)) \
     || __builtin_types_compatible_p(int16_t, __typeof__(expr)) \
     || __builtin_types_compatible_p(signed short int, __typeof__(expr)) \
     || __builtin_types_compatible_p(int32_t, __typeof__(expr)) \
     || __builtin_types_compatible_p(signed long int, __typeof__(expr)) \
     || __builtin_types_compatible_p(int64_t, __typeof__(expr)) \
     || __builtin_types_compatible_p(signed long long int, __typeof__(expr)))

/**
 * @brief Compile-time check if expr is a signed integer.
 * @param expr The expression.
 * @note This requires that the expression is a compile-time constant to prevent
 *       multiple runtime evaluations of the expression.
 * @return 1 if expr is a signed integer, 0 otherwise.
 */
#define IC_IS_INT(expr) \
    ({ \
        IC_ASSERT_CONSTANT(expr); \
        _IC_IS_INT(expr); \
    })

/**
 * @brief Compile-time constant require signed integer.
 * @param expr The expression.
 * @note This requires that the expression is a compile-time constant to prevent
 *       multiple runtime evaluations of the expression.
 * @return The expression.
 */
#define IC_REQUIRE_INT(expr) \
    ({ \
        IC_BUILD_ASSERT(IC_IS_INT(expr), #expr " is not a signed integer type"); \
        expr; \
    })

/**
 * @brief Compile-time constant check if expr is a floating point number.
 * @param expr The expression.
 * @note This requires that the expression is a compile-time constant to prevent
 *       multiple runtime evaluations of the expression.
 * @return 1 if expr is a floating point number, 0 otherwise.
 */
#define IC_IS_FP(expr) \
    ({ \
        IC_ASSERT_CONSTANT(expr); \
        (__builtin_types_compatible_p(float, __typeof__(expr)) \
         || __builtin_types_compatible_p(double, __typeof__(expr)) \
         || __builtin_types_compatible_p(long double, __typeof__(expr))); \
    })

/**
 * @brief Compile-time constant require floating point number.
 * @param expr The expression.
 * @note This requires that the expression is a compile-time constant to prevent
 *       multiple runtime evaluations of the expression.
 * @return The expression.
 */
#define IC_REQUIRE_FP(expr) \
    ({ \
        IC_BUILD_ASSERT(IC_IS_FP(IC_REQUIRE_CONSTANT(expr))); \
        expr; \
    })

#ifdef __cplusplus
}
#endif
