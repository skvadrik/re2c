if (CMAKE_CURRENT_LIST_FILE STREQUAL CMAKE_SCRIPT_MODE_FILE)
    get_filename_component(parent_dir "${cc_file}" DIRECTORY)
    file(RELATIVE_PATH relative_re_file "${CMAKE_CURRENT_BINARY_DIR}" "${source_dir}/${re_file}")

    file(MAKE_DIRECTORY "${parent_dir}")
    if (EXISTS "${re2c}")
        execute_process(
            COMMAND "${re2c}" -br -W "${relative_re_file}" -o "${cc_file}"
            RESULT_VARIABLE ret
        )
        if (NOT ret EQUAL 0)
             message(FATAL_ERROR "Failure running re2c: got exit status ${ret}")
        endif()
        file(COPY "${cc_file}" DESTINATION "${source_dir}/bootstrap/${parent_dir}")
        if (NOT "${h_file}" STREQUAL "")
            file(COPY "${h_file}" DESTINATION "${source_dir}/bootstrap/${parent_dir}")
        endif()
    else()
        file(COPY "${source_dir}/bootstrap/${cc_file}" DESTINATION "${parent_dir}")
        if (NOT "${h_file}" STREQUAL "")
            file(COPY "${source_dir}/bootstrap/${h_file}" DESTINATION "${parent_dir}")
        endif()
    endif()

    return()
endif()

set(__re2c_bootstrap_lexer_cmake "${CMAKE_CURRENT_LIST_FILE}")

function(re2c_bootstrap_lexer re_file cc_file)
    set(h_file "${ARGN}")
    set(outputs)
    list(APPEND outputs "${cc_file}")
    if(h_file)
        list(APPEND outputs "${h_file}")
    endif()
    if(NOT TARGET re2c)
        message(FATAL_ERROR "'re2c' is not a valid target")
    endif()
    add_custom_command(
        OUTPUT ${outputs}
        COMMAND
            "${CMAKE_COMMAND}"
            -Dsource_dir="${CMAKE_CURRENT_SOURCE_DIR}"
            -Dre_file="${re_file}" -Dcc_file="${cc_file}" -Dh_file="${h_file}"
            # Avoid $<TARGET_FILE:re2c>, because that adds a dependency on re2c,
            # which causes CMake to error if we put this into an object library,
            # which we need to have libre2c built from bootstrap too
            -Dre2c="${CMAKE_CURRENT_BINARY_DIR}/re2c${CMAKE_EXECUTABLE_SUFFIX}"
            -P "${__re2c_bootstrap_lexer_cmake}"
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        MAIN_DEPENDENCY "${CMAKE_CURRENT_SOURCE_DIR}/${re_file}"
        DEPENDS "${__re2c_bootstrap_lexer_cmake}"
    )
endfunction()
