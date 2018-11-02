# find qtcore
find_package(Qt5 REQUIRED Core)

list (APPEND JEPLULIBFINDER_SRC "JepluLibFinder.cpp")

# Build and link targets
add_library(JepluLibFinder STATIC ${JEPLULIBFINDER_SRC})
target_link_libraries(JepluLibFinder Qt5::Core)
