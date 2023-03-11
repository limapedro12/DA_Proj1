cmake_minimum_required(VERSION 3.24)
project(DA_Proj1)

set(CMAKE_CXX_STANDARD 17)

add_executable(DA_Proj1 main.cpp Classes/Municipality.cpp Classes/Municipality.h Classes/District.cpp Classes/District.h Classes/Graph.cpp Classes/Graph.h Classes/VertexEdge.cpp Classes/VertexEdge.h Functions/read_data.h Functions/read_data.cpp)
