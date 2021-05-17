find_package(Java)
find_package(JNI)
if (Java_FOUND AND JNI_FOUND)
    include(UseJava)

    # Java bindings to libre2c.
    # Generate header for libre2c_jni.
    add_jar(RE2C
        libre2c/RE2C.java
        GENERATE_NATIVE_HEADERS RE2C-native
        ENTRY_POINT re2c.RE2C
    )

    # Build libre2c_jni.
    add_library(re2c_jni SHARED libre2c/RE2C.cpp)
    target_include_directories(re2c_jni PRIVATE "${CMAKE_SOURCE_DIR}/lib")
    target_link_libraries(re2c_jni RE2C-native libre2c_shared)

    # Build ReTdfa library and the benchmark.
    add_jar(ReTdfa
        ReTdfa.java
        INCLUDE_JARS RE2C
        ENTRY_POINT ReTdfa
    )

    # Python script that runs the benchmark.
    set(builddir ".")
    configure_file(run.py.in run.py @ONLY)
endif()
