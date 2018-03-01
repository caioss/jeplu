# Jeplu files
include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories("${PROJECT_SOURCE_DIR}/src/core")

set(COMPONENTS loaders JepluLibFinder)
foreach(comp ${COMPONENTS})
    include_directories("${CMAKE_CURRENT_SOURCE_DIR}/${comp}")
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/${comp}")
endforeach()

set(JEPLU_SOURCES "core/PluginFactory.cpp"
                  "core/PluginManager.cpp"
                  "../example/custom-proxy/QCustomProxy.cpp")

# Build
add_executable(${CMAKE_PROJECT_NAME} "${PROJECT_SOURCE_DIR}/main.cpp" ${JEPLU_SOURCES} ${JEPLU_INCLUDE})

target_link_libraries(jeplu ${COMPONENTS})
