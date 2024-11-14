include(CheckCXXCompilerFlag)

# If C++ compiler recognizes 'flag', append 'flag' and 'implied-flags' to
# re2c_cxx_flags. Parameter 'implied-flags' is needed to suppress warnings (GCC
# warns about unrecognized -Wno-* options only in presence of other warnings).
function(try_cxxflag flag)
    set(varname "cxxflag_${flag}")
    string(MAKE_C_IDENTIFIER "${varname}" varname)
    check_cxx_compiler_flag("${flag}" ${varname})
    if(${varname})
        set(re2c_cxx_flags "${re2c_cxx_flags} ${flag}")
        foreach(implied_flag IN LISTS ARGN)
            set(re2c_cxx_flags "${re2c_cxx_flags} ${implied_flag}")
        endforeach()
        set(re2c_cxx_flags "${re2c_cxx_flags}" PARENT_SCOPE)
    endif()
endfunction()

get_property(isMultiConfig GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
set(re2c_cxx_flags "")

# Set default optimization flag if there is no build type provided.
# CMAKE_BUILD_TYPE is not used by multi-configuration generators.
if(NOT CMAKE_BUILD_TYPE AND NOT isMultiConfig)
    try_cxxflag("-O2")
endif()

if (NOT CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
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
        # CLANG eats some GCC options only to warn they are unknown
        "-Wno-unknown-warning-option"
        # to allow header guards of the form '_RE2C_PATH_TO_HEADER_BASENAME_'
        "-Wno-reserved-id-macro"
        "-Wno-padded"
        "-Wno-nested-anon-types"
        # user-defined literals like `_u8` must start with underscore
        "-Wno-reserved-identifier"
        # using same names in ctor seems more like a feature
        "-Wno-shadow-field-in-constructor"
        # explicit specialization to reduce build dependencies
        "-Wno-undefined-func-template"
        # re2c uses C++11, not C++98
        "-Wno-c++98-compat"
        "-Wno-c++98-compat-pedantic"
        "-Wno-unsafe-pointer-arithmetic"
        "-Wno-unsafe-buffer-usage"
        # re2c is single-threaded => no danger of race conditions
        "-Wno-exit-time-destructors"
        "-Wno-switch-enum"
    )
    try_cxxflag("-fdiagnostics-color=always")

    # Prepend to avoid overriding user-defined options set with -DCMAKE_CXX_FLAGS.
    set(CMAKE_CXX_FLAGS "${re2c_cxx_flags} ${CMAKE_CXX_FLAGS}")
else()
    # /W3 enables levels 1 - 3 (severe, significant and production quality warnings).
    # /W4 (informational warnings) and /Wall (/W4 plus off-by-default warnings) emit too much noise.
    try_cxxflag("/W3"
        "/wd4068" # disable C4068 warning about unused pragmas (we use some for GCC and Clang)
        "-D_CRT_SECURE_NO_WARNINGS" # disable C4996 that complains about functions like `fopen`.
    )
    # Standard C++ stack unwinding (s), assume extern "C" functions never throw (c).
    try_cxxflag("/EHsc")

    # Append, possibly overriding user-defined options. This is necessary to
    # override default CMAKE_CXX_FLAGS options added by CMake in MSVC builds.
    # There is no (easy) way to distinguish them from user-defined options.
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${re2c_cxx_flags}")
endif()

unset(re2c_cxx_flags)

# Print compiler and linker flags
message(STATUS "C compiler flags: ${CMAKE_C_FLAGS}")
message(STATUS "C++ compiler flags: ${CMAKE_CXX_FLAGS}")
message(STATUS "Linker flags for executables: ${CMAKE_EXE_LINKER_FLAGS}")
message(STATUS "Linker flags for shared libs: ${CMAKE_SHARED_LINKER_FLAGS}")
if (CMAKE_BUILD_TYPE)
    string(TOUPPER ${CMAKE_BUILD_TYPE} _type)
    message(STATUS "${CMAKE_BUILD_TYPE} C compiler flags: ${CMAKE_C_FLAGS_${_type}}")
    message(STATUS "${CMAKE_BUILD_TYPE} C++ compiler flags: ${CMAKE_CXX_FLAGS_${_type}}")
    message(STATUS "${CMAKE_BUILD_TYPE} linker flags for executables: ${CMAKE_EXE_LINKER_FLAGS_${_type}}")
    message(STATUS "${CMAKE_BUILD_TYPE} linker flags for shared libs: ${CMAKE_SHARED_LINKER_FLAGS_${_type}}")
    unset(_type)
endif()
