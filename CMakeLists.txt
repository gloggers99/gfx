cmake_minimum_required(VERSION 3.5)
project(gfx VERSION 1.0 DESCRIPTION "C++ OpenGL Renderer Framework")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include)
include_directories(include/imgui)
add_library(gfx SHARED
    # glad stuff
    include/glad/gl.h

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
    src/Model.cpp
    src/VertexStack.cpp
    src/IndicedVertexStack.cpp

    src/vo/VAO.cpp
    src/vo/VBO.cpp
    src/vo/EBO.cpp)
target_link_libraries(gfx glfw)
target_include_directories(gfx PUBLIC include)
target_compile_options(gfx PRIVATE -Wall -Wextra)

install(TARGETS gfx
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# slap glad's header into /usr/local/include/glad
file(GLOB GLAD_HEADERS include/glad/*.h)
install(FILES ${GLAD_HEADERS} DESTINATION /usr/local/include/glad)

file(GLOB MAIN_HEADERS src/*.hpp)
install(FILES ${MAIN_HEADERS} DESTINATION /usr/local/include/gfx)
file(GLOB VO_HEADERS src/vo/*.hpp)
install(FILES ${VO_HEADERS} DESTINATION /usr/local/include/gfx/vo)

configure_file(gfx.pc.in gfx.pc @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/gfx.pc DESTINATION /usr/local/lib/pkgconfig)
