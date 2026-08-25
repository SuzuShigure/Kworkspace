cmake_minimum_required(VERSION 3.20)
project(REPLACE_ME LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PROJECT_SOURCES main.cpp)
if (IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src")
    file(GLOB_RECURSE PROJECT_SRC_FILES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxx"
    )
    list(APPEND PROJECT_SOURCES ${PROJECT_SRC_FILES})
endif()

add_executable(REPLACE_ME ${PROJECT_SOURCES})

if (IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include")
    target_include_directories(REPLACE_ME PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
endif()

if (MSVC)
    target_compile_options(REPLACE_ME PRIVATE /W4 /permissive- /utf-8)
elseif (MINGW)
    target_compile_options(REPLACE_ME PRIVATE -Wall -Wextra -Wpedantic
        -finput-charset=UTF-8 -fexec-charset=UTF-8)
else()
    target_compile_options(REPLACE_ME PRIVATE -Wall -Wextra -Wpedantic)
endif()
