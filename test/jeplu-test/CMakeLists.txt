project(jeplu-test)

find_package(gtest)

if (NOT DEFINED EXAMPLE_DIR)
    message(FATAL_ERROR "Example dir not defined.")
endif()

# Include directories used for testing.
include_directories("${EXAMPLE_DIR}/custom-adapter/"
                    "Jeplu/")

# Include the test source files.
set(TEST_SOURCES  "main.cpp"
                  "Jeplu/JepluTest.hpp"
                  "${EXAMPLE_DIR}/custom-adapter/QCustomAdapter.cpp")

# Build
add_executable(jeplu-test ${TEST_SOURCES})

# Links the library with components.
target_link_libraries(jeplu-test gtest::gtest jeplu)
