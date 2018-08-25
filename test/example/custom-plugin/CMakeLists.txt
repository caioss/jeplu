cmake_minimum_required (VERSION 3.8.0)

# Project Language
set(LANGUAGE CXX)

# Project Name
set(PROJECT_NAME custom_plugin)

# Extra definitions
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include jeplu files.
file (GLOB JEPLU_INCLUDE "../../../include/*.hpp"
                         "../../../include/*.h")

include_directories("../../../include/")

MESSAGE("${JEPLU_INCLUDE}")

project (${PROJECT_NAME})

# Add flags to compiler.
#add_definitions(-[compiler_definition])

add_library(${PROJECT_NAME} SHARED
			    "CustomPlugin.cpp"
			    ${JEPLU_INCLUDE})                
