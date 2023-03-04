################
# MacOs
################

cmake_minimum_required(VERSION 3.21)
project(ArcBall)

set(CMAKE_CXX_STANDARD 11)

include_directories(includes/glad/include)
include_directories(/opt/homebrew/Cellar/glfw/3.3.8/include)
include_directories(includes/GLM)
include_directories(/opt/homebrew/Cellar/assimp/5.2.5/include)
include_directories(includes/stb_image)

link_directories(/opt/homebrew/Cellar/glfw/3.3.8/lib)
link_directories(/opt/homebrew/Cellar/assimp/5.2.5/lib)

add_executable(ArcBall
        includes/glad/src/glad.c
        includes/stb_image/stb_image.cpp
        utils/Shader.h
        utils/Camera.h
        utils/ArcBall.h
        utils/Mesh.h
        utils/Model.h
        main.cpp)

target_link_libraries(
        ArcBall
        glfw
        Assimp
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