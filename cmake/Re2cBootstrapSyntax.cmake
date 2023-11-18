function(re2c_bootstrap_syntax source target)
    set(bootstrap "${CMAKE_CURRENT_SOURCE_DIR}/bootstrap/${target}")
    if(RE2C_REBUILD_SYNTAX)
        get_filename_component(targetdir "${target}" DIRECTORY)
        add_custom_command(
            OUTPUT "${target}"
            COMMAND "${CMAKE_COMMAND}" -E make_directory ${targetdir}
            COMMAND "${PYTHON}" "${re2c_stx2cpp}" "${CMAKE_CURRENT_SOURCE_DIR}/${source}" "${target}"
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${target}" "${bootstrap}"
            DEPENDS "${source}" "${re2c_stx2cpp}"
        )
    else()
        add_custom_command(
            OUTPUT "${target}"
            COMMAND "${CMAKE_COMMAND}" -E copy "${bootstrap}" "${target}"
            DEPENDS "${bootstrap}"
            COMMENT "Copying bootstrap syntax file, reconfigure with RE2C_REBUILD_PARSERS to regenerate"
        )
    endif()
endfunction()
