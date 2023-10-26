file(GLOB_RECURSE files_to_format 
    ${CMAKE_CURRENT_LIST_DIR}/include/*.h
    ${CMAKE_CURRENT_LIST_DIR}/include/zephyr/*.h
    ${CMAKE_CURRENT_LIST_DIR}/include/ic_macros/*.h
    ${CMAKE_CURRENT_LIST_DIR}/tests/*.c
    ${CMAKE_CURRENT_LIST_DIR}/tests/*.h
    ${CMAKE_CURRENT_LIST_DIR}/src/*.c
)

if("${CMAKE_ARGV3}" STREQUAL "format")
    message("Running clang-format-18 in-place")
    foreach(file ${files_to_format})
        execute_process(
            COMMAND clang-format-18 "-i" "${file}"
            RESULT_VARIABLE res 
        )
        if(NOT ${res} STREQUAL "0")
            message(FATAL_ERROR "clang-format-18 error")
        endif()
    endforeach()
endif()

foreach(file ${files_to_format})
    execute_process(
        COMMAND clang-format-18 "--dry-run" "--Werror" "${file}"
        RESULT_VARIABLE res 
    )
    if(NOT ${res} STREQUAL "0")
        message(FATAL_ERROR "clang-format-18 error")
    endif()
endforeach()
message("clang-format-18 passed")
