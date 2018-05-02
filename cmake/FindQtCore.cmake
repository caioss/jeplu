# Find Qt package
find_package(Qt5 REQUIRED Core)

# Link with Qt
list(APPEND QTCORE_LIBRARY Qt5::Core)

