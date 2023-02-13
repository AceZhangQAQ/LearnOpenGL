################
# MacOs
################

cmake_minimum_required(VERSION 3.21)
project(Texture)

set(CMAKE_CXX_STANDARD 11)

include_directories(includes/glad/include)
include_directories(/opt/homebrew/Cellar/glfw/3.3.8/include)
include_directories(includes/GLM)

link_directories(/opt/homebrew/Cellar/glfw/3.3.8/lib)

add_executable(Texture
        includes/glad/src/glad.c
        includes/stb_image/stb_image.cpp
        shader.h
        main.cpp)

target_link_libraries(
        Texture
        glfw
)


################
#Windows
################

#cmake_minimum_required(VERSION 3.24)
#project(Texture)
#
#set(CMAKE_CXX_STANDARD 11)
#
#include_directories(D:/Studys_Files/CPP_Studys/CPP_Environment/glad/include)
#include_directories(D:/Studys_Files/CPP_Studys/CPP_Environment/GLFW/glfw-3.3.8/include)
#
#link_directories(D:/Studys_Files/CPP_Studys/CPP_Environment/GLFW/glfw-3.3.8/lib-mingw-w64)
#
#add_executable(Texture
#        ./glad/src/glad.c
#        stb_image.cpp
#        shader.h
#        main.cpp)
#
#target_link_libraries(
#        Texture
#        libglfw3.a
#)