function(re2c_bootstrap_parser ypp_file cc_file h_file)
    get_filename_component(parent_dir "${cc_file}" DIRECTORY)
    file(RELATIVE_PATH relative_ypp_file "${CMAKE_CURRENT_BINARY_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/${ypp_file}")

    if (BISON_EXECUTABLE)
        add_custom_command(
            OUTPUT ${cc_file} ${h_file}
            COMMAND "${CMAKE_COMMAND}" -E make_directory "${parent_dir}"
            COMMAND "${BISON_EXECUTABLE}" --defines="${h_file}" -o "${cc_file}" "${relative_ypp_file}"
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${cc_file}" "${CMAKE_CURRENT_SOURCE_DIR}/bootstrap/${cc_file}"
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${h_file}" "${CMAKE_CURRENT_SOURCE_DIR}/bootstrap/${h_file}"
            DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${ypp_file}"
        )
    else()
        add_custom_command(
            OUTPUT ${cc_file} ${h_file}
            COMMAND "${CMAKE_COMMAND}" -E make_directory "${parent_dir}"
            COMMAND "${CMAKE_COMMAND}" -E copy "${CMAKE_CURRENT_SOURCE_DIR}/bootstrap/${cc_file}" "${parent_dir}"
            COMMAND "${CMAKE_COMMAND}" -E copy "${CMAKE_CURRENT_SOURCE_DIR}/bootstrap/${h_file}" "${parent_dir}"
            DEPENDS
                "${CMAKE_CURRENT_SOURCE_DIR}/bootstrap/${cc_file}"
                "${CMAKE_CURRENT_SOURCE_DIR}/bootstrap/${h_file}"
        )
    endif()
endfunction()
