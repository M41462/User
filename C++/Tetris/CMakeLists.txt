cmake_minimum_required(VERSION 3.14)
project(Tetris VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(raylib CONFIG REQUIRED)

file(GLOB SOURCES src/*.cpp)

add_executable(Tetris ${SOURCES})

target_include_directories(Tetris PRIVATE include)
target_link_libraries(Tetris PRIVATE raylib)
