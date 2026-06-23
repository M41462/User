cmake_minimum_required(VERSION 3.14)
project(MPlayer VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SFML CONFIG REQUIRED COMPONENTS Graphics Audio Window System)

file(GLOB SOURCES src/main.cpp include/*.cpp)

add_executable(MPlayer ${SOURCES})

target_include_directories(MPlayer PRIVATE include)
target_link_libraries(MPlayer PRIVATE SFML::Graphics SFML::Audio SFML::Window SFML::System)

if(WIN32)
    target_link_libraries(MPlayer PRIVATE comdlg32)
endif()
