### QT LOADER ###
# Find Qt package
find_package(Qt5 REQUIRED Core)

list (APPEND LOADERS_SRC "qtloader.cpp")

# Link with Qt
list(APPEND LOADERS_LINK_LIBS Qt5::Core)


### DL LOADER ###
if (UNIX)
   # Create DlLoader static lib
   list(APPEND LOADERS_SRC "dlloader.cpp")
   
   # Link with Dl lib
   list(APPEND LOADERS_LINK_LIBS ${CMAKE_DL_LIBS})
endif (UNIX)


# Build and link targets
add_library(loaders ${LOADERS_SRC})
target_link_libraries(loaders ${LOADERS_LINK_LIBS})
