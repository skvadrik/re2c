function(re2c_gen_manpage source target bootstrap lang)
    if(RE2C_REBUILD_DOCS)
        set(source_l "${source}.${lang}")
        add_custom_command(
            OUTPUT "${target}"
            COMMAND "${re2c_splitman}" "${source}" "${source_l}" "${lang}"
            COMMAND "${RST2MAN}" --tab-width=4 "${source_l}" "${target}"
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${target}" "${bootstrap}"
            DEPENDS
                "${source}"
                "${re2c_splitman}"
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
        add_custom_command(
            OUTPUT "${target}"
            COMMAND "${RST2MAN}" "${source}" "${target}.1"
            COMMAND "${re2c_genhelp}" "${target}.1" "${target}"
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${target}" "${bootstrap}"
            DEPENDS
                "${source}"
                "${re2c_genhelp}"
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
