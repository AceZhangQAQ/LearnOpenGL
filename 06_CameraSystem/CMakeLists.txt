################
# MacOs
################

cmake_minimum_required(VERSION 3.21)
project(CameraSystem)

set(CMAKE_CXX_STANDARD 11)

include_directories(includes/glad/include)
include_directories(/opt/homebrew/Cellar/glfw/3.3.8/include)
include_directories(includes/GLM)

link_directories(/opt/homebrew/Cellar/glfw/3.3.8/lib)

add_executable(CameraSystem
        includes/glad/src/glad.c
        includes/stb_image/stb_image.cpp
        shader.h
        main.cpp)

target_link_libraries(
        CameraSystem
        glfw
)


################
#Windows
################

#cmake_minimum_required(VERSION 3.24)
#project(Transform)
#
#set(CMAKE_CXX_STANDARD 11)
#
#include_directories(includes/glad/include)
#include_directories(D:/Studys_Files/CPP_Studys/CPP_Environment/GLFW/glfw-3.3.8/include)
#include_directories(includes/GLM)
#
#link_directories(D:/Studys_Files/CPP_Studys/CPP_Environment/GLFW/glfw-3.3.8/lib-mingw-w64)
#
#add_executable(Transform
#        includes/glad/src/glad.c
#        includes/stb_image/stb_image.cpp
#        shader.h
#        main.cpp)
#
#target_link_libraries(
#        Transform
#        libglfw3.a
#)