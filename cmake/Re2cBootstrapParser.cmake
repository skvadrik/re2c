function(re2c_bootstrap_parser ypp_file cc_file h_file)
    get_filename_component(parent_dir "${cc_file}" DIRECTORY)
    file(RELATIVE_PATH relative_parser
        "${CMAKE_CURRENT_BINARY_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/${ypp_file}")

    set(bootstrap_parser "${CMAKE_CURRENT_SOURCE_DIR}/bootstrap/${cc_file}")
    set(bootstrap_header "${CMAKE_CURRENT_SOURCE_DIR}/bootstrap/${h_file}")
    if (RE2C_REBUILD_PARSERS)
        add_custom_command(
            OUTPUT ${cc_file} ${h_file}
            COMMAND "${CMAKE_COMMAND}" -E make_directory "${parent_dir}"
            COMMAND "${BISON_EXECUTABLE}" --warnings --output="${cc_file}" --defines="${h_file}" "${relative_parser}"
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${cc_file}" "${bootstrap_parser}"
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${h_file}" "${bootstrap_header}"
            DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${ypp_file}"
        )
    else()
        add_custom_command(
            OUTPUT ${cc_file} ${h_file}
            COMMAND "${CMAKE_COMMAND}" -E make_directory "${parent_dir}"
            COMMAND "${CMAKE_COMMAND}" -E copy "${bootstrap_parser}" "${parent_dir}"
            COMMAND "${CMAKE_COMMAND}" -E copy "${bootstrap_header}" "${parent_dir}"
            DEPENDS "${bootstrap_parser}" "${bootstrap_header}"
            COMMENT "Copying bootstrap parser, reconfigure with RE2C_REBUILD_PARSERS to regenerate"
        )
    endif()
endfunction()
