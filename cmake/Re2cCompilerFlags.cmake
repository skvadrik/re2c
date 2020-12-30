include(CheckCXXCompilerFlag)

# Iff C++ compiler recognizes 'flag', append 'flag' and 'implied-flags' to re2c_cxx_flags
# (Second param 'implied-flags' is needed for warning suppressions '-Wno-<warning>':
# GCC warns about unrecognized suppressions options only in presence of other warnings,
# which makes it hard to test for them with autoconf.)
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

get_property(isMultiConfig  GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
set(re2c_cxx_flags "")

# Set default optimization flag if there is no build type provided.
# CMAKE_BUILD_TYPE is not used by multi-configuration generators.
if(NOT CMAKE_BUILD_TYPE AND NOT isMultiConfig)
    try_cxxflag("-O2")
endif()

# The following flags are not supported by Visual Studio.
# Thus, we can speed up the configuration of the project
# by avoiding unnecessary checks.
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

    # Prepend to avoid overriding user-defined options set with -DCMAKE_CXX_FLAGS.
    set(CMAKE_CXX_FLAGS "${re2c_cxx_flags} ${CMAKE_CXX_FLAGS}")
else()
    # /Wall enables all warnings that are off by default including
    # some of the ones GCC/Clang enables through -Wxxxx flags.
    try_cxxflag("/Wall")
    try_cxxflag("/EHsc")    # Support C++ exceptions.

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
