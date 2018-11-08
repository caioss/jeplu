cmake_minimum_required (VERSION 3.8.0)

# Project Name
set(PROJECT_NAME qcustom_plugin)

# The project name should be declared at the beginning.
project (${PROJECT_NAME})

# Project Language
set(LANGUAGE CXX)

# Extra definitions
set(CMAKE_BUILD_TYPE debug)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_AUTOMOC ON)

# Find Qt
find_package(Qt5 REQUIRED Core)

include_directories("../../../include/"
                    "../custom-adapter"
                    ${Qt5_INCLUDE_DIRS})

add_library(${PROJECT_NAME} SHARED "QCustomPlugin.cpp")

target_link_libraries(${PROJECT_NAME} Qt5::Core)
