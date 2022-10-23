function(re2c_gen_manpage source target bootstrap lang)
    if(RE2C_REBUILD_DOCS)
        get_filename_component(targetdir "${target}" DIRECTORY)
        set(source_l "${source}.${lang}")
        add_custom_command(
            OUTPUT "${target}"
            COMMAND "${CMAKE_COMMAND}" -E make_directory ${targetdir}
            COMMAND "${PYTHON}" "${re2c_splitman}" "${source}" "${source_l}" "${lang}"
            COMMAND "${PYTHON}" "${re2c_rst2man}" --tab-width=4 "${source_l}" "${target}"
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${target}" "${bootstrap}"
            DEPENDS
                "${source}"
                "${re2c_splitman}"
                "${re2c_rst2man}"
                "${re2c_docs_sources}"
            BYPRODUCTS "${source_l}"
        )
    else()
        add_custom_command(
            OUTPUT "${target}"
            COMMAND "${CMAKE_COMMAND}" -E copy "${bootstrap}" "${target}"
            DEPENDS "${bootstrap}"
        )
    endif()
endfunction()

function(re2c_gen_help source target bootstrap)
    if(RE2C_REBUILD_DOCS)
        get_filename_component(targetdir "${target}" DIRECTORY)
        add_custom_command(
            OUTPUT "${target}"
            COMMAND "${CMAKE_COMMAND}" -E make_directory ${targetdir}
            COMMAND "${PYTHON}" "${re2c_rst2txt}" --variable-name=help "${source}" "${target}"
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${target}" "${bootstrap}"
            DEPENDS
                "${source}"
                "${re2c_rst2txt}"
                "${re2c_docs_sources}"
            BYPRODUCTS "${target}.1"
        )
    else()
        add_custom_command(
            OUTPUT "${target}"
            COMMAND "${CMAKE_COMMAND}" -E copy "${bootstrap}" "${target}"
            DEPENDS "${bootstrap}"
        )
    endif()
endfunction()
