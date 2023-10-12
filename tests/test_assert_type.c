/*
 * Copyright (c) 2023, Intercreate, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <unity.h>

void setUp(void) {} /* Is run before every test, put unit init calls here. */
void tearDown(void) {} /* Is run after every test, put unit clean-up calls here. */

#include <ic_macros.h>

#include "helpers.h"


void test_IC_ASSERT_TYPE(void) {
    IC_ASSERT_TYPE(uint8_t, (uint8_t) 1);
    IC_ASSERT_TYPE(uint16_t, (uint16_t const) 1);
    IC_ASSERT_TYPE(uint32_t const, (uint32_t const) 1);
    IC_ASSERT_TYPE(uint64_t, (uint64_t) 1);
    IC_ASSERT_TYPE(int8_t, (int8_t const) 1);
    IC_ASSERT_TYPE(int16_t, (int16_t) 1);
    IC_ASSERT_TYPE(int32_t const, (int32_t) 1);
    IC_ASSERT_TYPE(int64_t const, (int64_t) 1);
    IC_ASSERT_TYPE(float, (float) 1);
    IC_ASSERT_TYPE(double, (double) 1);
    IC_ASSERT_TYPE(long double, (long double) 1);

    struct my_struct {
        uint8_t one;
        uint8_t two;
    };
    IC_ASSERT_TYPE(struct my_struct, ((struct my_struct const){.one = 1, .two = 2}));
}

void test_IC_REQUIRE_TYPE(void) {
    TEST_ASSERT_EQUAL(1, IC_REQUIRE_TYPE(uint8_t, (uint8_t) 1));
    TEST_ASSERT_EQUAL(1, IC_REQUIRE_TYPE(uint16_t, (uint16_t const) 1));
    TEST_ASSERT_EQUAL(1, IC_REQUIRE_TYPE(uint32_t const, (uint32_t const) 1));
    TEST_ASSERT_EQUAL(1, IC_REQUIRE_TYPE(uint64_t, (uint64_t) 1));
    TEST_ASSERT_EQUAL(1, IC_REQUIRE_TYPE(int8_t, (int8_t const) 1));
    TEST_ASSERT_EQUAL(1, IC_REQUIRE_TYPE(int16_t, (int16_t) 1));
    TEST_ASSERT_EQUAL(1, IC_REQUIRE_TYPE(int32_t const, (int32_t) 1));
    TEST_ASSERT_EQUAL(1, IC_REQUIRE_TYPE(int64_t const, (int64_t) 1));
    TEST_ASSERT_EQUAL_FLOAT(1, IC_REQUIRE_TYPE(float, (float) 1));
    TEST_ASSERT_EQUAL_DOUBLE(1, IC_REQUIRE_TYPE(double, (double) 1));
    TEST_ASSERT_EQUAL_DOUBLE(1, IC_REQUIRE_TYPE(long double, (long double) 1));

    TEST_ASSERT_EQUAL_TYPE(uint8_t, IC_REQUIRE_TYPE(uint8_t, (uint8_t) 1));
    TEST_ASSERT_EQUAL_TYPE(uint16_t, IC_REQUIRE_TYPE(uint16_t, (uint16_t const) 1));
    TEST_ASSERT_EQUAL_TYPE(uint32_t, IC_REQUIRE_TYPE(uint32_t const, (uint32_t const) 1));
    TEST_ASSERT_EQUAL_TYPE(uint64_t, IC_REQUIRE_TYPE(uint64_t, (uint64_t) 1));
    TEST_ASSERT_EQUAL_TYPE(int8_t, IC_REQUIRE_TYPE(int8_t, (int8_t const) 1));
    TEST_ASSERT_EQUAL_TYPE(int16_t, IC_REQUIRE_TYPE(int16_t, (int16_t) 1));
    TEST_ASSERT_EQUAL_TYPE(int32_t, IC_REQUIRE_TYPE(int32_t const, (int32_t) 1));
    TEST_ASSERT_EQUAL_TYPE(int64_t, IC_REQUIRE_TYPE(int64_t const, (int64_t) 1));
    TEST_ASSERT_EQUAL_TYPE(float, IC_REQUIRE_TYPE(float, (float) 1));
    TEST_ASSERT_EQUAL_TYPE(double, IC_REQUIRE_TYPE(double, (double) 1));
    TEST_ASSERT_EQUAL_TYPE(long double, IC_REQUIRE_TYPE(long double, (long double) 1));
}

void test_IC_IS_UINT(void) {
    IC_ASSERT_CONSTANT(IC_IS_UINT((uint8_t) 1));

    TEST_ASSERT_TRUE(IC_IS_UINT((uint8_t) 1));
    TEST_ASSERT_TRUE(IC_IS_UINT((uint16_t) 1));
    TEST_ASSERT_TRUE(IC_IS_UINT((uint32_t) 1));
    TEST_ASSERT_TRUE(IC_IS_UINT((uint64_t) 1));
    TEST_ASSERT_TRUE(IC_IS_UINT((unsigned char) 1));
    TEST_ASSERT_TRUE(IC_IS_UINT((unsigned short int) 1));
    TEST_ASSERT_TRUE(IC_IS_UINT((unsigned long int) 1));
    TEST_ASSERT_TRUE(IC_IS_UINT((unsigned long long int) 1));

    TEST_ASSERT_FALSE(IC_IS_UINT((int8_t) 1));
    TEST_ASSERT_FALSE(IC_IS_UINT((int16_t) 1));
    TEST_ASSERT_FALSE(IC_IS_UINT((int32_t) 1));
    TEST_ASSERT_FALSE(IC_IS_UINT((int64_t) 1));
    TEST_ASSERT_FALSE(IC_IS_UINT((signed char) 1));
    TEST_ASSERT_FALSE(IC_IS_UINT((signed short int) 1));
    TEST_ASSERT_FALSE(IC_IS_UINT((signed long int) 1));
    TEST_ASSERT_FALSE(IC_IS_UINT((signed long long int) 1));
    TEST_ASSERT_FALSE(IC_IS_UINT((float) 1));
    TEST_ASSERT_FALSE(IC_IS_UINT((double) 1));
    TEST_ASSERT_FALSE(IC_IS_UINT((long double) 1));
}

void test_IC_REQUIRE_UINT(void) {
    IC_ASSERT_CONSTANT(IC_REQUIRE_UINT((uint8_t) 1));

    TEST_ASSERT_EQUAL(1, IC_REQUIRE_UINT((uint8_t) 1));
    TEST_ASSERT_EQUAL(2, IC_REQUIRE_UINT((uint16_t) 2));
    TEST_ASSERT_EQUAL(3, IC_REQUIRE_UINT((uint32_t) 3));
    TEST_ASSERT_EQUAL(4, IC_REQUIRE_UINT((uint64_t) 4));

    TEST_ASSERT_EQUAL_TYPE(uint8_t, IC_REQUIRE_UINT((uint8_t) 1));
    TEST_ASSERT_EQUAL_TYPE(uint16_t, IC_REQUIRE_UINT((uint16_t) 2));
    TEST_ASSERT_EQUAL_TYPE(uint32_t, IC_REQUIRE_UINT((uint32_t) 3));
    TEST_ASSERT_EQUAL_TYPE(uint64_t, IC_REQUIRE_UINT((uint64_t) 4));
}

void test_IC_Z_REQUIRE_UINT(void) {
    TEST_ASSERT_EQUAL(1, IC_Z_REQUIRE_UINT((uint8_t) 1));
    TEST_ASSERT_EQUAL(2, IC_Z_REQUIRE_UINT((uint16_t) 2));
    TEST_ASSERT_EQUAL(3, IC_Z_REQUIRE_UINT((uint32_t) 3));
    TEST_ASSERT_EQUAL(4, IC_Z_REQUIRE_UINT((uint64_t) 4));

    TEST_ASSERT_EQUAL_TYPE(uint8_t, IC_Z_REQUIRE_UINT((uint8_t) 1));
    TEST_ASSERT_EQUAL_TYPE(uint16_t, IC_Z_REQUIRE_UINT((uint16_t) 2));
    TEST_ASSERT_EQUAL_TYPE(uint32_t, IC_Z_REQUIRE_UINT((uint32_t) 3));
    TEST_ASSERT_EQUAL_TYPE(uint64_t, IC_Z_REQUIRE_UINT((uint64_t) 4));
}

void test_IC_REQUIRE_INT(void) {
    IC_ASSERT_CONSTANT(IC_REQUIRE_INT((int8_t) 1));

    TEST_ASSERT_EQUAL(1, IC_REQUIRE_INT((int8_t) 1));
    TEST_ASSERT_EQUAL(2, IC_REQUIRE_INT((int16_t) 2));
    TEST_ASSERT_EQUAL(3, IC_REQUIRE_INT((int32_t) 3));
    TEST_ASSERT_EQUAL(4, IC_REQUIRE_INT((int64_t) 4));
    TEST_ASSERT_TRUE(IC_IS_INT((signed char) 1));
    TEST_ASSERT_TRUE(IC_IS_INT((signed short int) 1));
    TEST_ASSERT_TRUE(IC_IS_INT((signed long int) 1));
    TEST_ASSERT_TRUE(IC_IS_INT((signed long long int) 1));

    TEST_ASSERT_EQUAL_TYPE(int8_t, IC_REQUIRE_INT((int8_t) 1));
    TEST_ASSERT_EQUAL_TYPE(int16_t, IC_REQUIRE_INT((int16_t) 2));
    TEST_ASSERT_EQUAL_TYPE(int32_t, IC_REQUIRE_INT((int32_t) 3));
    TEST_ASSERT_EQUAL_TYPE(int64_t, IC_REQUIRE_INT((int64_t) 4));
    TEST_ASSERT_FALSE(IC_IS_INT((unsigned char) 1));
    TEST_ASSERT_FALSE(IC_IS_INT((unsigned short int) 1));
    TEST_ASSERT_FALSE(IC_IS_INT((unsigned long int) 1));
    TEST_ASSERT_FALSE(IC_IS_INT((unsigned long long int) 1));
    TEST_ASSERT_FALSE(IC_IS_INT((float) 1));
    TEST_ASSERT_FALSE(IC_IS_INT((double) 1));
    TEST_ASSERT_FALSE(IC_IS_INT((long double) 1));
}

void test_IC_IS_FP(void) {
    IC_ASSERT_CONSTANT(IC_IS_FP(1.0));

    TEST_ASSERT_TRUE(IC_IS_FP(1.0));
    TEST_ASSERT_TRUE(IC_IS_FP(1.f));
    TEST_ASSERT_TRUE(IC_IS_FP(1.l));

    TEST_ASSERT_FALSE(IC_IS_FP((uint8_t) 1));
    TEST_ASSERT_FALSE(IC_IS_FP((uint16_t) 1));
    TEST_ASSERT_FALSE(IC_IS_FP((uint32_t) 1));
    TEST_ASSERT_FALSE(IC_IS_FP((uint64_t) 1));
    TEST_ASSERT_FALSE(IC_IS_FP((unsigned char) 1));
    TEST_ASSERT_FALSE(IC_IS_FP((unsigned short int) 1));
    TEST_ASSERT_FALSE(IC_IS_FP((unsigned long int) 1));
    TEST_ASSERT_FALSE(IC_IS_FP((unsigned long long int) 1));
    TEST_ASSERT_FALSE(IC_IS_FP((int8_t) 1));
    TEST_ASSERT_FALSE(IC_IS_FP((int16_t) 1));
    TEST_ASSERT_FALSE(IC_IS_FP((int32_t) 1));
    TEST_ASSERT_FALSE(IC_IS_FP((int64_t) 1));
    TEST_ASSERT_FALSE(IC_IS_FP((signed char) 1));
    TEST_ASSERT_FALSE(IC_IS_FP((signed short int) 1));
    TEST_ASSERT_FALSE(IC_IS_FP((signed long int) 1));
    TEST_ASSERT_FALSE(IC_IS_FP((signed long long int) 1));
}

void test_IC_REQUIRE_FP(void) {
    IC_ASSERT_CONSTANT(IC_REQUIRE_FP(1.0));

    TEST_ASSERT_EQUAL_DOUBLE(1.0, IC_REQUIRE_FP(1.0));
    TEST_ASSERT_EQUAL_FLOAT(1.f, IC_REQUIRE_FP(1.f));
    TEST_ASSERT_EQUAL_DOUBLE(1.l, IC_REQUIRE_FP(1.l));

    TEST_ASSERT_EQUAL_TYPE(double, IC_REQUIRE_FP(1.0));
    TEST_ASSERT_EQUAL_TYPE(float, IC_REQUIRE_FP(1.f));
    TEST_ASSERT_EQUAL_TYPE(long double, IC_REQUIRE_FP(1.l));
}


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_IC_ASSERT_TYPE);
    RUN_TEST(test_IC_REQUIRE_TYPE);
    RUN_TEST(test_IC_IS_UINT);
    RUN_TEST(test_IC_REQUIRE_UINT);
    RUN_TEST(test_IC_Z_REQUIRE_UINT);
    RUN_TEST(test_IC_REQUIRE_INT);
    RUN_TEST(test_IC_IS_FP);
    RUN_TEST(test_IC_REQUIRE_FP);

    return UNITY_END();
}