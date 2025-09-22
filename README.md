# SorenShell

一个简易的Shell程序，因为没有写入内核，且不希望直接使用系统调用对应指令，所以无法实现类似`sudo`的命令，
本项目并不是一个完备的终端程序，而是更多展示框架，保留更多的可扩展性。  
由于我们做的不是操作系统的内核Shell，所以做不到在不使用`system`函数的情况下，执行一个可执行文件或者根据`PATH`环境变量搜索可执行文件后执行，所以和实际的内核Shell有所差别，但是依然可以用于理解Shell的运行原理。

## 项目结构

```
SorenShell/
├── CMakeLists.txt               # 项目构建配置文件
├── main.cpp                     # 程序入口文件
├── .gitignore                   # Git忽略文件配置
├── include/                     # 公共头文件目录
│   ├── Base.hpp                 # 基础定义头文件
│   └── Terminal.hpp             # 终端类头文件
├── src/                         # 源文件目录
│   └── Terminal.cpp             # 终端类实现文件
├── User/                        # 用户管理模块
│   ├── include/
│   │   └── User.hpp             # 用户类头文件
│   └── src/
│       └── User.cpp             # 用户类实现文件
├── Hardware/                    # 硬件管理模块
│   ├── include/
│   │   └── HardwareManager.hpp  # 硬件管理类头文件
│   └── src/
│       └── HardwareManager.cpp  # 硬件管理类实现文件
└── commands/                    # 命令模块
    ├── include/
    │   ├── CdCommand.hpp        # cd命令头文件
    │   ├── Command.hpp          # 命令基类头文件
    │   ├── CommandFactory.hpp   # 命令工厂类头文件
    │   ├── EchoCommand.hpp      # echo命令头文件
    │   ├── ExitCommand.hpp      # exit命令头文件
    │   ├── LsCommand.hpp        # ls命令头文件
    │   └── WhoamiCommand.hpp    # whoami命令头文件
    └── src/
        ├── CdCommand.cpp        # cd命令实现文件
        ├── Command.cpp          # 命令基类实现文件
        ├── CommandFactory.cpp   # 命令工厂类实现文件
        ├── EchoCommand.cpp      # echo命令实现文件
        └── ... (其他命令实现文件)
```

## 体验方法

直接使用`git clone`当前仓库后使用`cmake`编译执行即可

## 更新计划

暂无，已经完成了基本框架，剩下的只要定义`Command`的派生类并登记，就可以实现扩展。
