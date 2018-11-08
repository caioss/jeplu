cmake_minimum_required(VERSION 3.8)

# Build example plugins for test usage.
#add_subdirectory("example/qt-custom-plugin/")

#set_target_properties(qcustom_plugin PROPERTIES
#                      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/plugins/qcustom_plugin/"
#                      LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/plugins/qcustom_plugin/")

enable_testing()

# Sets EXAMPLE_DIR for test usage.
set(EXAMPLE_DIR "../example/")

add_subdirectory("unit-tests")
add_subdirectory("jeplu-test")

#add_test(NAME jeplu-test COMMAND jeplu-test)

