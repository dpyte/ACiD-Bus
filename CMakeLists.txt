cmake_minimum_required(VERSION 3.22.1)
project(bus C CXX)

set (CMAKE_C_STANDARD 11)
set (CMAKE_CXX_STANDARD 17)

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    message (STATUS "Enabling extra debug info ...")
    set (ENABLE_EXTRA_DEBUG ON)
    set (ENABLE_DEBUG_MODE 1)
endif ()

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message (STATUS "Setting build type to 'Debug' as none was specified.")
    set (CMAKE_BUILD_TYPE Debug
            CACHE STRING "Choose the type of build" FORCE)

    set_property(CACHE CMAKE_BUILD_TYPE
            PROPERTY STRINGS
            "Debug"
            "Release"
            "RelWithDebInfo")
endif ()

############################################################
# ccache
find_program (CCACHE_FOUND ccache)
if (CCACHE_FOUND)
    message (STATUS "Using ccache")
    set_property (GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
endif ()

option (ENABLE_TESTING "Enable testing for this library" True)

############################################################
## print info
message (STATUS "build info:")
message (STATUS "  Host System: ${CMAKE_HOST_SYSTEM}")
message (STATUS "  Host System Name: ${CMAKE_HOST_SYSTEM_NAME}")
message (STATUS "  Host System Processor: ${CMAKE_HOST_SYSTEM_PROCESSOR}")

############################################################
## check required libraries
include (FetchContent)
include (CheckCXXCompilerFlag)
find_package (PkgConfig REQUIRED)

add_compile_options (-fno-builtin)
add_compile_options (-fstack-protector-strong)
if(CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "armv7l") # Raspberry Pi 4
    add_compile_options("-mcpu=cortex-a72")
elseif(CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "x86_64") # WSL2 on x86-64
    add_compile_options("-march=native")
endif()

link_libraries (-fstack-protector-strong)

set (Bus_INCLUDE_HEADERS
    include/bus.h
        include/types.h
        include/frame.h
        include/frame/header.h
        include/frame/general.h
        include/frame/buffer.h
)

set (Bus_INCLUDE_SOURCES
    lib/bus.c
        lib/frame.c
        lib/frame/header.c
        lib/frame/general.c
        lib/frame/buffer.c
)

add_library(bus STATIC ${Bus_INCLUDE_HEADERS} ${Bus_INCLUDE_SOURCES})
target_include_directories(bus PRIVATE include)
target_link_directories(bus PRIVATE include)

if (${ENABLE_TESTING})
    add_subdirectory (test)
endif ()