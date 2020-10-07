set(_allowable_build_types Debug Release RelWithDebInfo MinSizeRel)

# Specify the build type
if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "Setting build type to 'Release' as none was specified.")
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
elseif(NOT CMAKE_BUILD_TYPE IN_LIST _allowable_build_types)
    message(FATAL_ERROR "Invalid build type: ${CMAKE_BUILD_TYPE}")
endif()

unset(_allowable_build_types)
