include(CheckCXXCompilerFlag)

# Iff C++ compiler recognizes 'flag', append 'flag' and 'implied-flags' to CXXFLAGSDEFAULT
# (Second param 'implied-flags' is needed for warning suppressions '-Wno-<warning>':
# GCC warns about unrecognized suppressions options only in presence of other warnings,
# which makes it hard to test for them with autoconf.)
function(try_cxxflag flag)
    set(varname "cxxflag_${flag}")
    string(REPLACE "=" "_" varname "${varname}")
    check_cxx_compiler_flag("${flag}" ${varname})
    if(${varname})
        set(CMAKE_CXX_FLAGS "${flag} ${CMAKE_CXX_FLAGS}")
        foreach(implied_flag IN LISTS ARGN)
            set(CMAKE_CXX_FLAGS "${implied_flag} ${CMAKE_CXX_FLAGS}")
        endforeach()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" PARENT_SCOPE)
    endif()
endfunction()

# Set default optimization flag if there is no build type provided.
# For more see discussion at https://github.com/skvadrik/re2c/pull/316
if(NOT CMAKE_BUILD_TYPE)
    try_cxxflag("-O2")
endif()

try_cxxflag("-W")
try_cxxflag("-Wall")
try_cxxflag("-Wextra")
try_cxxflag("-Weffc++")
try_cxxflag("-pedantic")
try_cxxflag("-Wformat=2")
try_cxxflag("-Wredundant-decls")
try_cxxflag("-Wsuggest-attribute=format")
try_cxxflag("-Wconversion")
try_cxxflag("-Wsign-conversion")
try_cxxflag("-Werror=return-type")
try_cxxflag("-Weverything"
    "-Wno-unknown-warning-option" # CLANG eats some GCC options only to warn they are unknown
    "-Wno-reserved-id-macro" # to allow header guards of the form '_RE2C_PATH_TO_HEADER_BASENAME_'
    "-Wno-padded"
    "-Wno-old-style-cast" # RE2C-generated lexer has lots of C-style casts because of 're2c:yych:conversion = 1;'
    "-Wno-nested-anon-types"
    "-Wno-global-constructors" # initialization of global constants with std::numeric_limits<...> (mostly for size_t)
    "-Wno-shadow-field-in-constructor" # using same names in ctor seems more like a feature
    "-Wno-undefined-func-template" # explicit specialization to reduce build dependencies
)

try_cxxflag("-fdiagnostics-color=always")

# Verify compiler flags
get_property(_languages GLOBAL PROPERTY ENABLED_LANGUAGES)

foreach(_lang IN LISTS _languages)
    message(STATUS "Common compiler flags for ${_lang}: ${CMAKE_${_lang}_FLAGS}")
    if (CMAKE_BUILD_TYPE)
        string(TOUPPER ${CMAKE_BUILD_TYPE} _config)
        message(STATUS "${CMAKE_BUILD_TYPE} compiler flags for ${_lang}: ${CMAKE_${_lang}_FLAGS_${_config}}")
        unset(_config)
    endif()
endforeach()

unset(_languages)
