cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(googletest
        GIT_REPOSITORY "https://github.com/google/googletest.git"
        GIT_TAG "release-1.12.1"
        )

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

include_directories(../inc)
add_executable(Speeture-Test
        ${SRC_FILES}
        test/PitchPeriodEstimatorTests.cpp
        )

target_link_libraries(
        Speeture-Test
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(Speeture-Test)
