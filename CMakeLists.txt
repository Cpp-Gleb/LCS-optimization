cmake_minimum_required(VERSION 3.14)
project(LCSFastDistanceMultiplication)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB LIB_SOURCES "${PROJECT_SOURCE_DIR}/lib/*.cpp")
add_library(lcs_lib ${LIB_SOURCES})
target_include_directories(lcs_lib PUBLIC ${PROJECT_SOURCE_DIR}/lib)

file(GLOB BIN_SOURCES "${PROJECT_SOURCE_DIR}/bin/*.cpp")
add_executable(LCSFastDistanceMultiplication ${BIN_SOURCES})
target_link_libraries(LCSFastDistanceMultiplication lcs_lib)

include(FetchContent)
if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB TEST_SOURCES "${PROJECT_SOURCE_DIR}/tests/*.cpp")
message(STATUS "Test sources: ${TEST_SOURCES}")
if(TEST_SOURCES)
    add_executable(runTests ${TEST_SOURCES})
    target_include_directories(runTests PUBLIC ${PROJECT_SOURCE_DIR}/lib)
    target_link_libraries(runTests lcs_lib gtest gtest_main)

    include(GoogleTest)
    gtest_discover_tests(runTests)
else()
    message(WARNING "No test sources found in ${PROJECT_SOURCE_DIR}/tests")
endif()
