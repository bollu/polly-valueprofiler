cmake_minimum_required(VERSION 3.4.3)
project(valueprofiler)

# Colors when compiling with clang
set(CMAKE_CXX_FLAGS "-fdiagnostics-color=always")
set(CMAKE_C_FLAGS "-fdiagnostics-color=always")

add_library(valueprofiler src/valueprofiler.cpp)
include_directories(valueprofiler include)

set_target_properties(valueprofiler PROPERTIES CXX_STANDARD 11)

