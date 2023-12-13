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

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tgmath.h>

#include "ic_macros/assert_constant.h"
#include "ic_macros/assert_type.h"
#include "ic_macros/pragma_message.h"
#include "zephyr/build_assert.h"

/** @brief Create the runtime version of the the macro that takes 1 argument. */
#define _IC_MAKE_SINGLE_EVAL_1(macro, arg1) \
    __builtin_constant_p(arg1) ? macro(arg1) : ({ \
        __auto_type const _##macro##_1_ = (arg1); \
        macro(_##macro##_1_); \
    })

/** @brief Create the runtime version of the the macro that takes 2 arguments. */
#define _IC_MAKE_SINGLE_EVAL_2(macro, arg1, arg2) \
    __builtin_constant_p(arg1) && __builtin_constant_p(arg2) ? macro(arg1, arg2) : ({ \
        __auto_type const _##macro##_1_ = (arg1); \
        __auto_type const _##macro##_2_ = (arg2); \
        macro(_##macro##_1_, _##macro##_2_); \
    })

/** @brief Create the runtime version of the the macro that takes 3 arguments. */
#define _IC_MAKE_SINGLE_EVAL_3(macro, arg1, arg2, arg3) \
    __builtin_constant_p(arg1) && __builtin_constant_p(arg2) && __builtin_constant_p(arg3) \
        ? macro(arg1, arg2, arg3) \
        : ({ \
              __auto_type const _##macro##_1_ = (arg1); \
              __auto_type const _##macro##_2_ = (arg2); \
              __auto_type const _##macro##_3_ = (arg3); \
              macro(_##macro##_1_, _##macro##_2_, _##macro##_3_); \
          })


/** @brief Number of bits that make up a type */
#define IC_NUM_BITS(t) (sizeof(t) * 8)

/** @brief Cast @p x, a pointer, to an unsigned integer. */
#define IC_POINTER_TO_UINT(x) ((uintptr_t) (x))
/** @brief Cast @p x, an unsigned integer, to a <tt>void*</tt>. */
#define IC_UINT_TO_POINTER(x) ((void *) (uintptr_t) (x))
/** @brief Cast @p x, a pointer, to a signed integer. */
#define IC_POINTER_TO_INT(x) ((intptr_t) (x))
/** @brief Cast @p x, a signed integer, to a <tt>void*</tt>. */
#define IC_INT_TO_POINTER(x) ((void *) (intptr_t) (x))

/**
 * @brief Create a contiguous bitmask starting at bit position @p l
 *        and ending at position @p h.
 */
#define IC_GENMASK32(h, l) (((~0UL) - (1UL << (l)) + 1) & (~0UL >> (32UL - 1 - (h))))

/**
 * @brief Create a contiguous 64-bit bitmask starting at bit position @p l
 *        and ending at position @p h.
 */
#define IC_GENMASK64(h, l) (((~0ULL) - (1ULL << (l)) + 1) & (~0ULL >> (64ULL - 1 - (h))))


/** @brief Only use in global scope; extract the Least Significant Bit from @p value. */
#define IC_G_LSB_GET(value) ((value) & -(value))

/** @brief Extract the Least Significant Bit from @p value. */
#define IC_LSB_GET(value) _IC_MAKE_SINGLE_EVAL_1(value)

/**
 * @brief Only use in global scope; extract a bitfield element from @p value corresponding to
 *	  the field mask @p mask.
 */
#define IC_G_FIELD_GET(mask, value) (((value) & (mask)) / IC_LSB_GET(mask))

/**
 * @brief Extract a bitfield element from @p value corresponding to
 *	  the field mask @p mask.
 */
#define IC_FIELD_GET(mask, value) _IC_MAKE_SINGLE_EVAL_2(IC_G_FIELD_GET, mask, value)

/**
 * @brief Only use in global scope; prepare a bitfield element using @p value with @p mask
 *representing its field position and width. The result should be combined with other fields using a
 *logical OR.
 */
#define IC_G_FIELD_PREP(mask, value) (((value) * IC_LSB_GET(mask)) & (mask))

/**
 * @brief Prepare a bitfield element using @p value with @p mask representing
 *	  its field position and width. The result should be combined
 *	  with other fields using a logical OR.
 */
#define IC_FIELD_PREP(mask, value) _IC_MAKE_SINGLE_EVAL_2(IC_G_FIELD_PREP, mask, value)

/** @brief 0 if @p cond is true-ish; causes a compile error otherwise. */
#define IC_ZERO_OR_COMPILE_ERROR(cond) ((int) sizeof(char[1 - 2 * !(cond)]) - 1)

#if !defined(__cplusplus)
/**
 * @brief Zero if @p array has an array type, a compile error otherwise
 *
 * @note This macro is available only from C, not C++.
 */
#    define _IC_IS_ARRAY(array) \
        IC_ZERO_OR_COMPILE_ERROR( \
            !__builtin_types_compatible_p(__typeof__(array), __typeof__(&(array)[0])) \
        )

/**
 * @brief Number of elements in the given @p array; the "length"
 *
 * @details Passing a pointer as @p array causes a compile error.
 *
 * @param array A C array (that has not decayed to a pointer)
 * @return unsigned int - number of elements in the array
 */
#    define IC_ARRAY_LENGTH(array) \
        (unsigned int) (_IC_IS_ARRAY(array) + (sizeof(array) / sizeof((array)[0])))

/**
 * @brief Size of the given @p array in 8-bit bytes
 *
 * @details Passing a pointer as @p array causes a compile error.
 *
 * @param array A C array (that has not decayed to a pointer)
 * @return size_t - size of the array in 8-bit bytes
 */
#    define IC_ARRAY_SIZE(array) (size_t)(_IC_IS_ARRAY(array) + sizeof(array))

#endif /* not __cplusplus */

/**
 * @brief Whether @p ptr is an element of @p array
 *
 * This macro can be seen as a slightly stricter version of @ref PART_OF_ARRAY
 * in that it also ensures that @p ptr is aligned to an array-element boundary
 * of @p array.
 *
 * In C, passing a pointer as @p array causes a compile error.
 *
 * @param array the array in question
 * @param ptr the pointer to check
 *
 * @return 1 if @p ptr is part of @p array, 0 otherwise
 */
#define IC_IS_ARRAY_ELEMENT(array, ptr) \
    ((ptr) && IC_POINTER_TO_UINT(array) <= IC_POINTER_TO_UINT(ptr) \
     && IC_POINTER_TO_UINT(ptr) < IC_POINTER_TO_UINT(&(array)[IC_ARRAY_LENGTH(array)]) \
     && (IC_POINTER_TO_UINT(ptr) - IC_POINTER_TO_UINT(array)) % sizeof((array)[0]) == 0)

/**
 * @brief Index of @p ptr within @p array
 *
 * @details This macro will return -1
 * when @p ptr does not fall into the range of @p array or when @p ptr
 * is not aligned to an array-element boundary of @p array.
 *
 * In C, passing a pointer as @p array causes a compile error.
 *
 * @param array the array in question
 * @param ptr pointer to an element of @p array
 *
 * @return -1 on error, or the array index of @p ptr within @p array, on success
 */
#define IC_ARRAY_INDEX(array, ptr) \
    IC_IS_ARRAY_ELEMENT(array, ptr) ? (__typeof__((array)[0]) *) (ptr) - (array) : -1

/**
 * @brief Check if a pointer @p ptr lies within @p array.
 *
 * @details In C but not C++, this causes a compile error if @p array is not an array
 * (e.g. if @p ptr and @p array are mixed up).
 *
 * @param array an array
 * @param ptr a pointer
 * @return 1 if @p ptr is part of @p array, 0 otherwise
 */
#define IC_PART_OF_ARRAY(array, ptr) \
    ((ptr) && IC_POINTER_TO_UINT(array) <= IC_POINTER_TO_UINT(ptr) \
     && IC_POINTER_TO_UINT(ptr) < IC_POINTER_TO_UINT(&(array)[IC_ARRAY_LENGTH(array)]))

/**
 * @brief Array-index of @p ptr within @p array, rounded down
 *
 * @details This macro behaves much like @ref IC_ARRAY_INDEX with the notable
 * difference that it accepts any @p ptr in the range of @p array rather than
 * exclusively a @p ptr aligned to an array-element boundary of @p array.
 *
 * This macro will return -1
 * when @p ptr does not fall into the range of @p array.
 *
 * In C, passing a pointer as @p array causes a compile error.
 *
 * @param array the array in question
 * @param ptr pointer to an element of @p array
 *
 * @return -1 on error, or the array index of @p ptr within @p array, on success
 */
#define IC_ARRAY_INDEX_FLOOR(array, ptr) \
    IC_PART_OF_ARRAY(array, ptr) \
    ? (IC_POINTER_TO_UINT(ptr) - IC_POINTER_TO_UINT(array)) / sizeof((array)[0]) : -1

/**
 * @brief Validate if two entities have a compatible type
 *
 * @param a the first entity to be compared
 * @param b the second entity to be compared
 * @return 1 if the two elements are compatible, 0 if they are not
 */
#define IC_SAME_TYPE(a, b) __builtin_types_compatible_p(__typeof__(a), __typeof__(b))

#ifndef __cplusplus
/**
 * @brief Validate IC_CONTAINER_OF parameters, only applies to C mode.
 */
#    define _IC_CONTAINER_OF_VALIDATE(ptr, type, field) \
        IC_BUILD_ASSERT( \
            IC_SAME_TYPE(*(ptr), ((type *) 0)->field) || IC_SAME_TYPE(*(ptr), void), \
            "pointer type mismatch in IC_CONTAINER_OF" \
        );
#else
#    define _IC_CONTAINER_OF_VALIDATE(ptr, type, field)
#endif

/**
 * @brief Get a pointer to a structure containing the element
 *
 * @details Example:
 *
 *	struct foo {
 *		int bar;
 *	};
 *
 *	struct foo my_foo;
 *	int * ptr = &my_foo.bar;
 *
 *	struct foo * container = IC_CONTAINER_OF(ptr, struct foo, bar);
 *
 * Above, @p container points at @p my_foo.
 *
 * @param ptr pointer to a structure element
 * @param type name of the type that @p ptr is an element of
 * @param field the name of the field within the struct @p ptr points to
 * @return a pointer to the structure that contains @p ptr
 */
#define IC_CONTAINER_OF(ptr, type, field) \
    ({ \
        _IC_CONTAINER_OF_VALIDATE(ptr, type, field) \
        ((type *) (((char *) (ptr)) - offsetof(type, field))); \
    })

/**
 * @brief Only use in global scope; value of integer @p x rounded up to the next multiple of @p
 * align.
 * @param x integer to round
 * @return the rounded integer
 */
#define IC_G_IROUND_UP(x, align) \
    ((((unsigned long) (x) + ((unsigned long) (align) -1)) / (unsigned long) (align)) \
     * (unsigned long) (align))

/**
 * @brief Value of integer @p x rounded up to the next multiple of @p align.
 * @param x integer to round
 * @return the rounded integer
 */
#define IC_IROUND_UP(x, align) _IC_MAKE_SINGLE_EVAL_2(IC_G_IROUND_UP, x, align)

/**
 * @brief Only use in global scope; value of integer @p x rounded down to the next multiple of @p
 * align.
 * @param x integer to round
 * @return the rounded integer
 */
#define IC_G_IROUND_DOWN(x, align) \
    (((unsigned long) (x) / (unsigned long) (align)) * (unsigned long) (align));

/**
 * @brief Value of integer @p x rounded down to the next multiple of @p align.
 * @param x integer to round
 * @return the rounded integer
 */
#define IC_IROUND_DOWN(x, align) _IC_MAKE_SINGLE_EVAL_2(IC_IROUND_DOWN, x, align)

/** @brief Value of @p x rounded up to the next word boundary. */
#define IC_WB_UP(x) IC_IROUND_UP(x, sizeof(void *))

/** @brief Value of @p x rounded down to the previous word boundary. */
#define IC_WB_DN(x) IC_IROUND_DOWN(x, sizeof(void *))


/**
 * @brief Only use in global scope; compile-time floating point ceiling of f32 (float), f64
 * (double), & f128 (long double).
 * @details Useful for casting to an integer:
 *      #define ROUNDED_UP IC_CEIL(MY_FLOATING_POINT_NUMBER)
 * @param x floating point number to ceiling.
 * @return the output of ceil(x); same type as the argument
 */
#define IC_G_CEIL(x) ceil(x)

/**
 * @brief Compile-time floating point ceiling of f32 (float), f64 (double), & f128 (long
 * double).
 * @details Useful for casting to an integer:
 *      #define ROUNDED_UP IC_CEIL(MY_FLOATING_POINT_NUMBER)
 * @note Generates compile error if x is not a compile-time constant; use ceil(x) from
 * <tgmath.h>.
 * @param x floating point number to ceiling.
 * @return the output of ceil(x); same type as the argument
 */
#define IC_CEIL(x) \
    ({ \
        IC_BUILD_ASSERT( \
            IC_SAME_TYPE(x, float) || IC_SAME_TYPE(x, double) || IC_SAME_TYPE(x, long double), \
            "Argument must be a floating point number!" \
        ); \
        /* use <tgmath.h> */ \
        IC_REQUIRE_CONSTANT(ceil(x)); \
    })

/**
 * @brief Only use in global scope; compile-time floating point floor of f32 (float), f64 (double),
 * & f128 (long double).
 * @details Useful for casting to an integer:
 *      #define ROUNDED_DOWN IC_FLOOR(MY_FLOATING_POINT_NUMBER)
 * @note Generates compile error if x is not a compile-time constant; use floor(x) from
 * <tgmath.h>.
 * @param x floating point number to floor.
 * @return the output of floor(x); same type as the argument
 */
#define IC_G_FLOOR(x) floor(x)

/**
 * @brief Compile-time floating point floor of f32 (float), f64 (double), & f128 (long double).
 * @details Useful for casting to an integer:
 *      #define ROUNDED_DOWN IC_FLOOR(MY_FLOATING_POINT_NUMBER)
 * @note Generates compile error if x is not a compile-time constant; use floor(x) from
 * <tgmath.h>.
 * @param x floating point number to floor.
 * @return the output of floor(x); same type as the argument
 */
#define IC_FLOOR(x) \
    ({ \
        IC_BUILD_ASSERT( \
            IC_SAME_TYPE(x, float) || IC_SAME_TYPE(x, double) || IC_SAME_TYPE(x, long double), \
            "Argument must be a floating point number!" \
        ); \
        /* use <tgmath.h> */ \
        IC_REQUIRE_CONSTANT(floor(x)); \
    })

/**
 * @brief Only use in global scope; round of f32 (float), f64 (double), & f128 (long double).
 * @details Useful for casting to an integer:
 *  uint32_t const ROUNDED = (uint32_t) IC_G_ROUND(MY_FLOATING_POINT_NUMBER)
 * @note Tie-breaks .5 (1/2) AWAY FROM ZERO for positive and negative numbers,
 *  e.g. 0.5 -> 1 and -0.5 -> -1.
 * @param x floating point number to round.
 * @return The rounded number
 */
#define IC_G_ROUND(x) (__typeof__(x)) (int64_t) ((x) + ((x) >= 0 ? 0.5 : -0.5))

/**
 * @brief Round of f32 (float), f64 (double), & f128 (long double).
 * @details Useful for casting to an integer:
 *  #define ROUNDED (uint32_t) IC_ROUND(MY_FLOATING_POINT_NUMBER)
 * @note Generates compile error if x is not a compile-time constant; use
 *  round*(x) from <math.h> or  <tgmath.h>
 * @note Tie-breaks .5 (1/2) AWAY FROM ZERO for positive and negative numbers,
 *  e.g. 0.5 -> 1 and -0.5 -> -1.
 * @param x floating point number to round.
 * @return The rounded number
 */
#define IC_ROUND(x) \
    ({ \
        IC_BUILD_ASSERT( \
            IC_SAME_TYPE(x, float) || IC_SAME_TYPE(x, double) || IC_SAME_TYPE(x, long double), \
            "Argument must be a floating point number!" \
        ); /* unclear that ARM's <tgmath.h> implements round() */ \
        IC_BUILD_ASSERT((x) >= INT64_MIN || (x) <= INT64_MAX); \
        IC_REQUIRE_CONSTANT(IC_G_ROUND(x)); \
    })

/**
 * @brief Only use in global scope; divide and round up.
 *
 * @details Example:
 * @code{.c}
 * IC_DIV_ROUND_UP(1, 2); // 1
 * IC_DIV_ROUND_UP(3, 2); // 2
 * @endcode
 *
 * @param n Numerator.
 * @param d Denominator.
 *
 * @return The result of @p n / @p d, rounded up.
 */
#define IC_G_DIV_ROUND_UP(n, d) (((n) + (d) -1) / (d))

/**
 * @brief Divide and round up.
 *
 * @details Example:
 * @code{.c}
 * IC_DIV_ROUND_UP(1, 2); // 1
 * IC_DIV_ROUND_UP(3, 2); // 2
 * @endcode
 *
 * @param n Numerator.
 * @param d Denominator.
 *
 * @return The result of @p n / @p d, rounded up.
 *
 * @note Expressions are only evaluated once.
 */
#define IC_DIV_ROUND_UP(n, d) _IC_MAKE_SINGLE_EVAL_2(IC_G_DIV_ROUND_UP, n, d)

/**
 * @brief Only use in global scope; divide and round to the nearest integer.
 *
 * @details Example:
 * @code{.c}
 * IC_DIV_ROUND_CLOSEST(5, 2); // 3
 * IC_DIV_ROUND_CLOSEST(5, -2); // -3
 * IC_DIV_ROUND_CLOSEST(5, 3); // 2
 * @endcode
 *
 * @param n Numerator.
 * @param d Denominator.
 *
 * @return The result of @p n / @p d, rounded to the nearest integer.
 */
#define IC_G_DIV_ROUND_CLOSEST(n, d) \
    ((((n) < 0) ^ ((d) < 0)) ? ((n) - ((d) / 2)) / (d) : ((n) + ((d) / 2)) / (d))

/**
 * @brief Divide and round to the nearest integer.
 *
 * @details Example:
 * @code{.c}
 * IC_DIV_ROUND_CLOSEST(5, 2); // 3
 * IC_DIV_ROUND_CLOSEST(5, -2); // -3
 * IC_DIV_ROUND_CLOSEST(5, 3); // 2
 * @endcode
 *
 * @param n Numerator.
 * @param d Denominator.
 *
 * @return The result of @p n / @p d, rounded to the nearest integer.
 *
 * @note Expressions are only evaluated once.
 */
#define IC_DIV_ROUND_CLOSEST(n, d) _IC_MAKE_SINGLE_EVAL_2(IC_G_DIV_ROUND_CLOSEST, n, d)

/**
 * @brief Only use in global scope; obtain the maximum of two values.
 *
 * @param a First value.
 * @param b Second value.
 *
 * @returns Maximum value of @p a and @p b.
 */
#define IC_G_MAX(a, b) (((a) > (b)) ? (a) : (b))

/**
 * @brief Obtain the maximum of two values.
 *
 * @param a First value.
 * @param b Second value.
 *
 * @returns Maximum value of @p a and @p b.
 *
 * @note Expressions are only evaluated once.
 */
#define IC_MAX(a, b) _IC_MAKE_SINGLE_EVAL_2(IC_G_MAX, a, b)


/**
 * @brief Only use in global scope; obtain the minimum of two values.
 *
 * @param a First value.
 * @param b Second value.
 *
 * @returns Minimum value of @p a and @p b.
 */
#define IC_G_MIN(a, b) (((a) < (b)) ? (a) : (b))

/**
 * @brief Obtain the minimum of two values.
 *
 * @param a First value.
 * @param b Second value.
 *
 * @returns Minimum value of @p a and @p b.
 *
 * @note Expressions are only evaluated once.
 */
#define IC_MIN(a, b) _IC_MAKE_SINGLE_EVAL_2(IC_G_MIN, a, b)

/**
 * @brief Only use in global scope; clamp a value to a given range.
 *
 * @param val Value to be clamped.
 * @param low Lowest allowed value (inclusive).
 * @param high Highest allowed value (inclusive).
 *
 * @returns Clamped value.
 */
#define IC_G_CLAMP(val, low, high) (((val) <= (low)) ? (low) : IC_MIN(val, high))

/**
 * @brief Clamp a value to a given range.
 *
 * @param val Value to be clamped.
 * @param low Lowest allowed value (inclusive).
 * @param high Highest allowed value (inclusive).
 *
 * @returns Clamped value.
 *
 * @note Expressions are only evaluated once.
 */
#define IC_CLAMP(val, low, high) _IC_MAKE_SINGLE_EVAL_3(IC_G_CLAMP, val, low, high)

/**
 * @brief Only use in global scope; checks if a value is within range.
 *
 * @param val Value to be checked.
 * @param min Lower bound (inclusive).
 * @param max Upper bound (inclusive).
 *
 * @retval true If value is within range
 * @retval false If the value is not within range
 */
#define IC_G_IN_RANGE(val, min, max) \
    ((__typeof__(val)) -1) > 0 ? ((val) <= (max)) : ((val) >= (min) && (val) <= (max))

/**
 * @brief Checks if a value is within range.
 *
 * @param val Value to be checked.
 * @param min Lower bound (inclusive).
 * @param max Upper bound (inclusive).
 *
 * @retval true If value is within range
 * @retval false If the value is not within range
 *
 * @note Expressions are only evaluated once.
 */
#define IC_IN_RANGE(val, min, max) _IC_MAKE_SINGLE_EVAL_3(IC_G_IN_RANGE, val, min, max)

/**
 * @brief Only use in global scope; compute integer value of log2(x)
 *
 * @param x An unsigned integral value to compute logarithm of (positive only)
 *
 * @return log2(x)
 */
#define IC_G_ILOG2(x) \
    (sizeof(__typeof__(x)) > 4 ? (64 - __builtin_clzll(x) - 1) : (32 - __builtin_clz(x) - 1))

/**
 * @brief Compute integer value log2(x)
 *
 * @param x An unsigned integral value to compute logarithm of (positive only)
 *
 * @return log2(x) or -1 if x < 1
 */
#define IC_ILOG2(x) \
    __builtin_constant_p(x) ? IC_G_ILOG2(x) : ({ \
        __auto_type const _ic_z_ilog2_x_ = (IC_Z_REQUIRE_UINT(x)); \
        _ic_z_ilog2_x_ < 1 ? -1 : IC_G_ILOG2(_ic_z_ilog2_x_); \
    })

/**
 * @brief Only use in global scope; compute ceil(log2(x))
 *
 * @param x An unsigned integral value
 *
 * @return ceil(log2(x)) when 1 <= x <= max(type(x)), 0 when x < 1
 */
#define IC_G_LOG2CEIL(x) (x) < 1 ? 0 : IC_G_ILOG2((x) -1) + 1

/**
 * @brief Compute ceil(log2(x))
 *
 * @param x An unsigned integral value
 *
 * @return ceil(log2(x)) when 1 <= x <= max(type(x)), 0 when x < 1
 */
#define IC_LOG2CEIL(x) _IC_MAKE_SINGLE_EVAL_1(IC_G_LOG2CEIL, x)

/**
 * @brief Only use in global scope; compute next highest power of two
 *
 * Equivalent to 2^ceil(log2(x))
 *
 * @param x An unsigned integral value
 *
 * @return 2^ceil(log2(x)) or 0 if 2^ceil(log2(x)) would saturate 64-bits
 */
#define IC_G_NHPOT(x) ((x) < 1 ? 1 : ((x) > (1ULL << 63) ? 0 : 1ULL << IC_G_LOG2CEIL(x)))

/**
 * @brief Compute next highest power of two
 *
 * Equivalent to 2^ceil(log2(x))
 *
 * @note This macro expands its argument multiple times (to permit use
 *       in constant expressions), which must not have side effects.
 *
 * @param x An unsigned integral value
 *
 * @return 2^ceil(log2(x)) or 0 if 2^ceil(log2(x)) would saturate 64-bits
 */
#define IC_NHPOT(x) _IC_MAKE_SINGLE_EVAL_1(IC_G_NHPOT, x)

/**
 * @brief Only use in global scope; calculate power of two ceiling for some nonzero value
 *
 * @param x Nonzero unsigned long value
 * @return X rounded up to the next power of two
 */
#define IC_G_POW2_CEIL(x) ((x) <= 2UL ? (x) : (1UL << (8 * sizeof(long) - __builtin_clzl((x) -1))))

/**
 * @brief Calculate power of two ceiling for some nonzero value
 *
 * @param x Nonzero unsigned long value
 * @return X rounded up to the next power of two
 */
#define IC_POW2_CEIL(x) _IC_MAKE_SINGLE_EVAL_1(IC_G_POW2_CEIL, x)

/**
 * @brief Only use in global scope; check whether or not a value is a power of 2
 *
 * @param x The value to check
 * @return true if x is a power of 2, false otherwise
 */
#define IC_G_IS_POW2(x) (((x) != 0) && (((x) & ((x) -1)) == 0))

/**
 * @brief Check whether or not a value is a power of 2
 *
 * @param x The value to check
 * @return true if x is a power of 2, false otherwise
 */
#define IC_IS_POW2(x) _IC_MAKE_SINGLE_EVAL_1(IC_G_IS_POW2)

/** @brief Unsigned integer with bit position @p n set. */
#define IC_BIT(n) (1UL << (n))

/** @brief 64-bit unsigned integer with bit position @p n set. */
#define IC_BIT64(n) (1ULL << (n))

/**
 * @brief Only use in global scope; set or clear a bit depending on a boolean value
 *
 * @param var Variable to be altered
 * @param bit Bit number
 * @param set if 0, clears @p bit in @p var; any other value sets @p bit
 *
 * @return The value of var with the specified bit set or cleared
 */
#define IC_G_WRITE_BIT(var, bit, set) (set) ? ((var) | IC_BIT(bit)) : ((var) & ~IC_BIT(bit))

/**
 * @brief Set or clear a bit depending on a boolean value
 *
 * @param var Variable to be altered
 * @param bit Bit number
 * @param set if 0, clears @p bit in @p var; any other value sets @p bit
 *
 * @return The value of var with the specified bit set or cleared
 */
#define IC_WRITE_BIT(var, bit, set) _IC_MAKE_SINGLE_EVAL_3(IC_G_WRITE_BIT, var, bit, set)

/**
 * @brief Bit mask with bits 0 through n-1 (inclusive) set,
 * or 0 if @p n is 0.
 */
#define IC_BIT_MASK(n) (IC_BIT(n) - 1UL)

/**
 * @brief 64-bit bit mask with bits 0 through n-1 (inclusive) set,
 * or 0 if @p n is 0.
 */
#define IC_BIT64_MASK(n) (IC_BIT64(n) - 1ULL)

/**
 * @brief Only use in global scope; check if bits are set continuously from the specified bit
 *
 * @note The macro is not dependent on the bit-width.
 *
 * @param m Check whether the bits are set continuously or not.
 * @param s Specify the lowest bit for that is continuously set bits.
 */
#define IC_G_IS_SHIFTED_BIT_MASK(m, s) (!(((m) >> (s)) & (((m) >> (s)) + 1U)))

/**
 * @brief Check if bits are set continuously from the specified bit
 *
 * @note The macro is not dependent on the bit-width.
 *
 * @param m Check whether the bits are set continuously or not.
 * @param s Specify the lowest bit for that is continuously set bits.
 */
#define IC_IS_SHIFTED_BIT_MASK(m, s) _IC_MAKE_SINGLE_EVAL_2(IC_G_IS_SHIFTED_BIT_MASK, m, s)

/**
 * @brief Only use in global scope; check if bits are set continuously from the LSB.
 *
 * @param m Check whether the bits are set continuously from LSB.
 */
#define IC_G_IS_BIT_MASK(m) IC_G_IS_SHIFTED_BIT_MASK(m, 0)

/**
 * @brief Check if bits are set continuously from the LSB.
 *
 * @param m Check whether the bits are set continuously from LSB.
 */
#define IC_IS_BIT_MASK(m) IC_IS_SHIFTED_BIT_MASK(m, 0)

/**
 * @brief Only use in global scope; 24-bit byte swap.
 *
 * @param x 24-bit integer to byte swap.
 */
#define IC_G_BSWAP24(x) \
    (((x) >> 16) & 0x0000FF) | (((x) >> 00) & 0x00FF00) | ((((x) & 0x0000FF) << 16))

/**
 * @brief 24-bit byte swap.
 *
 * @param x 24-bit integer to byte swap.
 */
#define IC_BSWAP24(x) _IC_MAKE_SINGLE_EVAL_1(IC_G_BSWAP24, x)

#ifdef __cplusplus
}
#endif
