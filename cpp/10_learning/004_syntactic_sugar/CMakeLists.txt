cmake_minimum_required(VERSION 3.20)
project(SyntacticSugar LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(syntactic_sugar main.cpp)

if (MSVC)
    target_compile_options(syntactic_sugar PRIVATE /W4 /permissive- /utf-8)
elseif (MINGW)
    target_compile_options(syntactic_sugar PRIVATE -Wall -Wextra -Wpedantic
        -finput-charset=UTF-8 -fexec-charset=UTF-8)
else()
    target_compile_options(syntactic_sugar PRIVATE -Wall -Wextra -Wpedantic)
endif()
