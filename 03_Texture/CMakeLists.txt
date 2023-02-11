cmake_minimum_required(VERSION 3.21)
project(Texture)

set(CMAKE_CXX_STANDARD 11)

include_directories(./glad/include)
include_directories(/opt/homebrew/Cellar/glfw/3.3.8/include)

link_directories(/opt/homebrew/Cellar/glfw/3.3.8/lib)

add_executable(Texture
        ./glad/src/glad.c
        stb_image.cpp
        shader.h
        main.cpp)

target_link_libraries(
        Texture
        glfw
)