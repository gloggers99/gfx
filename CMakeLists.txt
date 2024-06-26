cmake_minimum_required(VERSION 3.5)
project(gfx)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include)
add_executable(gfx 
    src/Renderer.cpp
    src/Shader.cpp
    src/Camera.cpp

    src/vo/VAO.cpp
    src/vo/VBO.cpp
    src/vo/EBO.cpp

    test/main.cpp)
target_link_libraries(gfx glfw)
