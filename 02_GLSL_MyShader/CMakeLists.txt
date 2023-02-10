cmake_minimum_required(VERSION 3.24)
project(GLSL_MyShader)

set(CMAKE_CXX_STANDARD 11)

include_directories(D:/Studys_Files/CPP_Studys/CPP_Environment/glad/include)
include_directories(D:/Studys_Files/CPP_Studys/CPP_Environment/GLFW/glfw-3.3.8/include)

link_directories(D:/Studys_Files/CPP_Studys/CPP_Environment/GLFW/glfw-3.3.8/lib-mingw-w64)

add_executable(GLSL_MyShader
        src/glad.c
        main.cpp Shader.h)

target_link_libraries(
        GLSL_MyShader
        libglfw3.a
)
