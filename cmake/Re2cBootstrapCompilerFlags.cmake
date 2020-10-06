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
if(CMAKE_BUILD_TYPE IN_LIST ALLOWABLE_BUILD_TYPES)
    string(TOUPPER ${CMAKE_BUILD_TYPE} _build_type)
    message(STATUS "Used compiler flags: ${CMAKE_CXX_FLAGS_${_build_type}}")
    unset(_build_type)
endif()
