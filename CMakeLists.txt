cmake_minimum_required(VERSION 3.1.0)

# Project
project(jeplu)
set(CMAKE_BUILD_TYPE Release)

# Extra definitions
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Enable Cmake to run moc when it is needed.
set(CMAKE_AUTO_MOC ON)

# Linking libraries should be appended in this variable.
set(JEPLU_LINK_LIBS)

################# QT #########################
# Find Qt modules for loaders
if(MSVC)
    MESSAGE("MSVC compiler")
    set(CMAKE_PREFIX_PATH "C:\\Qt\\5.10.0\\msvc2015_64")
elseif(MINGW)
    MESSAGE("MINGW compiler")
    set(CMAKE_PREFIX_PATH "C:\\Qt\\5.10.0\\mingw53_32")
endif(MSVC)
find_package(Qt5Core)

# Add qtloader as static library
add_library(qtloader "${PROJECT_SOURCE_DIR}/src/qtloader.cpp")
target_link_libraries(qtloader Qt5::Core)
LIST(APPEND JEPLU_LINK_LIBS qtloader)
################# QT #########################

# Insert DL Libs to be linked.
if (UNIX)
    LIST(APPEND JEPLU_LINK_LIBS ${CMAKE_DL_LIBS})
endif (UNIX)

# Jeplu external
include_directories("${PROJECT_SOURCE_DIR}/include")
file (GLOB JEPLU_INCLUDE "${PROJECT_SOURCE_DIR}/include/*.hpp"
                         "${PROJECT_SOURCE_DIR}/include/*.h")

# Jeplu files
include_directories("${PROJECT_SOURCE_DIR}/src")
file(GLOB JEPLU_SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

if(NOT UNIX)
    LIST(REMOVE_ITEM JEPLU_SOURCES "${PROJECT_SOURCE_DIR}/src/dlloader.cpp")
endif(NOT UNIX)

# Example files
#include_directories("${PROJECT_SOURCE_DIR}/example")
#file(GLOB EXAMPLE_SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

# Build
add_executable(jeplu main.cpp ${JEPLU_SOURCES} ${JEPLU_INCLUDE} ${EXAMPLE_SOURCES})

target_link_libraries(jeplu ${JEPLU_LINK_LIBS})
