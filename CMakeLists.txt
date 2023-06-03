cmake_minimum_required(VERSION 3.4...3.18 FATAL_ERROR)
project(pyhpx CXX)

find_package(HPX)
add_subdirectory(pybind11)

pybind11_add_module(pyhpx src/binding.cpp)
target_link_libraries(pyhpx PUBLIC HPX::hpx HPX::wrap_main)

