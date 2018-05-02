# Jeplu files
include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories("${PROJECT_SOURCE_DIR}/src/core")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Links the implementation of the interfaces ILibFinder or IPluginLoader
# If the developer don't want Qt as dependecy or if the file structure should be other, just removeits implementation
# and link with another created by its own. Create another ILibFinder/IPluginLoader, insert its CMakeList target name
# here (wich represents the same name of its subdir. e.g: JepluLibFinder/CMakeLists.txt) and register into
# `IPluginManager` changing the `Jeplu.cpp`, at the registration section.
set(COMPONENTS core loaders JepluLibFinder)

# Including components subdir
foreach(comp ${COMPONENTS})
    include_directories("${CMAKE_CURRENT_SOURCE_DIR}/${comp}")
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/${comp}")
endforeach()

set(JEPLU_SOURCES "Jeplu.cpp")

# Build
add_library(jeplu SHARED ${JEPLU_SOURCES} ${JEPLU_INCLUDE})

# Links the library with components.
target_link_libraries(jeplu ${COMPONENTS})

# Set definition to export symbols.
target_compile_definitions(jeplu PRIVATE JEPLU_EXPORTS)

set_target_properties(jeplu PROPERTIES PUBLIC_HEADER "${INCLUDE_STR}")

# Install target to lib dir and its public headers to include dir.
install(FILES ${JEPLU_INCLUDE} "Jeplu.hpp" DESTINATION "${PROJECT_BINARY_DIR}/include")
install(TARGETS jeplu DESTINATION "${PROJECT_BINARY_DIR}/lib")
