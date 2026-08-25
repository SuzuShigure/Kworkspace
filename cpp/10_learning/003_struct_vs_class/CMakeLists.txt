cmake_minimum_required(VERSION 3.20)
project(StructVsClass LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(struct_vs_class main.cpp)

if (MSVC)
    # 明确指定源文件和执行字符集，避免中文窄字符串被本地代码页转换。
    target_compile_options(struct_vs_class PRIVATE /W4 /permissive- /utf-8)
elseif (MINGW)
    target_compile_options(struct_vs_class PRIVATE -Wall -Wextra -Wpedantic
        -finput-charset=UTF-8 -fexec-charset=UTF-8)
else()
    target_compile_options(struct_vs_class PRIVATE -Wall -Wextra -Wpedantic)
endif()
