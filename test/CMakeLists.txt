cmake_minimum_required(VERSION 3.8)

project(jeplu-test)

# Extra definitions
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories("../example/")

# Find Qt package
find_package(Qt5 REQUIRED Core)

# Find jeplu library
find_library(JEPLU_LINK jeplu PATHS "${PROJECT_BINARY_DIR}/../lib" NO_DEFAULT_PATH)
include_directories("${PROJECT_BINARY_DIR}/../include/")

set(TEST_SOURCES  "main.cpp"
                  "${PROJECT_BINARY_DIR}/../include/dlplugincreator.h"
                  "${PROJECT_BINARY_DIR}/../include/IPlugin.hpp"
                  "${PROJECT_BINARY_DIR}/../include/IPluginProxy.hpp"
                  "${PROJECT_BINARY_DIR}/../include/IQtPlugin.hpp"
                  "../example/custom-proxy/ICustomInterface.hpp"
                  "../example/custom-proxy/QCustomProxy.cpp")

# Build
add_executable(jeplu-test ${TEST_SOURCES} ${JEPLU_INCLUDE})

# Links the library with components.
target_link_libraries(jeplu-test Qt5::Core ${JEPLU_LINK})
