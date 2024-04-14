
FetchContent_Declare (
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/master.zip
)

FetchContent_MakeAvailable (googletest)


add_executable (bus_tests bus_test.cxx)
target_include_directories(bus_tests PRIVATE "${PROJECT_SOURCE_DIR}/include")
target_link_libraries (bus_tests gtest_main bus)

enable_testing ()
add_test (NAME frame_test COMMAND bus_tests)
