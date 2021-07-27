cmake_minimum_required(VERSION 3.16)
project(MagicBoxWM)

#set(CMAKE_CXX_STANDARD 17)

add_executable(MagicBoxWM
        src/main.cpp src/MBWindow.cpp src/MBWindow.h src/MBApp.cpp src/MBApp.h)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

find_library(
        XCB
        NAMES xcb
        HINTS /usr/include/xcb
        REQUIRED
)
target_link_libraries(${PROJECT_NAME} ${XCB})
