function(re2c_bootstrap_lexer input output)
    # optional header file, 3rd argument
    set(header "${ARGN}")

    # source files (use relative path to avoid hardcoding in line directives)
    set(source "${CMAKE_CURRENT_SOURCE_DIR}/${input}")
    file(RELATIVE_PATH relative_source "${CMAKE_CURRENT_BINARY_DIR}" "${source}")

    # bootstrap files
    set(boot_output "${CMAKE_CURRENT_SOURCE_DIR}/bootstrap/${output}")
    set(boot_header "${CMAKE_CURRENT_SOURCE_DIR}/bootstrap/${header}")

    set(re2c_flags "-b" "-W" "-Wno-match-empty-string" "--no-generation-date")

    if (RE2C_REBUILD_LEXERS)
        # recompile the lexer and update bootstrap file(s)
        if("${header}" STREQUAL "")
            # without header
            get_filename_component(outdir "${output}" DIRECTORY)
            add_custom_command(
                OUTPUT "${output}"
                COMMAND "${CMAKE_COMMAND}" -E make_directory ${outdir}
                COMMAND "${RE2C_FOR_BUILD}" ${re2c_flags} "${relative_source}" -o "${output}"
                COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${output}" "${boot_output}"
                DEPENDS "${source}"
                COMMENT "Generating ${output}"
            )
        else()
            # with header
            get_filename_component(outdir "${output}" DIRECTORY)
            get_filename_component(hdrdir "${header}" DIRECTORY)
            add_custom_command(
                OUTPUT "${output}" "${header}"
                COMMAND "${CMAKE_COMMAND}" -E make_directory ${outdir}
                COMMAND "${CMAKE_COMMAND}" -E make_directory ${hdrdir}
                COMMAND "${RE2C_FOR_BUILD}" ${re2c_flags} "${relative_source}" -o "${output}"
                COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${output}" "${boot_output}"
                COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${header}" "${boot_header}"
                DEPENDS "${source}"
                COMMENT "Generating ${output} and ${header}"
            )
        endif()
    else()
        # copy precompiled bootstrap file(s)
        if("${header}" STREQUAL "")
            # without header
            add_custom_command(
                OUTPUT "${output}"
                COMMAND "${CMAKE_COMMAND}" -E copy "${boot_output}" "${output}"
                DEPENDS "${source}" "${boot_output}"
                COMMENT "Copying bootstrap ${output}, reconfigure with RE2C_REBUILD_LEXERS to regenerate"
            )
        else()
            # with header
            add_custom_command(
                OUTPUT "${output}" "${header}"
                COMMAND "${CMAKE_COMMAND}" -E copy "${boot_output}" "${output}"
                COMMAND "${CMAKE_COMMAND}" -E copy "${boot_header}" "${header}"
                DEPENDS "${source}" "${boot_output}" "${boot_header}"
                COMMENT "Copying bootstrap ${output} and ${header}, reconfigure with RE2C_REBUILD_LEXERS to regenerate"
            )
        endif()
    endif()
endfunction()
