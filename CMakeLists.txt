cmake_minimum_required(VERSION 3.1.0)

# Project
project(jeplu)
set(CMAKE_BUILD_TYPE Debug)

# Project extra definitions

# Extra definitions
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Enable Cmake to run moc when it is needed.
set(CMAKE_AUTO_MOC ON)

# Jeplu external
include_directories("${PROJECT_SOURCE_DIR}/include")
set(JEPLU_INCLUDE "${PROJECT_SOURCE_DIR}/include/dlplugincreator.h"
                  "${PROJECT_SOURCE_DIR}/include/IPlugin.hpp"
                  "${PROJECT_SOURCE_DIR}/include/IPluginProxy.hpp"
                  "${PROJECT_SOURCE_DIR}/include/IQtPlugin.hpp")

# Include src main CMakeLists
add_subdirectory("${PROJECT_SOURCE_DIR}/src")
