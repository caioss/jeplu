# Set src files
set (JEPLU_CORE_SRC "PluginManager.cpp"
                    "PluginFactory.cpp")

# Build core module
add_library(core ${JEPLU_CORE_SRC} ${JEPLU_INCLUDE})
