# C++ 封装：从访问控制到实现隐藏

这个案例把“封装”拆成三个可以观察、可以验证的层次：

1. `PublicSnapshot` 是透明的数据包。成员公开，调用方可以把 `value` 改成任意值，适合没有业务规则的数据。
2. `BankAccount` 是普通 `class`。数据成员在头文件中可见，但属于 `private`；余额只能通过存取款接口改变，类负责保证“余额非负、金额为正、不会溢出”等不变性。
3. `Player` 使用 Pimpl（pointer to implementation）。头文件只有接口和 `std::unique_ptr<Impl>`，姓名、血量和算法都在 `src/encapsulation.cpp` 中，演示物理实现隐藏以及更稳定的编译/ABI边界。

## 文件关系

```text
main.cpp                    # 使用方：只 include 头文件
include/encapsulation.h     # 对外契约：类型、函数签名、可见行为
src/encapsulation.cpp       # 实现方：数据、校验规则、算法
```

```bash
cmake -S . -B build
cmake --build build
./build/class_encapsulation   # Windows 可运行 build/Debug/class_encapsulation.exe
```

## Windows 中文乱码

源码采用 UTF-8；CMake 在 MSVC 下使用 `/utf-8`，在 MinGW 下使用 UTF-8 输入/执行字符集选项，程序启动时还会设置 Windows 控制台输出代码页为 UTF-8。若仍显示乱码，先在运行程序的终端执行 `chcp 65001`，然后重新构建并运行最新的 `class_encapsulation.exe`。

## CLion 编译与调试

请打开包含本项目 `CMakeLists.txt` 的 `Class_Encapsulation` 目录，不要把 `main.cpp` 单独作为临时项目运行。右上角运行配置应选择 CMake 目标 `class_encapsulation`；如果当前显示的是 `main` 或 `Current File`，请在 **Run | Edit Configurations...** 中新建 **CMake Application**，将 Target 设为 `class_encapsulation`，Executable 使用 `cmake-build-debug/class_encapsulation.exe`，Working directory 使用项目根目录。

之后使用锤子图标构建，使用绿色三角运行，使用小虫图标进入调试。CMake Application 会同时编译 `main.cpp` 和 `src/encapsulation.cpp`，并自动加入 `include` 头文件目录。

如果直接使用 GCC 编译，必须同时传入头文件搜索目录和实现文件：

```powershell
Set-Location F:\workspace\Kworkspace\cpp\10_learning\002_class_encapsulation
g++ -std=c++20 -Wall -Wextra -Wpedantic -finput-charset=UTF-8 -fexec-charset=UTF-8 -I.\include .\main.cpp .\src\encapsulation.cpp -o .\main.exe
.\main.exe
```

如果当前目录不是项目根目录，请把 `-I.\include`、`.\main.cpp` 和 `.\src\encapsulation.cpp` 改成对应的绝对路径。只编译 `main.cpp` 会找不到 `include/encapsulation.h`；即使加上头文件目录，也会因为没有链接 `src/encapsulation.cpp` 而出现 `undefined reference` 链接错误。

## 读代码时要问的三个问题

- **谁能改状态？** `private` 成员不能被外部直接写入；外部必须调用有业务含义的成员函数。
- **规则放在哪里？** 规则和状态放在同一个类中，构造函数建立初始不变性，成员函数在每次变化后继续维护它。
- **实现改动影响谁？** `BankAccount` 展示逻辑封装；`Player` 的 Pimpl 进一步把布局和实现移出头文件。只改 `.cpp` 中的字段或算法时，使用方源文件无需重新编译（重新链接仍是构建流程的一部分），仍依赖同一份接口。

因此，封装不是简单地“把变量标成 private”，而是让类型对自己的状态负责，并用最小、稳定的接口控制变化。
