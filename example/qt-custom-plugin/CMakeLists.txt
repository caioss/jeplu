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

################# QT #########################
find_package(Qt5 REQUIRED Core)
################# QT #########################
# Include jeplu files.
file (GLOB JEPLU_INCLUDE "../include/*.hpp"
                         "../include/*.h")

# Add flags to compiler.
#add_definitions(-[compiler_definition])

add_library(${PROJECT_NAME} SHARED
			    "qcustomplugin.cpp"
			    ${JEPLU_INCLUDE})

target_include_directories(${PROJECT_NAME} PUBLIC "../include/")

target_link_libraries(${PROJECT_NAME} Qt5::Core)
