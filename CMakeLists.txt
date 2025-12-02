cmake_minimum_required(VERSION 3.15)
project(AoC CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build type (Debug, Release)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Address sanitizer
option(ASAN "Enable Address Sanitizer" OFF)
if(ASAN)
    message(STATUS "Address Sanitizer enabled")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
endif()

# Debug flags
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Debug mode enabled")
endif()

# Gather all AoC day files with <day>_<a/b>_anything.cpp
file(GLOB DAY_FILES src/??_[ab]_*.cpp)

foreach(SRC_FILE ${DAY_FILES})
    get_filename_component(FNAME ${SRC_FILE} NAME_WE)   # e.g., 01_a_trebuchet
    string(REGEX MATCH "^[0-9][0-9]_[ab]" PREFIX ${FNAME})      # extract prefix

    # Use the full basename as executable name (01_a_trebuchet)
    add_executable(${PREFIX} ${SRC_FILE})
endforeach()

