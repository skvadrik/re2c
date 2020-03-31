function(re2c_bootstrap_compiled_help rst_file cc_file)
    if (NOT IS_ABSOLUTE "${rst_file}")
        set(rst_file "${CMAKE_CURRENT_SOURCE_DIR}/${rst_file}")
    endif()

    get_filename_component(parent_dir "${cc_file}" DIRECTORY)
    if(RE2C_REBUILD_DOCS)
        add_custom_command(
            OUTPUT "${cc_file}"
            COMMAND "${CMAKE_COMMAND}" -E make_directory "${parent_dir}"
            COMMAND "${RST2MAN}" "${rst_file}" > "${cc_file}.1"
            COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/genhelp.sh" "${cc_file}.1" "${cc_file}"
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${cc_file}" "${CMAKE_CURRENT_SOURCE_DIR}/bootstrap/${cc_file}"
            MAIN_DEPENDENCY "${rst_file}"
            DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/genhelp.sh"
        )
    else()
        add_custom_command(
            OUTPUT "${cc_file}"
            COMMAND "${CMAKE_COMMAND}" -E make_directory "${parent_dir}"
            COMMAND "${CMAKE_COMMAND}" -E copy "${CMAKE_CURRENT_SOURCE_DIR}/bootstrap/${cc_file}" "${cc_file}"
            MAIN_DEPENDENCY "${CMAKE_CURRENT_SOURCE_DIR}/bootstrap/${cc_file}"
        )
    endif()
endfunction()
