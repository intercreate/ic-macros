# Copyright (c) 2023 Intercreate, Inc.
# SPDX-License-Identifier: Apache-2.0
#
# Authors: J.P. Hutchins <jp@intercreate.io>

include_guard(GLOBAL)

if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.24.0")
    set(download_extract_timestamp "DOWNLOAD_EXTRACT_TIMESTAMP true")
endif()

include(FetchContent)

FetchContent_Declare(ic_macros
    URL https://github.com/intercreate/ic-macros/releases/latest/download/ic_macros.zip
    ${download_extract_timestamp}
)
FetchContent_MakeAvailable(ic_macros)
