cmake_minimum_required(VERSION 3.10)
project(acm_library)

set(CMAKE_CXX_STANDARD 17)

add_executable(acm_library main.cpp matrix.h bit.h other.h helper.h legacy.h tries.h tarjan.h extension.h)