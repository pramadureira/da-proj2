cmake_minimum_required(VERSION 3.23)
project(feup_da_proj2)

set(CMAKE_CXX_STANDARD 14)

add_executable(feup_da_proj2 main.cpp code/src/Reader.cpp code/headers/Reader.h code/headers/Graph.h code/src/Graph.cpp code/headers/VertexEdge.h code/src/VertexEdge.cpp code/headers/Menu.h code/headers/Printer.h code/src/Printer.cpp code/src/Menu.cpp code/headers/MutablePriorityQueue.h)
