# Jeplu files
include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories("${PROJECT_SOURCE_DIR}/src/core")

# Links the implementation of the interfaces ILibFinder or IPluginLoader
# If the developer don't want Qt as dependecy or if the file structure should be other, just removeits implementation
# and link with another created by its own. Create another ILibFinder/IPluginLoader, insert its CMakeList target name
# here (wich represents the same name of its subdir. e.g: JepluLibFinder/CMakeLists.txt) and register into
# `IPluginManager` changing the `Jeplu.cpp`, at the registration section.
set(COMPONENTS loaders JepluLibFinder)

# Including components subdir
foreach(comp ${COMPONENTS})
    include_directories("${CMAKE_CURRENT_SOURCE_DIR}/${comp}")
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/${comp}")
endforeach()

set(JEPLU_SOURCES "core/PluginFactory.cpp"
                  "core/PluginManager.cpp"
                  "../example/custom-proxy/QCustomProxy.cpp")

# Build
add_executable(${CMAKE_PROJECT_NAME} "${PROJECT_SOURCE_DIR}/main.cpp" ${JEPLU_SOURCES} ${JEPLU_INCLUDE})

# Links the library with components.
target_link_libraries(jeplu ${COMPONENTS})
