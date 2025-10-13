cmake_minimum_required(VERSION 3.14)
project(GraphLib)

# --- Core C++ Library (Header-Only) ---
add_library(GraphLibCore INTERFACE)
target_include_directories(GraphLibCore INTERFACE include)

# --- pybind11 ---
add_subdirectory(pybind11)
pybind11_add_module(gphl src/graphlib.cpp)
target_link_libraries(gphl PRIVATE GraphLibCore)

# --- Testing with Catch2 ---
enable_testing()
include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.1
)
FetchContent_MakeAvailable(Catch2)

add_subdirectory(tests)