find_package(zip)
find_package(Qt5 REQUIRED Core)

# Include libzip headers directory
include_directories(${LIBZIP_INCLUDE_DIR})

# Set src files
set (INSTALLER_SOURCE "Zip.cpp"
                      "Archive.cpp"
                      "PluginArchive.cpp")
                         
message("libzip include dir: ${LIBZIP_INCLUDE_DIR}")
message("libzip library: ${LIBZIP_LIBRARY}")

# Build installer module
add_library(installer STATIC ${INSTALLER_SOURCE})

# link libzip
target_link_libraries(installer Qt5::Core ${zip})

