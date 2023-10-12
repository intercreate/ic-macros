/*
 * Copyright (c) 2023, Intercreate, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <unity.h>

#define TEST_ASSERT_EQUAL_TYPE(t, expr) \
    TEST_ASSERT(__builtin_types_compatible_p(t, __typeof__(expr)))
