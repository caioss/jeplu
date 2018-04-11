# find qtcore
find_package(QtCore REQUIRED)

list (APPEND JEPLULIBFINDER_SRC "JepluLibFinder.cpp")

# Build and link targets
add_library(JepluLibFinder ${JEPLULIBFINDER_SRC})
target_link_libraries(JepluLibFinder ${QTCORE_LIBRARY})
