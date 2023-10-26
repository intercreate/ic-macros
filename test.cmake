# Copyright (c) 2023, Intercreate, Inc.
# SPDX-License-Identifier: Apache-2.0
#
# Automate CMake configure, build, and test.
#
# usage:
#   cmake -P test.cmake [toolchain]
#
# See the toolchain folder for options.  Specify without the extension, .cmake.
#
# example:
#   cmake -P test.cmake arm-none-eabi-gcc

if(${CMAKE_ARGC} EQUAL 3)
    set(toolchain_arg)
    set(build_folder build-native)
elseif(${CMAKE_ARGC} EQUAL 4)
    set(toolchain_arg "-DCMAKE_TOOLCHAIN_FILE=toolchain/${CMAKE_ARGV3}.cmake")
    set(build_folder "build-${CMAKE_ARGV3}")
else()
    message(FATAL_ERROR "Must provide 0 or 1 arguments!")
endif()

execute_process(
    COMMAND cmake "-B${build_folder}" "-GNinja" "${toolchain_arg}"
    RESULT_VARIABLE res 
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
)
if(NOT ${res} STREQUAL "0")
    message(FATAL_ERROR "CMake configuration step failed.")
endif()

execute_process(
    COMMAND cmake "--build" "${build_folder}" "--clean-first"
    RESULT_VARIABLE res
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
)
if(NOT ${res} STREQUAL "0")
    message(FATAL_ERROR "CMake build step failed.")
endif()

execute_process(COMMAND ctest "-V" "--test-dir" "${build_folder}/tests" "--output-on-failure"
    RESULT_VARIABLE res
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
)
if(NOT ${res} STREQUAL "0")
    message(FATAL_ERROR "1 or more tests failed.")
endif()
