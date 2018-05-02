cmake_minimum_required(VERSION 3.1.0)

# Project
project(jeplu)
set(CMAKE_BUILD_TYPE Debug)

# set cmake modules path
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# Project extra definitions
# Options. Turn off with 'cmake -Dtest=FALSE'.
option(test "Build all tests." TRUE) # Makes boolean 'test' available.

# Extra definitions
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Change output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Enable Cmake to run moc when it is needed.
set(CMAKE_AUTO_MOC ON)

# Jeplu external
include_directories("${PROJECT_SOURCE_DIR}/include")
set(JEPLU_INCLUDE "${PROJECT_SOURCE_DIR}/include/dlplugincreator.h"
                  "${PROJECT_SOURCE_DIR}/include/IPlugin.hpp"
                  "${PROJECT_SOURCE_DIR}/include/IPluginProxy.hpp"
                  "${PROJECT_SOURCE_DIR}/include/IQtPlugin.hpp"
                  "${PROJECT_SOURCE_DIR}/include/Jeplu.hpp")

# Include src main CMakeLists
add_subdirectory("${PROJECT_SOURCE_DIR}/src")

# Include tests if enabled
if (test)
 add_subdirectory("${PROJECT_SOURCE_DIR}/test")
endif ()
