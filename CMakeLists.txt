cmake_minimum_required(VERSION 3.4.3)
project(valueprofiler)

add_library(valueprofiler SHARED src/valueprofiler.cpp)
include_directories(valueprofiler include)

set_target_properties(valueprofiler PROPERTIES CXX_STANDARD 11)

