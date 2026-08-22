# C++ 项目模板

复制此目录创建新项目，然后替换项目名和说明。模板刻意保持扁平，项目变复杂后再引入 `src/`、`include/` 和 `tests/`。`.vscode/` 中的调试配置依赖 CMake Tools；若项目改用其他构建方式，应把它替换为项目自己的任务。项目迁移为独立 Git 仓库时，保留这里的 `.gitignore`。

```bash
cmake -S . -B build
cmake --build build
```
