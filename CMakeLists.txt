cmake_minimum_required(VERSION 3.15)

project(BigInt)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(main main.cpp operator.cpp BigInt.cpp)

