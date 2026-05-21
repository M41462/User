cmake_minimum_required(VERSION 3.20)

project(Pacman
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/build")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/build")
set(CMAKE_CXX_EXTENSIONS OFF)
find_package(SFML REQUIRED COMPONENTS Graphics Window System Audio Network)

file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_executable(Pacman ${SOURCES})

target_include_directories(Pacman PRIVATE "${CMAKE_SOURCE_DIR}/include")

target_link_libraries(Pacman PRIVATE sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
