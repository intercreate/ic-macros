/*
 * Copyright (c) 2023, Intercreate, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */


#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "zephyr/build_assert.h"


/**
 * @brief Assert that the expression is a compile-time constant.
 * @details Raises a compile error if the expression is not constant.
 * @param expr expression
 */
#define IC_ASSERT_CONSTANT(expr) \
    IC_BUILD_ASSERT(__builtin_constant_p(expr), #expr " is not a compile-time constant.")

/**
 * @brief Require that the expression is a compile-time constant before returning it unchanged.
 * @details Raises a compile error if the expression is not constant.
 * @param expr expression
 * @return The same expression provided as argument.
 */
#define IC_REQUIRE_CONSTANT(expr) \
    ({ \
        IC_ASSERT_CONSTANT(expr); \
        expr; \
    })

/**
 * @brief Assert that the expression is not a compile-time constant.
 * @details Raises a compile error if the expression is constant.
 * @param expr expression
 */
#define IC_ASSERT_NOT_CONSTANT(expr) \
    IC_BUILD_ASSERT(!__builtin_constant_p(expr), #expr " is a compile-time constant.")

/**
 * @brief Require that the expression is not a compile-time constant before returning it unchanged.
 * @details Raises a compile error if the expression is constant.
 * @param expr expression
 * @return The same expression provided as argument.
 */
#define IC_REQUIRE_NOT_CONSTANT(expr) \
    ({ \
        IC_ASSERT_NOT_CONSTANT(expr); \
        expr; \
    })

#ifdef __cplusplus
}
#endif
