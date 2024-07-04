cmake_minimum_required(VERSION 3.5)
project(gfx_test)

add_executable(gfx_test
    main.cpp
    )
target_link_libraries(gfx_test gfx)
