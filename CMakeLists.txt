cmake_minimum_required(VERSION 3.28)
project(hmc)

set(CMAKE_CXX_STANDARD 14)

add_executable(hmc main.cpp
        core/Hamming.cpp
        core/Hamming.hpp)
