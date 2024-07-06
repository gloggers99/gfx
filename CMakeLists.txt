cmake_minimum_required(VERSION 3.2)
project(gfx VERSION 1.0 DESCRIPTION "C++ OpenGL Renderer Framework")

set(CMAKE_CXX_STANDARD 17)

file(GLOB SRC_FILES ./src/*.cpp)
file(GLOB SRC_VO_FILES ./src/vo/*.cpp)


IF (WIN32)
    add_executable(gfx_test ${SRC_FILES} ${SRC_VO_FILES} main.cpp)
    add_library(gfx STATIC ${SRC_FILES} ${SRC_VO_FILES})
    target_include_directories(gfx PUBLIC include)
    target_link_directories(gfx PUBLIC lib)
    target_link_libraries(gfx glfw3)
    target_link_libraries(gfx -static)
ELSE()
    file(GLOB IMGUI_FILES ./include/imgui/*.cpp)
    #file(GLOB IMGUI_BACKEND_FILES ./include/imgui/backends/*.cpp)

    add_library(gfx SHARED 
        ${SRC_FILES} 
        ${SRC_VO_FILES} 
        ${IMGUI_FILES} 
        include/imgui/backends/imgui_impl_glfw.cpp 
        include/imgui/backends/imgui_impl_opengl3.cpp)

    add_executable(gfx_test
        ${SRC_FILES} 
        ${SRC_VO_FILES} 
        ${IMGUI_FILES} 
        include/imgui/backends/imgui_impl_glfw.cpp 
        include/imgui/backends/imgui_impl_opengl3.cpp
        main.cpp)

    target_link_libraries(gfx glfw)
    target_link_libraries(gfx_test glfw)
    target_include_directories(gfx PUBLIC include)
    target_include_directories(gfx_test PUBLIC include)
    target_include_directories(gfx PUBLIC include/imgui)
    target_include_directories(gfx_test PUBLIC include/imgui)
    target_compile_options(gfx PRIVATE -Wall -Wextra)

    install(TARGETS gfx
        LIBRARY DESTINATION /usr/lib
        PUBLIC_HEADER DESTINATION /usr/include)

    # setup install command
    file(GLOB GLAD_HEADERS include/glad/*.h)
    install(FILES ${GLAD_HEADERS} DESTINATION /usr/include/glad)

    file(GLOB MAIN_HEADERS src/*.hpp)
    install(FILES ${MAIN_HEADERS} DESTINATION /usr/include/gfx)
    file(GLOB VO_HEADERS src/vo/*.hpp)
    install(FILES ${VO_HEADERS} DESTINATION /usr/include/gfx/vo)

    configure_file(gfx.pc.in gfx.pc @ONLY)
    install(FILES ${CMAKE_BINARY_DIR}/gfx.pc DESTINATION /usr/local/lib/pkgconfig)
ENDIF()


