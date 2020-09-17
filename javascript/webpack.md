# webpack 笔记

## 概念

* entry（入口）
  
> 表明webpack应当从哪个文件开始处理模块

``` javascript
entry: {
    app: './src/app.js'
},
```

* output（输出）
  > 表示模块处理完成后，应当输出的目录

``` javascript
// 指定应用的输出目录
output: {
    path: path.resolve(__dirname, 'dist'),
    filename: '[name].bundle.js',
    publicPath: '/',
},
```

* loaders（加载器）

> loaders 处理非 JavaScript 文件，可以将所有类型的文件转换为 webpack 能够处理的有效模块

``` javascript
rules: [
    //“嘿，webpack 编译器，当你碰到「在 require()/import 语句中被解析为 '.css' 的路径」时，在你对它打包之前，先使用 css-loader 转换一下。”
    {
        test: /\.css$/,
        use: [
            'style-loader',
            'css-loader',
        ]
    }
]
```

* plugin（插件）

> loader 被用于转换某些类型的模块，而插件则可以用于执行范围更广的任务。插件的范围包括，从打包优化和压缩，一直到重新定义环境中的变量。插件接口功能极其强大，可以用来处理各种各样的任务

``` javascript

const HtmlWebpackPlugin = require('html-webpack-plugin');
const { CleanWebpackPlugin } = require('clean-webpack-plugin');

plugins: [
    // 构建前情路输出目录
    new CleanWebpackPlugin(),
    // 在输出目录自动生成html文件
    new HtmlWebpackPlugin({
        title: 'Production',
    }),
]
```


## `webpack.config.js` 示例

``` javascript
const path = require('path');
const HtmlWebpackPlugin = require('html-webpack-plugin');
const { CleanWebpackPlugin } = require('clean-webpack-plugin');


const config = {
    // 指定应用的入口文件，会根据入口文件的依赖引用来处理打包
    entry: {
        app: './src/app.js'
    },
    // 指定应用的输出目录
    output: {
        path: path.resolve(__dirname, 'dist'),
        filename: '[name].bundle.js',
        publicPath: '/',
    },
    // 开发环境可配置
    mode: 'development',
    devtool: 'inlin-source-map',
    // 热重载相关
    devServer: {
        contentBase: './dist',
    },
    module: {
        // loaders 处理非 JavaScript 文件，可以将所有类型的文件转换为 webpack 能够处理的有效模块
        rules: [
            //“嘿，webpack 编译器，当你碰到「在 require()/import 语句中被解析为 '.css' 的路径」时，在你对它打包之前，先使用 css-loader 转换一下。”
            {
                test: /\.css$/,
                use: [
                    'style-loader',
                    'css-loader',
                ]
            }
        ]
    },
    plugins: [
        // 构建前情路输出目录
        new CleanWebpackPlugin(),
        // 在输出目录自动生成html文件
        new HtmlWebpackPlugin({
            title: 'Production',
        }),
    ]
};

module.exports = config;

```
> 对应的 `package.json`
``` javascript
"scripts": {
    "start": "webpack-dev-server --open --config webpack.config.js",
    "build": "webpack --config webpack.config.js"
},
```

## TypeScript 支持

1. 配置 loader

``` javascript
{ 
    test: /\.tsx?$/,
    use: 'ts-loader',
    exclude: /node_modules/,
},
```

2. 配置 resolve

``` javascript
resolve: {
    extensions: [ '.tsx', '.ts', '.js' ],
},

```

3. 配置tsconfig.json

``` json
{
    "compilerOptions": {
      "outDir": "./dist/",
     "sourceMap": true,
      "noImplicitAny": true,
      "module": "commonjs",
      "target": "es5",
      "jsx": "react",
      "allowJs": true
    }
  }

```

# Ref

* [webpack Guide](https://webpack.js.org/guides/)