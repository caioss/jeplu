### QT LOADER ###
# Find Qt package
find_package(Qt5 REQUIRED Core)
# Link with Qt
list(APPEND LOADERS_LINK_LIBS Qt5::Core)

set(INCLUDE_FILES "${PROJECT_SOURCE_DIR}/include/dlplugincreator.h"
                  "${PROJECT_SOURCE_DIR}/include/IPlugin.hpp"
                  "${PROJECT_SOURCE_DIR}/include/IQtPlugin.hpp")

list (APPEND LOADERS_SRC "QtLoader.cpp")

### DL LOADER ###
if (UNIX)
   # Create DlLoader static lib
   list(APPEND LOADERS_SRC "DlLoader.cpp")
   
   # Link with Dl lib
   list(APPEND LOADERS_LINK_LIBS ${CMAKE_DL_LIBS})
endif (UNIX)


# Build and link targets
add_library(loaders ${LOADERS_SRC} ${INCLUDE_FILES})
target_link_libraries(loaders ${LOADERS_LINK_LIBS})
