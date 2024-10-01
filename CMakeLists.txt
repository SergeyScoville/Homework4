# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(Homework4 VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directory for headers
include_directories(${CMAKE_SOURCE_DIR}/src)

# Addthe executable target
add_executable(Homework4
    ${CMAKE_SOURCE_DIR}/src/main_revised.cxx
)

add_executable(Homework4union
    ${CMAKE_SOURCE_DIR}/src/main_union.cxx
)

add_executable(Homework4revised
    ${CMAKE_SOURCE_DIR}/src/main_revised.cxx
)

add_definitions(-DDATA_DIR="${CMAKE_SOURCE_DIR}/data/")
