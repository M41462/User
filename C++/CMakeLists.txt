cmake_minimum_required(VERSION 3.14)
project(CPlusPlusProjects LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/bin")

add_subdirectory(Game)
add_subdirectory(MPlayer)
add_subdirectory(Pacman)
add_subdirectory(Paint)
add_subdirectory(PING-PONG)
add_subdirectory(Quiz)
add_subdirectory(Tetris)
