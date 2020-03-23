
# C & C++

* ### C++ 哈希表

> 引用 [C++ STL 之哈希表 | unordered_map](https://www.sczyh30.com/posts/C-C/cpp-stl-hashmap/)

## CMake 入门实战

`cmake`的编译分为两个基本步骤:

> 1 cmake
>
> 2 make

> cmake指向`CMakeLists.txt`所在的目录，例如 `cmake ..`表示`CMakeLists.txt`在当前目录的上一级目录，cmake后会产生很多编译的中间文件，以及makefile文件，一般建议新建一个目录用来编译：

```
mkdir build
cd build
cmake ..
make

```

#### 编写CMakeLists.txt

> 依赖CMakeLists.txt文件，项目主目录一个，主目录中可指定包含的子目录；
>
> 在项目CMakeLists.txt中使用project指定项目名称，add_subdirectory添加子目录
> 
> 子目录CMakeLists.txt将从父目录CMakeLists.txt继承设置（TBD，待检验）


* 常用命令

`cmake_minimum_required(VERSION 3.2)` # 指定cmake版本

`project (PROJECT_NAME)` # 指定项目名称 

`include_directories(include)` # 指定目录

`add_subdirectory(SUB_DIR)` # 包含子目录

`add_executable (target src/file)` # 编译可执行程序，指定编译，好像也可以添加.o文件

[链接](https://www.hahack.com/codes/cmake/#)

[Cmake知识](https://blog.csdn.net/hebbely/article/details/79169965)