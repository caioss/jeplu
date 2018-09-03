# find libzip
find_package(LibZip REQUIRED)

# find qtcore
find_package(QtCore REQUIRED)

# Include libzip headers directory
include_directories(${LIBZIP_INCLUDE_DIR_ZIP})

# Set src files
set (INSTALLER_SOURCE    "Zip.cpp"
                         "Archive.cpp"
                         "PluginArchive.cpp")
                         
message("libzip include dir: ${LIBZIP_INCLUDE_DIR_ZIP}")
message("libzip librar: ${LIBZIP_LIBRARY}")

# Build installer module
add_library(installer ${INSTALLER_SOURCE})

# link libzip
target_link_libraries(installer ${LIBZIP_LIBRARY} ${QTCORE_LIBRARY})

