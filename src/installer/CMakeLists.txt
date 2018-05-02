# find libzip
find_package(LibZip REQUIRED)

# find qtcore
find_package(QtCore REQUIRED)

# Set src files
set (INSTALLER_SOURCE    "Zip.cpp"
                         "Archive.cpp"
                         "PluginInstaller.cpp")
                         
# Build installer module
add_library(installer ${INSTALLER_SOURCE})

# link libzip
target_link_libraries(installer ${LIBZIP_LIBRARY} ${QTCORE_LIBRARY})

