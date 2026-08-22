import { defineConfig } from 'vitepress'

export default defineConfig({
  title: 'C++ Workspace',
  description: 'C++ 项目、实验和工程决策记录',
  lang: 'zh-CN',
  cleanUrls: true,
  lastUpdated: true,
  themeConfig: {
    outline: 'deep',
    search: { provider: 'local' },
    nav: [
      { text: '首页', link: '/' },
      { text: '工作区约定', link: '/guide/workspace' },
      { text: '项目模板', link: '/guide/cpp-project' },
      { text: '记录模板', link: '/notes/record-template' },
    ],
    sidebar: {
      '/guide/': [
        {
          text: '使用指南',
          items: [
            { text: '工作区约定', link: '/guide/workspace' },
            { text: '创建 C++ 项目', link: '/guide/cpp-project' },
          ],
        },
      ],
      '/notes/': [
        {
          text: '开发记录',
          items: [{ text: '记录模板', link: '/notes/record-template' }],
        },
      ],
    },
    footer: {
      message: '小项目独立生长，结论持续沉淀。',
      copyright: 'C++ Workspace',
    },
  },
})
