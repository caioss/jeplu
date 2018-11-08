# find qtcore
find_package(Qt5 REQUIRED Core)

set(INCLUDE_FILES "${PROJECT_SOURCE_DIR}/include/IPlugin.hpp"
                  "${PROJECT_SOURCE_DIR}/include/IQtPlugin.hpp")

# Build and link targets
add_library(qt-loader STATIC "QtLoader.cpp")
target_link_libraries(qt-loader Qt5::Core)

