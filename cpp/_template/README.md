# C++ 项目模板

复制此目录创建一个独立 C++ 项目，然后把 `REPLACE_ME` 替换为项目名。模板以 CMake 和命令行为基准，不依赖特定编辑器；`.vscode/` 只是可选的编辑器辅助配置。

## 推荐目录

```text
project/
├── CMakeLists.txt
├── main.cpp
├── include/       # 可选：对外头文件
└── src/           # 可选：实现文件，C/C++ 文件会自动加入目标
```

## CMake 构建（推荐）

```bash
cmake -S . -B build
cmake --build build
```

运行产物位于 `build/`；Windows 多配置生成器通常位于 `build/Debug/REPLACE_ME.exe`。

使用 CLion、Qt Creator 或其他 CMake-aware IDE 时，打开包含 `CMakeLists.txt` 的项目目录，并选择 CMake 生成的目标；不要使用“运行当前文件”功能代替项目目标。

## 直接使用 GCC/MinGW

只有 `main.cpp` 时：

```bash
g++ -std=c++20 -Wall -Wextra -Wpedantic main.cpp -o main
```

项目包含头文件和 `src/` 实现时，必须同时指定头文件目录并编译所有实现文件，例如：

```bash
g++ -std=c++20 -Wall -Wextra -Wpedantic -Iinclude main.cpp src/*.cpp -o main
```

PowerShell 不展开 `src/*.cpp` 时，请逐个列出实现文件，或直接使用 CMake。
