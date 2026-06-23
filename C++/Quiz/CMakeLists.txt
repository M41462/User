cmake_minimum_required(VERSION 3.14)
project(Quiz VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(raylib CONFIG REQUIRED)

file(GLOB SOURCES Include/*.cpp)

add_executable(Quiz ${SOURCES})

target_include_directories(Quiz PRIVATE Include)
target_link_libraries(Quiz PRIVATE raylib)
