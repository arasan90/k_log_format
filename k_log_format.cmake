cmake_minimum_required(VERSION 3.10)

set(sources
    ${CMAKE_CURRENT_LIST_DIR}/src/k_log_format.c
    )

set(public_includes
    ${CMAKE_CURRENT_LIST_DIR}/include
    )

set(private_includes
    ${CMAKE_CURRENT_LIST_DIR}/src
    )

set(public_linked_libs
    )

set(private_linked_libs
    )

function(k_log_format_get_sources OUT_VAR)
    set(${OUT_VAR}
        ${sources}
        PARENT_SCOPE)
endfunction()

function(k_log_format_get_public_headers OUT_VAR)
    set(${OUT_VAR}
        ${public_includes}
        PARENT_SCOPE)
endfunction()

function(k_log_format_get_private_headers OUT_VAR)
    set(${OUT_VAR}
        ${private_includes}
        PARENT_SCOPE)
endfunction()

function(k_log_format_get_private_linked_libs OUT_VAR)
    set(${OUT_VAR}
        ${private_linked_libs}
        PARENT_SCOPE)
endfunction()

function(k_log_format_get_public_linked_libs OUT_VAR)
    set(${OUT_VAR}
        ${public_linked_libs}
        PARENT_SCOPE)
endfunction()

function (k_log_format_create_mock_library)
    add_library(k_log_format_mock ${CMAKE_CURRENT_LIST_DIR}/mock/k_log_format_mock.c)
    target_include_directories(k_log_format_mock PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
    target_include_directories(k_log_format_mock PRIVATE ${CMAKE_CURRENT_LIST_DIR}/mock)
endfunction()