cmake_minimum_required(VERSION 3.22)
project(MagicBox C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(src)
include_directories(/usr/include/pixman-1)

add_compile_options("-DWLR_USE_UNSTABLE")

add_executable(MagicBox
        src/main.c
        src/server.c
        src/server.h)

target_link_libraries(MagicBox
        wayland-server
        wlroots
        )