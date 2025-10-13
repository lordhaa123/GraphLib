cmake_minimum_required(VERSION 3.4)
project(GraphLib)

add_subdirectory(pybind11)

include_directories(include)

pybind11_add_module(graphlib src/graphlib.cpp)