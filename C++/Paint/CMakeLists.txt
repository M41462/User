cmake_minimum_required(VERSION 3.14)
project(Paint VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)

file(GLOB SOURCES Src/*.cpp)

add_executable(Paint ${SOURCES})

target_include_directories(Paint PRIVATE Include)
target_link_libraries(Paint PRIVATE SDL2::SDL2 SDL2_image::SDL2_image)
