# find qtcore
find_package(QtCore REQUIRED)

list(APPEND LIST_LINK_LIBRARY ${QTCORE_LIBRARY})

set(INCLUDE_FILES "${PROJECT_SOURCE_DIR}/include/dlplugincreator.h"
                  "${PROJECT_SOURCE_DIR}/include/IPlugin.hpp"
                  "${PROJECT_SOURCE_DIR}/include/IQtPlugin.hpp")

list (APPEND LOADERS_SRC "QtLoader.cpp")

### DL LOADER ###
if (UNIX)
   # Create DlLoader static lib
   list(APPEND LOADERS_SRC "DlLoader.cpp")
   
   # Link with Dl lib
   list(APPEND LIST_LINK_LIBRARY ${CMAKE_DL_LIBS})
endif (UNIX)

# Build and link targets
add_library(loaders ${LOADERS_SRC} ${INCLUDE_FILES})
target_link_libraries(loaders ${LIST_LINK_LIBRARY})

