function(re2c_gen_docs source target tool args)
    file(RELATIVE_PATH relative_target "${CMAKE_CURRENT_BINARY_DIR}" "${target}")
    set(bootstrap "${CMAKE_CURRENT_SOURCE_DIR}/bootstrap/${relative_target}")
    if(RE2C_REBUILD_DOCS)
        get_filename_component(targetdir "${target}" DIRECTORY)
        set(split_source "${target}.rst")
        add_custom_command(
            OUTPUT "${target}"
            COMMAND "${CMAKE_COMMAND}" -E make_directory ${targetdir}
            COMMAND "${PYTHON}" "${re2c_splitman}" "${source}" "${split_source}"
            COMMAND "${PYTHON}" "${tool}" ${args} "${split_source}" "${target}"
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${target}" "${bootstrap}"
            DEPENDS
                "${source}"
                "${tool}"
                "${re2c_splitman}"
                "${re2c_docs_sources}"
            BYPRODUCTS "${split_source}"
        )
    else()
        add_custom_command(
            OUTPUT "${target}"
            COMMAND "${CMAKE_COMMAND}" -E copy "${bootstrap}" "${target}"
            DEPENDS "${bootstrap}"
        )
    endif()
endfunction()

function(re2c_gen_manpage source target)
    re2c_gen_docs("${source}" "${target}" "${re2c_rst2man}" "--tab-width=4")
endfunction()

function(re2c_gen_help source target)
    re2c_gen_docs("${source}" "${target}" "${re2c_rst2txt}" "--variable-name=help")
endfunction()
