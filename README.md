# C++ Workspace

一个学习 C++ 的工作区。

## 打开方式

打开 [vault.code-workspace](./vault.code-workspace)。工作区会分别显示临时实验、学习项目、可复用库、正式项目和项目模板；每个实际项目都可以随时单独初始化 Git、单独发布或迁移到其他位置。

## 目录约定

```text
Kworkspace/
├── vault.code-workspace       # VS Code 多根工作区入口
├── .vscode/                   # VS Code 默认配置
├── cpp/
│   ├── 00_scratch/            # 实验
│   ├── 10_learning/           # 学习项目
│   ├── 20_libraries/          # 单文件/小型库
│   ├── 30_projects/           # 长期项目
│   └── _template/             # 新建项目
└── KerveinWiki/               # 独立 VitePress Wiki（单独仓库）
```

## 新建项目

```powershell
Copy-Item -Recurse cpp/_template cpp/10_learning/002_my_topic
code cpp/10_learning/002_my_topic
```

## 文档

Wiki 已拆分为独立仓库：[KerveinWiki](https://github.com/SuzuShigure/KerveinWiki)。

本地开发：

```powershell
cd KerveinWiki
npm ci
npm run docs:dev
```

Vercel 构建配置已写入 `KerveinWiki/vercel.json`，可直接使用 `wiki.veic.tech` 部署。


