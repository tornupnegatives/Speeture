cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 17)

project(Speeture)
option(SPEETURE_BUILD_TESTS "Build test programs" ON)

include_directories(inc)
add_library(${PROJECT_NAME}
        src/FeatureExtractor.cpp
        src/PitchPeriodEstimator.cpp
        )

if (SPEETURE_BUILD_TESTS)
    include(test/CMakeLists.txt)
endif()