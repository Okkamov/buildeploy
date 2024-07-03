cmake_minimum_required(VERSION 3.29)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

set(MY_PROJECT_NAME buildeploy)
set(EXEC_FILE_NAME buildeploy) #bdcli
set(TEST_FILE_NAME testlist)

#SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin")

set(SOURCES_DIR ../src/)
set(INCLUDE_DIR ../include/)
set(SOURCES ${SOURCES_DIR}main.cpp ${INCLUDE_DIR}list.hpp)

set(TEST_DIR ../test/)
set(TEST_SRC testlist.cpp)

project(${MY_PROJECT_NAME} VERSION ${PROJECT_VESRION})

find_package(ZLIB REQUIRED)
find_package(fmt CONFIG REQUIRED)

# Main target
add_executable(${EXEC_FILE_NAME} ${SOURCES})

set_target_properties(${EXEC_FILE_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
target_link_libraries(${EXEC_FILE_NAME} PRIVATE ZLIB::ZLIB fmt::fmt)

# Test target
add_executable(${TEST_FILE_NAME} ${TEST_DIR}${TEST_SRC})

enable_testing()

find_package(GTest CONFIG REQUIRED)

# Add src to the include directories for the test target
target_include_directories(${TEST_FILE_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Add googletest to the include directories for the test target
target_include_directories(${TEST_FILE_NAME} PRIVATE ${GTEST_INCLUDE_DIRS}
)
target_link_libraries(${TEST_FILE_NAME} PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

add_test(AllTestsInMain ${TEST_FILE_NAME})

if (MSVC)
    target_compile_options(
        ${EXEC_FILE_NAME} PRIVATE
        /W4
    )
    target_compile_options(
        ${TEST_FILE_NAME} PRIVATE
        /W4
    )
else ()
    target_compile_options(
        ${EXEC_FILE_NAME} PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(
        ${TEST_FILE_NAME} PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()
