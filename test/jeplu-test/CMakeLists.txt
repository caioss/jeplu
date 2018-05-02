project(jeplu-test)

# Include directories used for testing.
include_directories("${CMAKE_SOURCE_DIR}/src"
                    "${CMAKE_SOURCE_DIR}/include"
                    "Jeplu/")

# Include the test source files.
set(TEST_SOURCES  "main.cpp"
                  "Jeplu/JepluTest.hpp")

# Build
add_executable(jeplu-test ${TEST_SOURCES} ${INCLUDE_TESTS})

# Links the library with components.
target_link_libraries(jeplu-test gtest jeplu)
