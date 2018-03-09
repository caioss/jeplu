# Set include files used by this module
set(INCLUDE_FILES "${PROJECT_SOURCE_DIR}/include/IPlugin.hpp"
                  "${PROJECT_SOURCE_DIR}/include/IPluginProxy.hpp")
                  
# Set src files
set (JEPLU_CORE_SRC "PluginManager.cpp"
                    "PluginFactory.cpp")

# Build core module
add_library(core ${JEPLU_CORE_SRC} ${INCLUDE_FILES})
