cmake_minimum_required(VERSION 3.16)
project(MagicBoxWM)

#set(CMAKE_CXX_STANDARD 17)

add_executable(MagicBoxWM
        src/main.cpp src/MBApp.cpp src/MBApp.h)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

find_library(
        WAYLAND_CLIENT
        NAMES wayland-client
        HINTS /usr/include
        REQUIRED
)

target_link_libraries(${PROJECT_NAME} ${WAYLAND_CLIENT})
