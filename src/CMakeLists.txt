# Jeplu files
include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories("${PROJECT_SOURCE_DIR}/src/core")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Adds core to build.
set(MODULES core)

# Adds JepluLibFinder to be built if not excluded
if (no-default-libfinder)
    add_definitions(-DNO_DEFAULT_LIBFINDER)
else ()
    list(APPEND MODULES "JepluLibFinder")
endif()

# Adds dlopen-loader to be built if UNIX system and if it's not excluded.
if (no-dlopen-loader)
    add_definitions(-DNO_DL_LOADER)
elseif (UNIX)
    list(APPEND MODULES "dlopen-loader")
endif ()

# Adds qt-loader to be built if not excluded.
if (no-qt-loader)
    add_definitions(-DNO_QT_LOADER)
else ()
    list(APPEND MODULES "qt-loader")
endif ()

# Adds installer to be built if not excluded.
if (no-plugin-installer)
    add_definitions(-DNO_PLUGIN_INSTALLER)
else ()
    list(APPEND MODULES "installer")
endif ()

# Build components that was added above.
foreach(module ${MODULES})
    message("Module " ${module} " marked for build.")
    include_directories("${CMAKE_CURRENT_SOURCE_DIR}/${module}")
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/${module}")
endforeach()

# Adds Jeplu source files.
set(JEPLU_SOURCES "Jeplu.cpp")

# Build shared
# TODO: adds option to build static.
add_library(jeplu SHARED ${JEPLU_SOURCES} ${JEPLU_INCLUDE})

# Links the library with components.
target_link_libraries(jeplu ${MODULES})

# Set definition to export symbols.
target_compile_definitions(jeplu PRIVATE JEPLU_EXPORTS)

set_target_properties(jeplu PROPERTIES PUBLIC_HEADER "${INCLUDE_STR}")

# Install target to lib dir and its public headers to include dir.
install(FILES ${JEPLU_INCLUDE} DESTINATION "include/${JEPLU_NAME_VERSION}/")
install(TARGETS jeplu DESTINATION "lib/${JEPLU_NAME_VERSION}/")
