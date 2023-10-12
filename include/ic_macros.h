/*
 * Copyright (c) 2023, Intercreate, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Zephyr Util Macros
 *      Copyright (c) 2011-2014, Wind River Systems, Inc.
 *      Copyright (c) 2021, Nordic Semiconductor ASA
 *
 *      SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "ic_macros/assert_constant.h"
#include "ic_macros/assert_type.h"
#include "ic_macros/enum_cast.h"
#include "ic_macros/integer_cast.h"
#include "zephyr/build_assert.h"
#include "zephyr/util.h"


/**
 * @brief Absolute value.
 * @note Arguments are evaluated more than once.
 * @returns The absolute value of the argument.
 */
#define IC_ABS(x) ((x) < 0 ? (-(x)) : (x))

#define IC_ANSI_RED "\x1b[31m"
#define IC_ANSI_GREEN "\x1b[32m"
#define IC_ANSI_YELLOW "\x1b[33m"
#define IC_ANSI_BLUE "\x1b[34m"
#define IC_ANSI_MAGENTA "\x1b[95m"
#define IC_ANSI_CYAN "\x1b[96m"
#define IC_ANSI_BOLD "\x1b[1m"
#define IC_ANSI_DIM "\x1b[2m"
#define IC_ANSI_DIM2 "\x1b[38;5;241m"
#define IC_ANSI_NONE ""
#define IC_ANSI_RESET "\x1b[0m"

/**
 * @brief Inline the function regardless of optimization level.
 * @details Generally, functions are not inlined unless optimization is
 * specified. For functions declared inline, this attribute inlines the
 * function independent of any restrictions that otherwise apply to inlining.
 * Failure to inline such a function is diagnosed as an error. Note that if
 * such a function is called indirectly the compiler may or may not inline it
 * depending on optimization level and a failure to inline an indirect call may
 * or may not be diagnosed.
 */
#define IC_INLINE inline __attribute__((always_inline))

/**
 * @brief The packed attribute specifies that a variable or structure field
 * should have the smallest possible alignment—one byte for a variable, and one
 * bit for a field, unless you specify a larger value with the aligned
 * attribute.
 */
#define IC_PACK __attribute__((packed))

/**
 * @brief Calls to functions whose return value is not affected by changes to
 * the observable state of the program and that have no observable effects on
 * such state other than to return a value may lend themselves to optimizations
 * such as common subexpression elimination. Declaring such functions with the
 * const attribute allows GCC to avoid emitting some calls in repeated
 * invocations of the function with the same argument values.
 *
 * @details For example,
 *      int square (int) __attribute__ ((const));
 * tells GCC that subsequent calls to function square with the same argument
 * value can be replaced by the result of the first call regardless of the
 * statements in between.
 *
 * The const attribute prohibits a function from reading objects that affect
 * its return value between successive invocations. However, functions declared
 * with the attribute can safely read objects that do not change their return
 * value, such as non-volatile constants.
 *
 * The const attribute imposes greater restrictions on a function’s definition
 * than the similar pure attribute. Declaring the same function with both the
 * const and the pure attribute is diagnosed. Because a const function cannot
 * have any observable side effects it does not make sense for it to return void.
 * Declaring such a function is diagnosed.
 *
 * @note Note that a function that has pointer arguments and examines the data pointed
 * to must not be declared const if the pointed-to data might change between
 * successive invocations of the function. In general, since a function cannot
 * distinguish data that might change from data that cannot, const functions
 * should never take pointer or, in C++, reference arguments. Likewise, a
 * function that calls a non-const function usually must not be const itself.
 */
#define IC_CONST __attribute__((const))

/**
 * @brief Calls to functions that have no observable effects on the state of
 * the program other than to return a value may lend themselves to optimizations
 * such as common subexpression elimination. Declaring such functions with the
 * pure attribute allows GCC to avoid emitting some calls in repeated invocations
 * of the function with the same argument values.
 *
 * The pure attribute prohibits a function from modifying the state of the program
 * that is observable by means other than inspecting the function’s return value.
 * However, functions declared with the pure attribute can safely read any
 * non-volatile objects, and modify the value of objects in a way that does not
 * affect their return value or the observable state of the program.
 *
 * @details For example,
 *      int hash (char *) __attribute__ ((pure));
 * tells GCC that subsequent calls to the function hash with the same string can
 * be replaced by the result of the first call provided the state of the program
 * observable by hash, including the contents of the array itself, does not change
 * in between. Even though hash takes a non-const pointer argument it must not
 * modify the array it points to, or any other object whose value the rest of the
 * program may depend on. However, the caller may safely change the contents of
 * the array between successive calls to the function (doing so disables the
 * optimization). The restriction also applies to member objects referenced by the
 * this pointer in C++ non-static member functions.
 *
 * Some common examples of pure functions are strlen or memcmp. Interesting non-pure
 * functions are functions with infinite loops or those depending on volatile memory
 * or other system resource, that may change between consecutive calls (such as the
 * standard C feof function in a multithreading environment).
 *
 * @note The pure attribute imposes similar but looser restrictions on a function’s
 * definition than the const attribute: pure allows the function to read any
 * non-volatile memory, even if it changes in between successive invocations of the
 * function. Declaring the same function with both the pure and the const attribute
 * is diagnosed. Because a pure function cannot have any observable side effects it
 * does not make sense for such a function to return void. Declaring such a
 * function is diagnosed.
 */
#define IC_PURE __attribute__((pure))

#ifdef __cplusplus
}
#endif
