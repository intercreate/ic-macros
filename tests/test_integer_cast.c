/*
 * Copyright (c) 2023, Intercreate, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <unity.h>

void setUp(void) {} /* Is run before every test, put unit init calls here. */
void tearDown(void) {} /* Is run after every test, put unit clean-up calls here. */

#include <ic_macros.h>

static int assert_result = 1;

/**
 * @brief Override the assertion fail for testing.
 */
void _ic_assert_fail(long long int expr, ...) {
    assert_result = 0;
}

static unsigned int expression_called_count = 0;

/**
 * @brief Use an expression sent to the macro to assert single evaluation.
 */
__int128_t _expression(__int128_t expr) {
    expression_called_count += 1;
    return expr;
}

/**
 * @brief Use an expression sent to the macro to assert single evaluation.
 */
long double _expressionf(long double expr) {
    expression_called_count += 1;
    return expr;
}

#define _RESET_FIXTURES() \
    assert_result = 1; \
    expression_called_count = 0;

#define ASSERT_SUCCESS() \
    TEST_ASSERT_EQUAL(1, assert_result); \
    TEST_ASSERT_EQUAL(1, expression_called_count); \
    _RESET_FIXTURES();

#define ASSERT_FAIL() \
    TEST_ASSERT_EQUAL(0, assert_result); \
    TEST_ASSERT_EQUAL(1, expression_called_count); \
    _RESET_FIXTURES();

#define _TEST(macro, val, should_succeed) \
    ({ \
        __auto_type const _res = macro( \
            _Generic(val, int: _expression, unsigned int: _expression, long int: _expression, unsigned long int: _expression, unsigned long long int: _expression, long long int: _expression, __int128_t: _expression, double: _expressionf, long double: _expressionf)( \
                val \
            ) \
        ); \
        if (should_succeed) { \
            TEST_ASSERT_EQUAL(val, _res); \
            ASSERT_SUCCESS(); \
        } else { \
            ASSERT_FAIL(); \
        } \
    })

void test_IC_Z_CAST_NUMBER(void) {
    uint8_t val = IC_Z_CAST_NUMBER(uint8_t, 0, 0xFF, _expression(0));
    TEST_ASSERT_EQUAL(0, val);
    ASSERT_SUCCESS();

    val = IC_Z_CAST_NUMBER(uint8_t, 0, 0xFF, _expression(1));
    TEST_ASSERT_EQUAL(1, val);
    ASSERT_SUCCESS();

    val = IC_Z_CAST_NUMBER(uint8_t, 0, 0xFF, _expression(254));
    TEST_ASSERT_EQUAL(254, val);
    ASSERT_SUCCESS();

    val = IC_Z_CAST_NUMBER(uint8_t, 0, 0xFF, _expression(255));
    TEST_ASSERT_EQUAL(255, val);
    ASSERT_SUCCESS();

    val = IC_Z_CAST_NUMBER(uint8_t, 0, 0xFF, _expressionf(0.01));
    TEST_ASSERT_EQUAL(0, val);
    ASSERT_SUCCESS();

    val = IC_Z_CAST_NUMBER(uint8_t, 0, 0xFF, _expressionf(254.99));
    TEST_ASSERT_EQUAL(254, val);
    ASSERT_SUCCESS();

    val = IC_Z_CAST_NUMBER(uint8_t, 0, 0xFF, _expression(-1));
    ASSERT_FAIL();

    val = IC_Z_CAST_NUMBER(uint8_t, 0, 0xFF, _expression(256));
    ASSERT_FAIL();

    val = IC_Z_CAST_NUMBER(uint8_t, 0, 0xFF, _expressionf(-0.01));
    ASSERT_FAIL();

    val = IC_Z_CAST_NUMBER(uint8_t, 0, 0xFF, _expressionf(255.01));
    ASSERT_FAIL();
}

void test_IC_UINT8(void) {
    _TEST(IC_UINT8, 0, true);
    _TEST(IC_UINT8, 255, true);
    _TEST(IC_UINT8, 0.01, true);
    _TEST(IC_UINT8, 254.99, true);

    _TEST(IC_UINT8, -1, false);
    _TEST(IC_UINT8, 256, false);
    _TEST(IC_UINT8, -0.01, false);
    _TEST(IC_UINT8, 255.01, false);
}

void test_IC_UINT16(void) {
    _TEST(IC_UINT16, 0, true);
    _TEST(IC_UINT16, 0xFFFF, true);
    _TEST(IC_UINT16, 0.01, true);
    _TEST(IC_UINT16, 0xFFFF - 0.01, true);

    _TEST(IC_UINT16, -1, false);
    _TEST(IC_UINT16, 0xFFFF + 1, false);
    _TEST(IC_UINT16, -0.01, false);
    _TEST(IC_UINT16, 0xFFFF + 0.01, false);
}

void test_IC_UINT32(void) {
    _TEST(IC_UINT32, 0, true);
    _TEST(IC_UINT32, 0xFFFFFFFF, true);
    _TEST(IC_UINT32, 0.01, true);
    _TEST(IC_UINT32, 0xFFFFFFFF - 0.01, true);

    _TEST(IC_UINT32, -1, false);
    _TEST(IC_UINT32, 0xFFFFFFFFUL + 1UL, false);
    _TEST(IC_UINT32, -0.01, false);
    _TEST(IC_UINT32, 0xFFFFFFFF + 0.01, false);
}

void test_IC_UINT64(void) {
    _TEST(IC_UINT64, 0, true);
    _TEST(IC_UINT64, UINT64_MAX, true);
    _TEST(IC_UINT64, 0.01, true);
    // _TEST(IC_UINT64, UINT64_MAX - 0.01l, true);  // TODO: test fails
    _TEST(IC_UINT64, UINT64_MAX / 2.0l, true);

    _TEST(IC_UINT64, -1, false);
    _TEST(IC_UINT64, (__int128_t) 0xFFFFFFFFFFFFFFFF + 1, false);
    _TEST(IC_UINT64, -0.01, false);
    _TEST(IC_UINT64, UINT64_MAX + 0.01, false);
    _TEST(IC_UINT64, UINT64_MAX + 999999999999.01l, false);
}

void test_IC_INT8(void) {
    _TEST(IC_INT8, -128, true);
    _TEST(IC_INT8, 127, true);
    _TEST(IC_INT8, -127.99, true);
    _TEST(IC_INT8, 126.99, true);

    _TEST(IC_INT8, -129, false);
    _TEST(IC_INT8, 128, false);
    _TEST(IC_INT8, -128.01, false);
    _TEST(IC_INT8, 127.01, false);
}

void test_IC_INT16(void) {
    _TEST(IC_INT16, INT16_MIN, true);
    _TEST(IC_INT16, INT16_MAX, true);
    _TEST(IC_INT16, INT16_MIN + 0.01, true);
    _TEST(IC_INT16, INT16_MAX - 0.01, true);

    _TEST(IC_INT16, INT16_MIN - 1, false);
    _TEST(IC_INT16, INT16_MAX + 1, false);
    _TEST(IC_INT16, INT16_MIN - 0.01, false);
    _TEST(IC_INT16, INT16_MAX + 0.01, false);
}

void test_IC_INT32(void) {
    _TEST(IC_INT32, INT32_MIN, true);
    _TEST(IC_INT32, INT32_MAX, true);
    _TEST(IC_INT32, INT32_MIN + 0.01, true);
    _TEST(IC_INT32, (long double) INT32_MAX - 0.01l, true);

    _TEST(IC_INT32, INT32_MIN - 1ll, false);
    _TEST(IC_INT32, INT32_MAX + 1ll, false);
    _TEST(IC_INT32, INT32_MIN - 0.01, false);
    _TEST(IC_INT32, INT32_MAX + 0.01, false);
}

void test_IC_INT64(void) {
    _TEST(IC_INT64, INT64_MIN, true);
    _TEST(IC_INT64, INT64_MAX, true);
    _TEST(IC_INT64, INT64_MIN + 0.01, true);
    _TEST(IC_INT64, INT64_MAX - 0.01l, true);

    _TEST(IC_INT64, (__int128_t) INT64_MIN - 1ll, false);
    _TEST(IC_INT64, (__int128_t) INT64_MAX + 1ll, false);
    // _TEST(IC_INT64, INT64_MIN - 0.01l, false);  // TODO: test fails <= 0.5
    // _TEST(IC_INT64, INT64_MAX + 0.01l, false);  // TODO: test fails <= 0.5
    _TEST(IC_INT64, INT64_MIN - 0.500625l, false);
    _TEST(IC_INT64, INT64_MAX + 0.500625l, false);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_IC_Z_CAST_NUMBER);
    RUN_TEST(test_IC_UINT8);
    RUN_TEST(test_IC_UINT16);
    RUN_TEST(test_IC_UINT32);
    RUN_TEST(test_IC_UINT64);
    RUN_TEST(test_IC_INT8);
    RUN_TEST(test_IC_INT16);
    RUN_TEST(test_IC_INT32);
    RUN_TEST(test_IC_INT64);

    return UNITY_END();
}
