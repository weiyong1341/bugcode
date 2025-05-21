cmake_minimum_required(VERSION 3.4...3.18)
project(example LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11) 
# add_subdirectory(pybind11)
set(pybind11_DIR "/root/workspace/pybind11_demo/pybind11/share/cmake/pybind11")
find_package(pybind11 REQUIRED)

pybind11_add_module(example example.cpp)