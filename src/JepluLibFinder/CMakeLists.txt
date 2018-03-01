# Find Qt package
find_package(Qt5 REQUIRED Core)

list (APPEND JEPLULIBFINDER_SRC "JepluLibFinder.cpp")

# Link with Qt
list(APPEND JEPLULIBFINDER_LINKS Qt5::Core)

# Build and link targets
add_library(JepluLibFinder ${JEPLULIBFINDER_SRC})
target_link_libraries(JepluLibFinder ${JEPLULIBFINDER_LINKS})
