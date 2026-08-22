# C++ Workspace

这是一个面向长期 C++ 开发的 VS Code 工作区。它借鉴 Tsoding 的管理方式：项目保持小而独立，构建入口和说明跟着项目走，根目录只负责打开方式、编辑器默认值和目录约定。

## 打开方式

直接打开 [vault.code-workspace](./vault.code-workspace)。工作区会分别显示临时实验、学习项目、可复用库、正式项目和项目模板；每个实际项目都可以随时单独初始化 Git、单独发布或迁移到其他位置。

## 目录约定

```text
Kworkspace/
├── vault.code-workspace       # VS Code 多根工作区入口
├── .vscode/                   # 直接打开根目录时也可用的 VS Code 默认配置
├── cpp/
│   ├── 00_scratch/            # 一次性实验，可以随时删除
│   ├── 10_learning/           # 有明确主题的学习项目
│   ├── 20_libraries/          # 可复制、可复用的单文件/小型库
│   ├── 30_projects/           # 需要长期维护的正式项目
│   └── _template/             # 新建项目的起点
└── docs/                      # VitePress 开发记录（可选）
```

## 管理原则

1. 一个目录解决一个问题；目录名用稳定、可搜索的英文名，细节写在同目录 `README.md`。
2. 练习不共享根级 CMake。每个项目自己选择 CMake、Ninja、Make 或项目内置构建程序。
3. 可复用代码优先保持单文件或少文件，复制到其他项目即可使用；抽象出库之前先证明复用场景。
4. 项目变得重要时，在项目目录内独立建仓库，而不是把整个工作区变成一个 monorepo。
5. 构建产物一律放在项目自己的 `build/` 或 `out/`，不提交到 Git。

## 新建项目

```powershell
Copy-Item -Recurse cpp/_template cpp/10_learning/002_my_topic
code cpp/10_learning/002_my_topic
```

复制后修改 `README.md`、`CMakeLists.txt` 和项目名。项目只要能独立打开、构建、运行，就符合工作区约定。

## 文档（可选）

开发记录集中在 [docs/](./docs/) 并由 VitePress 组织：

```powershell
cd docs
npm install
npm run docs:dev
```

文档记录“为什么这样做”和可复现命令；代码的唯一事实来源仍然是项目目录本身。

## 旧工作区

`MyWrokSpace-main/` 是旧 Ubuntu 工作区的原始参考，保留原样，不参与新工作区构建。确认某个旧项目值得继续维护后，再把它作为一个完整项目迁移到 `cpp/30_projects/`；不要把旧工作区的环境脚本、缓存和第三方大文件整体复制过来。

`Tsoding/` 同样只是本地参考资料。它体现的重点是“小项目自带构建和文档、可复用代码保持轻量”，而不是把所有代码收进一个总工程。

GitHub 仓库中的 `Tsoding/sources/` 是三个仓库的源码副本（不含 `.git` 元数据）；本地可更新的副本继续留在 `Tsoding/20260822Clone/`，不会重复提交。
