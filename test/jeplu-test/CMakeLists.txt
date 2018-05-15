project(jeplu-test)

if (NOT DEFINED EXAMPLE_DIR)
    message(FATAL_ERROR "Example dir not defined.")
endif()

# Include directories used for testing.
include_directories("${CMAKE_SOURCE_DIR}/src/"
                    "${CMAKE_SOURCE_DIR}/include/"
                    "${EXAMPLE_DIR}/custom-proxy/"
                    "Jeplu/")

# Include the test source files.
set(TEST_SOURCES  "main.cpp"
                  "Jeplu/JepluTest.hpp"
                  "${EXAMPLE_DIR}/custom-proxy/QCustomProxy.cpp")

# Build
add_executable(jeplu-test ${TEST_SOURCES} ${INCLUDE_TESTS})

# Links the library with components.
target_link_libraries(jeplu-test gtest jeplu)
