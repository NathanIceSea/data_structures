# C++ 数据结构 - 邓俊辉

## 使用教材

[数据结构(C++语言版)第三版](resource/数据结构(C++语言版)第三版_完整书签_邓俊辉.pdf)

[数据结构(C++语言版)第三版 习题解析](resource/数据结构(C++语言版)第三版_数据结构习题解析_邓俊辉.pdf)

## 练习用 IDE

VSCode + Makefile 跨平台编译

使用 VSCode 打开项目文件夹

### VSCode 配置文件

tasks.json 中已经配置 Make C Project 和 Make C++ Project，支持从打开文件所在目录编译所有 .c[pp] 和 .h 文件并链接生成到 build 目录

launch.json 已经配置 C/C++ Project Launch 通过 F5 调试调用 tasks 编译项目然后运行 build 下的文件进行调试

**调试前务必在 Debug 菜单选择 C++**

## 项目组织

### 命名规范

[C++谷歌命名规范](https://www.jianshu.com/p/f56383486520)

### src 目录树

目录命名遵循 Google C++ 命名规范

按照**章节目录 - 小章节/数据结构/算法实现**的形式组织单元结构

书本案例的实现使用 `_book_impl` 目录后缀

个人特例实现使用 `_xxx_impl` 目录后缀

譬如考虑如下目录结构：
* src/
    * ch1_intro
    * ch2_vector
        * ch2_1_vector_book_impl
        * ch2_1_myvec_icesea_impl
        * ch2_7_myvec_sort_icesea_impl

### 命名空间