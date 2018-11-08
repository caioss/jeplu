find_package(libzip)
find_package(Qt5 REQUIRED Core)

# Set src files
set (INSTALLER_SOURCE "Zip.cpp"
                      "Archive.cpp"
                      "PluginArchive.cpp")
                         
message("libzip include dir: ${libzip_INCLUDE_DIR}")
message("libzip library: ${libzip_LIBRARY}")

# Build installer module
add_library(installer STATIC ${INSTALLER_SOURCE})

# link libzip
target_link_libraries(installer Qt5::Core libzip::libzip)

