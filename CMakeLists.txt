cmake_minimum_required(VERSION 3.4...3.18 FATAL_ERROR)
project(pyhpx CXX)

set(CMAKE_PREFIX_PATH /home/matrix/pyhpx/debug_hpx/hpx/cmake-install/Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fstack-protector")
set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_PREFIX_PATH /home/matrix/pyhpx/release_hpx/hpx/cmake_install)


find_package(HPX REQUIRED)
add_subdirectory(pybind11)

add_executable(inter src/inter.cpp)
target_link_libraries(inter PUBLIC HPX::hpx HPX::wrap_main pybind11::embed)

pybind11_add_module(pyhpx src/binding.cpp)
target_link_libraries(pyhpx PUBLIC HPX::hpx HPX::wrap_main)