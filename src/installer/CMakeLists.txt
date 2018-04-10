### QT LOADER ###
# Find Qt package
find_package(Qt5 REQUIRED Core)
# Link with Qt
list(APPEND QT_CORE_LIB Qt5::Core)

find_library(ZIP_LIB zip)

# Set src files
set (JEPLU_INSTALLER_SRC "Zip.cpp"
                         "PluginInstaller.cpp")
                         
# Build installer module
add_library(installer ${JEPLU_INSTALLER_SRC})

# link libzip
target_link_libraries(installer ${ZIP_LIB} ${QT_CORE_LIB})

