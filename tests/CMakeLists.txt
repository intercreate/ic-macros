# Copyright (c) 2023 Intercreate, Inc.
# SPDX-License-Identifier: Apache-2.0
#
# Author: J.P. Hutchins <jp@intercreate.io>

enable_testing()

include(FetchContent)

FetchContent_Declare(
    unity
    GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
    GIT_TAG 1b9199ee380e203603b6649df9510db9cab147d9
)
add_compile_definitions(
    UNITY_INCLUDE_DOUBLE=1
    UNITY_DOUBLE_PRECISION=1e-12f
)
FetchContent_MakeAvailable(unity)

FetchContent_Declare(
    fff
    GIT_REPOSITORY https://github.com/meekrosoft/fff.git
    GIT_TAG 5111c61e1ef7848e3afd3550044a8cf4405f4199
)
FetchContent_MakeAvailable(fff)

# Collect the test folders
file(GLOB tests RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "test_*")
message(STATUS "Collected tests [ ${tests} ]")

# Build each test and add it to CTest
foreach(test ${tests})
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${test})
        file(GLOB_RECURSE src_files ${CMAKE_CURRENT_SOURCE_DIR}/${test}/*.c)
        message(STATUS "${test} src_files [ ${src_files} ]")
    elseif(${test} MATCHES "test_.*\.c")
        set(src_files ${test})
    else()
        continue()
    endif()
    project(${test})
    add_executable(${test} ${src_files})
    target_link_libraries(${test} ic_macros unity fff)
    add_test(${test} ${test})
endforeach()
