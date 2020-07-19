project(jeplu-utest)

# Include the files for testing.
set(INCLUDE_TESTS "${CMAKE_SOURCE_DIR}/src/core/PluginManager.cpp"
                  "${CMAKE_SOURCE_DIR}/src/core/PluginFactory.cpp")
                       
# Include directories used for testing.
include_directories("${CMAKE_SOURCE_DIR}/include"
                    "${CMAKE_SOURCE_DIR}/src"
                    "${CMAKE_SOURCE_DIR}/src/installer"
                    "PluginManager/")

# Include the test source files.
set(UNIT_TEST_SOURCES  "main.cpp"
                       "PluginManager/FakeLibFinder.hpp"
                       "PluginManager/PluginManagerTest.hpp")

# Build
add_executable(jeplu-utest ${UNIT_TEST_SOURCES} ${INCLUDE_TESTS})

# Links the library with components.
target_link_libraries(jeplu-utest gtest installer)
