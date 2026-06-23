cmake_minimum_required(VERSION 3.14)
project(PingPong VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)

file(GLOB SOURCES main/main.cpp Include/*.cpp)

add_executable(PingPong ${SOURCES})

target_include_directories(PingPong PRIVATE Include)
target_link_libraries(PingPong PRIVATE SDL2::SDL2 SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf)
