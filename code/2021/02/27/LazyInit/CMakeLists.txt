cmake_minimum_required(VERSION 3.15)

project(CppLazyInit LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(LazyInit LazyInit.cpp)

add_executable(runner Runner.cpp)
