# C++ 语法糖与语法盐

这是一个独立的 C++20 示例，使用 CMake 构建，不依赖特定编辑器。

```bash
cmake -S . -B build
cmake --build build
```

生成目标名为 `syntactic_sugar`。Windows 下可运行 `build/Debug/syntactic_sugar.exe`，或直接使用项目配置好的 MinGW 编译器：

```powershell
g++ -std=c++20 -Wall -Wextra -Wpedantic `
    -finput-charset=UTF-8 -fexec-charset=UTF-8 `
    .\main.cpp -o .\syntactic_sugar.exe
```

程序在 Windows 上会设置 UTF-8 控制台代码页，避免中文输出乱码。
