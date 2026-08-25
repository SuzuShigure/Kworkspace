# struct 与 class：封装边界对比

这个案例对比 `struct` 的公开数据和 `class` 的访问控制、不变性维护。

## Windows 中文乱码

源码使用 UTF-8，CMake 在 MSVC 下通过 `/utf-8` 固定源文件和执行字符集；程序启动时还会调用 `SetConsoleOutputCP(CP_UTF8)`，让 Windows 控制台按 UTF-8 解码输出。

如果仍然乱码，先在运行程序的终端执行：

```powershell
chcp 65001
```

然后重新构建，确保运行的是刚生成的 `struct_vs_class.exe`，而不是旧的 `main.exe`。

```bash
cmake -S . -B build
cmake --build build
```
