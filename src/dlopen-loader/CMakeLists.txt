set(INCLUDE_FILES "${PROJECT_SOURCE_DIR}/include/dlplugincreator.h"
                  "${PROJECT_SOURCE_DIR}/include/IPlugin.hpp")

# Create DlLoader static lib
list(APPEND LOADERS_SRC "DlLoader.cpp")
   
# Link with Dl lib
list(APPEND LIST_LINK_LIBRARY ${CMAKE_DL_LIBS})

# Build and link targets
add_library(dlopen-loader ${LOADERS_SRC} ${INCLUDE_FILES})
target_link_libraries(dlopen-loader ${LIST_LINK_LIBRARY})
