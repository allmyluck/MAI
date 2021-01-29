cmake_minimum_required(VERSION 3.10)
project(os_lab_06)

set(CMAKE_CXX_STANDARD 17)

add_executable(terminal main_node.cpp)
set_target_properties(
    terminal PROPERTIES
        COMPILE_OPTIONS "-g;-Wall;-Wextra;-Wpedantic;"
)
add_executable(child_node child_node.cpp)
add_library(functions server_functions.cpp server_functions.h)

target_link_libraries(functions zmq)
target_link_libraries(terminal zmq functions)
target_link_libraries(child_node zmq functions)

