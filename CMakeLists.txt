cmake_minimum_required(VERSION 3.28)
project(gfx)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SRC_FILES ./src/*.cpp)
file(GLOB SRC_VO_FILES ./src/vo/*.cpp)

add_executable(gfx  ${SRC_FILES} ${SRC_VO_FILES} main.cpp)
target_include_directories(gfx PUBLIC include)
target_link_directories(gfx PUBLIC lib)
target_link_libraries(gfx glfw3)
target_link_libraries(gfx -static)