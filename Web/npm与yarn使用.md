
* 初始化一个基于node的项目，会创建一个配置文件package.json

`npm init`

* 安装模块（包）：

```
//全局安装
$ npm install 模块名 -g
//本地安装
$ npm install 模块名
//一次性安装多个
$ npm install 模块1 模块2 模块n --save

//安装运行时依赖包
$ npm install 模块名 --save
//安装开发时依赖包
$ npm install 模块名 --save-dev

```

* 卸载模块（包）：
```
//卸载本地模块
$ npm uninstall 模块名

//卸载全局模块
$ npm uninstall -g 模块名

```

* 使用 TypeScript

[手册](https://typescript.bootcss.com/)

- 安装配置 TypeScript

```

yarn init
yarn add typescript
./node_modules/.bin/tsc --init # 获得 tsconfig.json 文件

yarn add webpack babel-core babel-loader babel-preset-es2015 babel-preset-react ts-loader webpack-dev-server

```

- 创建Webpack 配置文件

```

const webpack = require('webpack')
const path = require('path')

module.exports = {
  // 设置 sourcemaps 为 eval 模式，将模块封装到 eval 包裹起来
  devtool: 'eval',

  // 我们应用的入口, 在 `src` 目录 (我们添加到下面的 resolve.modules):
  entry: [
    'index.tsx'
  ],

  // 配置 devServer 的输出目录和 publicPath
  output: {
    filename: 'app.js',
    publicPath: 'dist',
    path: path.resolve('dist')
  },

  // 配置 devServer 
  devServer: {
    port: 3000,
    historyApiFallback: true,
    inline: true,
  },

  // 告诉 Webpack 加载 TypeScript 文件
  resolve: {
    // 首先寻找模块中的 .ts(x) 文件, 然后是 .js 文件
    extensions: ['.ts', '.tsx', '.js'],

    // 在模块中添加 src, 当你导入文件时，可以将 src 作为相关路径
    modules: ['src', 'node_modules'],
  },

  module: {
    loaders: [
      // .ts(x) 文件应该首先经过 Typescript loader 的处理, 然后是 babel 的处理
      { test: /\.tsx?$/, loaders: ['babel-loader', 'ts-loader'], include: path.resolve('src') }
    ]
  },
}

```

- 在 index.tsx 下创建一个组件并渲染

> 注意版本之间的兼容

- 此时通过`./node_modules/.bin/webpack-dev-server`来启动(如果)`webpack-dev-server` 全局安装了，则可以直接启动

- 添加`html-webpack-plugin`处理html入口文件

> [ref](https://segmentfault.com/q/1010000013851451)

快速创建 react 项目 ==> `create-react-app my-app --scripts-version=react-scripts-ts`