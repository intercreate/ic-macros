# Copyright (c) 2023 Intercreate, Inc.
# SPDX-License-Identifier: Apache-2.0
#
# Authors: J.P. Hutchins <jp@intercreate.io>

include_guard(GLOBAL)

include(FetchContent)

FetchContent_Declare(ic_macros
    URL https://github.com/intercreate/ic-macros/releases/latest/download/ic_macros.zip
    DOWNLOAD_EXTRACT_TIMESTAMP true
)
FetchContent_MakeAvailable(ic_macros)
