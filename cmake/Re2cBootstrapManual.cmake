function(re2c_bootstrap_manual rst_file man_file)
    if (NOT IS_ABSOLUTE "${rst_file}")
        set(rst_file "${CMAKE_CURRENT_SOURCE_DIR}/${rst_file}")
    endif()

    get_filename_component(parent_dir "${man_file}" DIRECTORY)
    if(RE2C_REBUILD_DOCS)
        add_custom_command(
            OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${man_file}"
            COMMAND "${CMAKE_COMMAND}" -E make_directory "${parent_dir}"
            COMMAND "${RST2MAN}" "${rst_file}" > "${man_file}"
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${man_file}" "${CMAKE_CURRENT_SOURCE_DIR}/bootstrap/${man_file}"
            MAIN_DEPENDENCY "${rst_file}"
        )
    else()
        add_custom_command(
            OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${man_file}"
            COMMAND "${CMAKE_COMMAND}" -E make_directory "${parent_dir}"
            COMMAND "${CMAKE_COMMAND}" -E copy "${CMAKE_CURRENT_SOURCE_DIR}/bootstrap/${man_file}" "${man_file}"
            MAIN_DEPENDENCY "${CMAKE_CURRENT_SOURCE_DIR}/bootstrap/${man_file}"
        )
    endif()
endfunction()
