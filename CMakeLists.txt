cmake_minimum_required(VERSION 2.6)

# Enable debug symbols by default
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

project(foundation)
enable_testing()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

# Release and debug flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -ggdb -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")

# Directory structure
set(SRC_DIR     ${PROJECT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(LIB_DIR     ${PROJECT_SOURCE_DIR}/lib)
set(TEST_DIR    ${PROJECT_SOURCE_DIR}/test)

include_directories(${INCLUDE_DIR})
include_directories(${LIB_DIR})

add_subdirectory(${SRC_DIR})
add_subdirectory(${TEST_DIR})
