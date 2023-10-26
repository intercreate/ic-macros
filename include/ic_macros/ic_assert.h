/*
 * Copyright (c) 2023, Intercreate, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @brief Runtime assertion failed; implementation should be provided by user.
 * @param  ... Optional arguments, like a debug message.
 */
void _ic_assert_fail(const char * file, int line, const char * expr, const char * msg);

/**
 * @brief Runtime assertion.
 * @param expr An expression; if it evaluates to 0 then _ic_assert_fail() is called.
 * @param  msg... An optional debug message describing the assert.
 */
#define IC_ASSERT(expr, msg...) \
    (expr) == 0 ? _ic_assert_fail(__FILE__, __LINE__, #expr, ""##msg) : ({})

/**
 * @brief Runtime assertion that returns the evaluated expression.
 * @param expr An expression.
 * @param condition The condition that the result of the expression is held to, e.g. >= 0
 * @param  msg... An optional debug message describing the assert.
 * @return The evaluated expression, expr.
 */
#define IC_ASSERT_CONDITION(expr, condition, msg...) \
    ({ \
        __auto_type const _IC_ASSERT_expr_ = (expr); \
        (_IC_ASSERT_expr_ condition) ? _ic_assert_fail(__FILE__, __LINE__, #expr, ""##msg) \
                                     : _IC_ASSERT_expr_; \
    })
