cmake_minimum_required(VERSION 3.5)
project(gfx)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include)
include_directories(include/imgui)
add_executable(gfx 
    # imgui stuff
    include/imgui/imgui.cpp
    include/imgui/imgui_demo.cpp
    include/imgui/imgui_draw.cpp
    include/imgui/imgui_tables.cpp
    include/imgui/imgui_widgets.cpp
    include/imgui/backends/imgui_impl_glfw.cpp
    include/imgui/backends/imgui_impl_opengl3.cpp

    # gfx stuff
    src/Renderer.cpp
    src/Shader.cpp
    src/Camera.cpp
    src/Texture.cpp
    src/ShaderWatcher.cpp

    src/obj/Cube.cpp

    src/vo/VAO.cpp
    src/vo/VBO.cpp
    src/vo/EBO.cpp

    test/main.cpp)
target_link_libraries(gfx glfw)
