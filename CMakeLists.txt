cmake_minimum_required(VERSION 3.10)

project(geometry)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

add_executable(
    geometry main.cc
    src/glad.c 
    src/shader.cpp
    src/program.cpp
    
    src/bst.cpp
    src/avl.cpp
    src/rbtree.cpp

    src/gmath.cpp
    src/convex.cpp
    src/style.cpp
    src/shape.cpp
    src/window.cpp
)

target_link_libraries(geometry glfw3 X11 GL)