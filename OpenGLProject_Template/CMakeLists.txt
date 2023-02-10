cmake_minimum_required(VERSION 3.21)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 11)

include_directories(./glad/include)
include_directories(/opt/homebrew/Cellar/glfw/3.3.8/include)

link_directories(/opt/homebrew/Cellar/glfw/3.3.8/lib)

add_executable(LearnOpenGL
        ./glad/src/glad.c
        main.cpp)

target_link_libraries(
        LearnOpenGL
        glfw
)