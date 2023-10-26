/*
 * Copyright (c) 2011-2014, Wind River Systems, Inc.
 * Copyright (c) 2023, Intercreate, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif


/* concatenate the values of the arguments into one */
#define _IC_Z_DO_CONCAT(x, y) x##y
#define _IC_Z_CONCAT(x, y) _IC_Z_DO_CONCAT(x, y)

#define _IC_Z_DO_STR(x) #x
#define _IC_Z_STR(x) _IC_Z_DO_STR(x)

/**
 * @brief Compile-time assertion.
 * @param expr An expression that is a compile-time constant.
 * @param msg Optional string to describe the assertion should it fail.
 */
#define IC_BUILD_ASSERT(expr, msg...) \
    enum _IC_Z_CONCAT(__build_assert_enum, __COUNTER__) { \
        _IC_Z_CONCAT(__build_assert, __COUNTER__) = 1 / !!(expr) \
    }
/* C++11 has static_assert built in */
#if defined(__cplusplus) && (__cplusplus >= 201103L)
#    undef IC_BUILD_ASSERT
/**
 * @brief Compile-time assertion.
 * @param expr An expression that is a compile-time constant.
 * @param msg Optional string to describe the assertion should it fail.
 */
#    define IC_BUILD_ASSERT(expr, msg...) static_assert(expr, "" msg)
/*
 * GCC 4.6 and higher have the C11 _Static_assert built in and its
 * output is easier to understand than the common IC_BUILD_ASSERT macros.
 * Don't use this in C++98 mode though (which we can hit, as
 * static_assert() is not available)
 */
#elif !defined(__cplusplus) \
    && ((__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)) || (__STDC_VERSION__) >= 201100)
#    undef IC_BUILD_ASSERT
/**
 * @brief Compile-time assertion.
 * @param expr An expression that is a compile-time constant.
 * @param msg Optional string to describe the assertion should it fail.
 */
#    define IC_BUILD_ASSERT(expr, msg...) (void) 0
#endif /* defined(__cplusplus) && (__cplusplus >= 201103L) */

#ifdef __cplusplus
}
#endif
