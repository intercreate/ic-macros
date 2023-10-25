# SPDX-License-Identifier: Apache-2.0
#
# Copyright (c) 2023 Intercreate, Inc.
# Author: J.P. Hutchins <jp@intercreate.io>

cmake_minimum_required(VERSION 3.20)

project(ic_macros LANGUAGES C CXX)

# add the headers to the library
add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE include)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    # We're in the root, define additional targets for developers.
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

    target_compile_options(${PROJECT_NAME}
        INTERFACE
        # -Wall
        # -Wextra
        # -Wshadow
        # -Wconversion
        # -Wdouble-promotion
        # -Wformat=2
        # -Wformat-truncation
        # -Wundef
        # -fno-common
        # -Wtype-limits
    )

    add_subdirectory(tests)

    # generate a package for distribution
    # reference: https://www.foonathan.net/2022/06/cmake-fetchcontent/
    set(package_files include/ CMakeLists.txt LICENSE fetch_ic_macros.cmake)
    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.zip
        COMMAND ${CMAKE_COMMAND} -E tar 
            c ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.zip 
            --format=zip 
            -- ${package_files}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DEPENDS ${package_files}
    )
    add_custom_target(package
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.zip
    )
endif()
