set(_allowed_build_types Debug Release RelWithDebInfo MinSizeRel)

# 1. The default value for CMAKE_BUILD_TYPE is an empty string.
# 2. User can set CMAKE_BUILD_TYPE to any value at the cmake command line.
#
# Therefore, we check both cases, and make sure that we are dealing with
# a known build type (if any).
#
# For more see discussion at https://github.com/skvadrik/re2c/pull/316
if(CMAKE_BUILD_TYPE AND NOT CMAKE_BUILD_TYPE IN_LIST _allowed_build_types)
    message(FATAL_ERROR "Invalid build type: ${CMAKE_BUILD_TYPE}")
endif()

unset(_allowed_build_types)
