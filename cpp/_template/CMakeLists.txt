cmake_minimum_required(VERSION 3.20)
project(REPLACE_ME LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(REPLACE_ME main.cpp)

if (MSVC)
    target_compile_options(REPLACE_ME PRIVATE /W4 /permissive-)
else()
    target_compile_options(REPLACE_ME PRIVATE -Wall -Wextra -Wpedantic)
endif()
