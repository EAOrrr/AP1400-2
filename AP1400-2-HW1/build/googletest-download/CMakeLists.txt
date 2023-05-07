cmake_minimum_required(VERSION 2.8.2)

project(googletest-download NONE)

include(ExternalProject)
ExternalProject_Add(googletest
        GIT_REPOSITORY    https://github.com/google/googletest.git
        GIT_TAG           release-1.10.0
        SOURCE_DIR        "/mnt/d/practice/h_programming basis/AP1400-2/AP1400-2-HW1/build/googletest-src"
        BINARY_DIR        "/mnt/d/practice/h_programming basis/AP1400-2/AP1400-2-HW1/build/googletest-build"
        CONFIGURE_COMMAND ""
        BUILD_COMMAND     ""
        INSTALL_COMMAND   ""
        TEST_COMMAND      ""
        )
