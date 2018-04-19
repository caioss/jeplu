cmake_minimum_required(VERSION 3.8)

project(jeplu-test)

######## Google Test
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
set(GOOGLETEST_SRC "${PROJECT_SOURCE_DIR}/ext/googletest-src")
add_subdirectory(${GOOGLETEST_SRC}
                 ${PROJECT_BINARY_DIR}/googletest-build
                                  EXCLUDE_FROM_ALL)

enable_testing()

# Include examples for testing plugins.
include_directories("${CMAKE_SOURCE_DIR}/src")

set(INCLUDE_TESTS "${CMAKE_SOURCE_DIR}/src/core/PluginManager.cpp"
                  "${CMAKE_SOURCE_DIR}/src/core/PluginFactory.cpp")

set(TEST_SOURCES  "main.cpp"
                  "FakeLibFinder.hpp"
                  "PluginManagerTest.hpp")

# Build
add_executable(jeplu-test ${TEST_SOURCES} ${INCLUDE_TESTS})

# Links the library with components.
target_link_libraries(jeplu-test gtest)

# First Simple Google Test
#add_executable(PluginManagerTest PluginManagerTest.hpp)
#target_link_libraries(PluginManagerTest gtest_main gtest)
add_test(NAME jeplu-test COMMAND jeplu-test)
