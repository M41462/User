cmake_minimum_required(VERSION 3.14)
project(Game VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(raylib CONFIG REQUIRED)

file(GLOB SOURCES src/*.cpp)

add_executable(Game ${SOURCES})

target_include_directories(Game PRIVATE src)
target_link_libraries(Game PRIVATE raylib)
