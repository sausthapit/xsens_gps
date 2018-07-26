cmake_minimum_required(VERSION 3.10)

project(xsens_gps)

include_directories(/usr/local/xsens/include)

add_executable(xda_c_cpp src/main.cpp)