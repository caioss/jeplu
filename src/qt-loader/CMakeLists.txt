# find qtcore
find_package(Qt5 REQUIRED Core)

set(INCLUDE_FILES "${PROJECT_SOURCE_DIR}/include/IPlugin.hpp"
                  "${PROJECT_SOURCE_DIR}/include/IQtPlugin.hpp")

list (APPEND QT_LOADER_SRC "QtLoader.cpp")

# Build and link targets
add_library(qt-loader STATIC ${QT_LOADER_SRC} ${INCLUDE_FILES})
target_link_libraries(qt-loader Qt5::Core)

