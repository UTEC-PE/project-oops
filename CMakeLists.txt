cmake_minimum_required(VERSION 3.10)
project(project_oops)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(project_oops
        edge.h
        graph.h
        main.cpp
        node.h)
