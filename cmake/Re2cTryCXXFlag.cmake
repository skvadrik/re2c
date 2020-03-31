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
