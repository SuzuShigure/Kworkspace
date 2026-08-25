#include <iostream>
#include <string>
#include <vector>
#include <memory>

#ifdef _WIN32
#include <windows.h>
#endif

namespace {

void configure_console_encoding() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
}

} // namespace

// ================================================================
// 第一部分：语法糖 (Syntactic Sugar) —— 甜甜的快捷键
// 知识点：编译器帮你负重前行，让你岁月静好。不增加新功能，只为了让人写着爽、看着清。
// 设计意图：降低敲击键盘的疲劳，提高代码“信噪比”，让人类一眼看懂业务意图。
// ================================================================
struct Weapon {
    std::string name;
    int damage;
    void attack() const {
        std::cout << "挥舞 [" << name << "] 造成 " << damage << " 点伤害！\n";
    }
};

void showSugar() {
    std::cout << "========== 语法糖演示 ==========\n";
    std::vector<Weapon> inventory = { {"铁剑", 10}, {"钢斧", 25} };

    // 【无糖原味】：繁琐、充满底层细节，人类阅读时需要过滤掉大量无用信息
    std::cout << "【无糖遍历】:\n";
    for (std::vector<Weapon>::const_iterator it = inventory.begin(); it != inventory.end(); ++it) {
        // (*it).name 这种写法就是极其原始的解引用
        std::cout << "武器: " << (*it).name << "\n";
    }

    // 【加糖版】：极简！auto 自动推导类型，范围 for 隐藏了迭代器，-> 隐藏了解引用
    std::cout << "\n【加糖遍历】:\n";
    for (const auto& w : inventory) {
        w.attack(); // 这里的 w.attack() 看着清爽，底层和上面其实一模一样
    }
}

// ================================================================
// 第二部分：语法盐 (Syntactic Salt) —— 咸苦的防呆设计
// 知识点：语言故意设计得“难写”、“啰嗦”，强迫程序员跨过人为设置的门槛。
// 设计意图：防止手滑、防止隐式转换带来的幽灵 Bug。强迫你“显式表达意图”，证明你知道自己在干嘛。
// ================================================================

// 案例 1：老式枚举（没有盐） vs 强类型枚举（加了盐）
// 老式枚举就是个透明塑料袋，里面的值会泄漏到全局，还能随便当整数做算术运算。
enum OldState { ALIVE, DEAD };

// C++11 引入的 enum class 就是典型的语法盐！
// 你必须带上作用域（GameState::），且绝不允许隐式转换成整数。
enum class GameState { ALIVE, DEAD };

class Player {
private:
    std::string name;
    int id;

public:
    // 案例 2：explicit 关键字 —— 最经典的语法盐！
    // 如果不加 explicit，C++ 允许通过一个 int 隐式构建 Player 对象。
    // 加了 explicit，就是告诉编译器：“必须老老实实调用构造函数，不许自作聪明！”
    explicit Player(int playerId) : name("未知玩家"), id(playerId) {}

    void print() const {
        std::cout << "玩家 ID: " << id << "\n";
    }
};

// 模拟一个按 ID 查找玩家的业务函数
void checkPlayer(const Player& p) {
    p.print();
}

void showSalt() {
    std::cout << "\n========== 语法盐演示 ==========\n";

    // 1. 枚举的语法盐
    OldState s1 = ALIVE;
    int test = s1 + 100; // 离谱：老式枚举居然能和数字相加，编译器不阻拦！

    GameState s2 = GameState::ALIVE;
    // int test2 = s2 + 100; // 解开注释直接报错！语法盐起作用了，类型不匹配！
    // 强制要求你这么写（强转）：int test2 = static_cast<int>(s2) + 100;

    // 2. explicit 构造函数的语法盐
    // 假设团队里的新手手滑写了下面这行代码：
    // checkPlayer(999);

    // 【如果没有 explicit（没加盐）】：
    // 编译器会偷偷把 999 变成 Player(999)，然后传进去。
    // 这会导致莫名其妙创建了一个临时对象，出现极其隐蔽的性能和逻辑 Bug。

    // 【因为加了 explicit（加了盐）】：
    // 上面那行 checkPlayer(999) 编译直接报错！
    // 语法盐强迫新手必须显式、清晰地写出意图：
    checkPlayer(Player(999));
    std::cout << "通过语法盐的校验，安全执行完毕。\n";
}

int main() {
    configure_console_encoding();

    showSugar();
    showSalt();

    /*
     * ========== 核心知识点总结（写在代码里方便复习） ==========
     * 1. 语法糖 (Sugar)：
     *    - 目的：提高开发效率，提升代码可读性。
     *    - 哲学：编译器多干活，程序员少打字（例：auto, 范围 for）。
     *    - 风险：滥用会导致“魔法”太多，掩盖底层真实的性能开销（比如隐藏了深拷贝）。
     *
     * 2. 语法盐 (Salt)：
     *    - 目的：降低犯错概率，提升代码安全性与健壮性。
     *    - 哲学：故意让你难受，逼你三思而后行（例：explicit, enum class, static_cast）。
     *    - 风险：代码写起来比较啰嗦（Boilerplate），稍微降低了初期的开发速度。
     *
     * 【团队架构规范】：
     * “用糖来表达业务逻辑，用盐来保护核心架构。”
     * 外包交付的代码，必须在数据转换和内存操作上撒满“语法盐”，确保交接时不出妖蛾子。
     */
    return 0;
}
