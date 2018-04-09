find_library(ZIP_LIB libzip.so)

# Set src files
set (JEPLU_INSTALLER_SRC "Zip.cpp")
                         
# Build installer module
add_library(installer ${JEPLU_INSTALLER_SRC})

# link libzip
target_link_libraries(installer ${ZIP_LIB})

