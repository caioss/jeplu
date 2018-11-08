# find qtcore
find_package(Qt5 REQUIRED Core)

# Build and link targets
add_library(JepluLibFinder STATIC "JepluLibFinder.cpp")
target_link_libraries(JepluLibFinder Qt5::Core)
