/*
 * Copyright (c) 2023, Intercreate, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @brief Runtime assertion failed; implementation should be provided by user.
 * @param  ... Optional arguments, like a debug message.
 */
void _ic_assert_fail(long long int expr, ...);

/**
 * @brief Runtime assertion.
 * @param expr An expression; if it evaluates to 0 then _ic_assert_fail() is called.
 * @param  ... Optional arguments, like a debug message.
 * @return The evaluated expression.
 */
#define IC_ASSERT(expr, args...) \
    ({ \
        __auto_type const _IC_ASSERT_expr_ = (expr); \
        _IC_ASSERT_expr_ == 0 ? _ic_assert_fail(_IC_ASSERT_expr_, ##args) : _IC_ASSERT_expr_; \
    })
