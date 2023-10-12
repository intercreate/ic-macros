/*
 * Copyright (c) 2023, Intercreate, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <unity.h>

void setUp(void) {} /* Is run before every test, put unit init calls here. */
void tearDown(void) {} /* Is run after every test, put unit clean-up calls here. */

#include <ic_macros.h>


void test_IC_ASSERT_CONSTANT(void) {
    IC_ASSERT_CONSTANT(1);

#define ONE 1
    IC_ASSERT_CONSTANT(ONE);
#undef ONE

    IC_ASSERT_CONSTANT(1.99 * 5839024 / (3 * 10380));

#define CPP_DOUBLE 1.99 * 5839024 / (3 * 10380)
    IC_ASSERT_CONSTANT(CPP_DOUBLE);
#undef CPP_DOUBLE
}

void test_IC_REQUIRE_CONSTANT(void) {
#define ONE IC_REQUIRE_CONSTANT(1)
    TEST_ASSERT_EQUAL(1, ONE);
#undef ONE

    int zero = IC_REQUIRE_CONSTANT(0);
    TEST_ASSERT_EQUAL(0, zero);

#define FORTY2 IC_REQUIRE_CONSTANT(0.42)
    TEST_ASSERT_EQUAL_DOUBLE(0.42, FORTY2);
#undef FORTY2

#define CPP_DOUBLE IC_REQUIRE_CONSTANT(1.99 * 5839024 / (3 * 10380))
    TEST_ASSERT_EQUAL_DOUBLE(1.99 * 5839024 / (3 * 10380), CPP_DOUBLE);
    TEST_ASSERT_EQUAL_DOUBLE(373.142509955, CPP_DOUBLE);
#undef CPP_DOUBLE

    double cpp_double = IC_REQUIRE_CONSTANT(1.99 * 5839024 / (3.0 * 10380));
    TEST_ASSERT_EQUAL_DOUBLE(1.99 * 5839024 / (3 * 10380), cpp_double);
    TEST_ASSERT_EQUAL_DOUBLE(373.142509955, cpp_double);

#define PLUS(x, y, z) IC_REQUIRE_CONSTANT(x + y + z)
    TEST_ASSERT_EQUAL(42, PLUS(19, 15, 8));
#undef PLUS

#define PLUS(x, y, z) (x + y + z)
    TEST_ASSERT_EQUAL(42, IC_REQUIRE_CONSTANT(PLUS(19, 15, 8)));
#undef PLUS

#define LOTSA_MATH(a, b, c, d, e) IC_REQUIRE_CONSTANT(a * b + c / d / e)
    TEST_ASSERT_EQUAL_DOUBLE(
        1.2 * 3.4 + 43.6 / 18343.8 / 0.0023478924, LOTSA_MATH(1.2, 3.4, 43.6, 18343.8, 0.0023478924)
    );
}

void test_assert_constant_fails(void) {
    /* mock IC_BUILD_ASSERT */
    int ret = -1;
#undef IC_BUILD_ASSERT
#define IC_BUILD_ASSERT(expr, ...) ret = expr

    /* test the mock */
    IC_ASSERT_CONSTANT(1.99 * 5839024 / (3.0 * 10380));
    TEST_ASSERT(ret == 1);
    ret = -1;

    /* test the fails */

    int const one = 1;
    IC_ASSERT_CONSTANT(one);
    TEST_ASSERT(ret == 0);
    ret = -1;

    IC_ASSERT_CONSTANT(one + 1);
    TEST_ASSERT(ret == 0);
    ret = -1;

    IC_REQUIRE_CONSTANT(one);
    TEST_ASSERT(ret == 0);
    ret = -1;

    IC_REQUIRE_CONSTANT(one + 1);
    TEST_ASSERT(ret == 0);
    ret = -1;
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_IC_ASSERT_CONSTANT);
    RUN_TEST(test_IC_REQUIRE_CONSTANT);
    RUN_TEST(test_assert_constant_fails);

    return UNITY_END();
}