# find qtcore
find_package(QtCore REQUIRED)

list(APPEND LIST_LINK_LIBRARY ${QTCORE_LIBRARY})

set(INCLUDE_FILES "${PROJECT_SOURCE_DIR}/include/IPlugin.hpp"
                  "${PROJECT_SOURCE_DIR}/include/IQtPlugin.hpp")

list (APPEND QT_LOADER_SRC "QtLoader.cpp")

# Build and link targets
add_library(qt-loader ${QT_LOADER_SRC} ${INCLUDE_FILES})
target_link_libraries(qt-loader ${LIST_LINK_LIBRARY})

