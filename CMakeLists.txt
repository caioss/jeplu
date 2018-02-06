cmake_minimum_required(VERSION 3.1.0)

# Project
project(jeplu-example)
set(CMAKE_BUILD_TYPE Release)

# Extra definitions
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Jeplu files
include_directories("${PROJECT_SOURCE_DIR}/src")
file(GLOB JEPLU_SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

# Example files
include_directories("${PROJECT_SOURCE_DIR}/example")
file(GLOB EXAMPLE_SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

# Build
add_executable(jeplu-example ${JEPLU_SOURCES} ${EXAMPLE_SOURCES})
