cmake_minimum_required(VERSION 3.8)

project(jeplu-test)

# Extra definitions
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Test
# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
RESULT_VARIABLE result
WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
RESULT_VARIABLE result
WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${PROJECT_SOURCE_DIR}/ext/googletest-src
                 ${PROJECT_BINARY_DIR}/googletest-build
                                  EXCLUDE_FROM_ALL)

# Include examples for testing plugins.
include_directories("${CMAKE_SRC_DIR}/example/")

# Find jeplu library
include_directories("${CMAKE_SRC_DIR}/include/")
# Include lib output directory 
link_directories("${CMAKE_BINARY_DIR}/lib/")

set(TEST_SOURCES  "main.cpp"
                  "../example/custom-proxy/ICustomInterface.hpp"
                  "../example/custom-proxy/QCustomProxy.cpp")

# Build
add_executable(jeplu-test ${TEST_SOURCES} ${JEPLU_INCLUDE})

# Links the library with components.
target_link_libraries(jeplu-test jeplu gtest_main)
