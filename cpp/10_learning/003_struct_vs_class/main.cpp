#include <iostream>
#include <string>
#include <type_traits> // 现代 C++ 用于在编译期洞察类型本质的库

#ifdef _WIN32
#include <windows.h>
#endif

namespace {

void configure_console_encoding() {
#ifdef _WIN32
    // 源文件和窄字符串字面量统一使用 UTF-8；让 Windows 控制台也按 UTF-8 解码。
    // 在输出被重定向到文件/管道时，SetConsoleOutputCP 会失败，但不会影响程序继续运行。
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
}

} // namespace

// ================================================================
// 第一部分：struct —— 就是个透明塑料袋（容器本质）
// 知识点：在 C++ 里，struct 默认权限是 public。
// “我这里面没秘密，随便看随便改”。
// 虽然 C++ 允许我里面放函数，但那纯粹是为了调用方便，管不住外部代码的手。
//
// 【现代 C++ 架构视角补充】：
// 现代 C++ 规范（如 C++ Core Guidelines）严格规定：
// 当数据成员可以独立变化，没有“逻辑不变性（Invariant）”时，使用 struct。
// 这被称为“聚合类型（Aggregate Type）”。编译器对它的内存布局和拷贝优化是极致的。
// ================================================================
struct Player {
    std::string name;
    int hp;
    int attack;

    // 附带个工具函数，省得外部每次都要写打印循环，图个省事
    // 但注意：这个函数管不了外部直接把 hp 改成 -9999
    void showStatus() const {
        std::cout << "[" << name << "] HP: " << hp << " ATK: " << attack << std::endl;
    }
};

// ================================================================
// 第二部分：class —— 带门禁的黑匣子（蓝图/自治容器）
// 知识点：class 默认权限是 private。
// 设计意图：数据是我的命根子，外部想改？得按我的规矩来（走成员函数）。
// 这里封装的不只是数据，还有“业务规则”（比如血量不能为负，等级不能乱跳）。
//
// 【现代 C++ 架构视角补充】：
// 在 OOP 中不再用 struct 写类的原因在于“语义契约”。
// class 向其他程序员和编译器宣告：“我拥有不变性（Invariant）和资源所有权”。
// 一旦使用了 private，它就不再是聚合类型，不能随意内存拷贝，通常伴随 RAII 机制。
// ================================================================
class Monster {
private:
    std::string type;
    int hp;
    int level;

    // 内部私有的校验逻辑，外部根本不知道有这个函数存在
    // 这就是“隐藏实现细节”
    int calcMaxHpByLevel(int lv) const {
        return 500 + lv * 100;
    }

public:
    // 构造函数：初始化时就把规矩立好
    // 现代 C++ 提倡使用 explicit 防止隐式类型转换带来的诡异 Bug
    explicit Monster(const std::string& t, int lv) : type(t), level(lv) {
        hp = calcMaxHpByLevel(lv);
    }

    // 对外接口：受到攻击
    // 这里面有业务逻辑：扣血不能扣成负数，死了就是死了，不能回档
    void takeDamage(int damage) {
        if (damage <= 0) {
            std::cout << "攻击无效，别想卡 Bug\n";
            return;
        }

        hp -= damage;
        if (hp < 0) hp = 0; // 强制归零，血条不能是负的，这是业务规则
        std::cout << type << " 受到 " << damage << " 点伤害，剩余 HP: " << hp << "\n";
    }

    // 只读接口：只能看，不能改
    int getHp() const { return hp; }

    // 升级接口：等级不能乱改，必须经过我这里的阈值校验
    void levelUp() {
        level += 1;
        // 升级回血是游戏规则，封装在这个函数里，外部不需要知道怎么算的
        hp = calcMaxHpByLevel(level);
        std::cout << type << " 升级啦！当前等级 " << level << "，满血复活！\n";
    }
};

int main() {
    configure_console_encoding();

    std::cout << "========== struct 容器与现代 C++ 初始化演示 ==========\n";
    // 现代 C++20 特性：指定初始化器 (Designated Initializers)
    // 只有纯粹的 struct（聚合类型）才能享受这种极具可读性的初始化语法！
    // 如果你在 struct 里加了 private，这种优雅的写法直接报错。
    Player p1{ .name = "勇者", .hp = 100, .attack = 15 };
    p1.showStatus();

    // 容器：外部代码想怎么改就怎么改。
    // 结构体本身不承担任何管理责任，它就是一堆数据的集合。
    // 哪怕把血量改成负数，编译器都不带吭声的，因为它是 public 的。
    std::cout << "\n外部代码强行修改数据（没有拦阻）：\n";
    p1.hp = -999;
    p1.attack = 9999;
    p1.showStatus();

    std::cout << "\n========== class 封装与业务不变性演示 ==========\n";
    Monster boss("远古巨龙", 5);

    // 编译期物理屏障：boss.hp = 1; // 解开注释直接编译失败

    std::cout << "初始血量(通过接口获取): " << boss.getHp() << "\n";
    boss.takeDamage(300);
    boss.levelUp();
    boss.takeDamage(2000);

    std::cout << "\n========== 现代 C++ 编译器视角（Type Traits） ==========\n";
    // 编译器会通过 Type Traits 区分它们，从而决定底层优化策略：
    std::cout << "Player 是聚合类型吗？(可安全 memcpy?): "
              << (std::is_aggregate_v<Player> ? "Yes" : "No") << "\n";

    std::cout << "Monster 是聚合类型吗？(包含业务逻辑，禁止暴力拷贝): "
              << (std::is_aggregate_v<Monster> ? "Yes" : "No") << "\n";

    /*
     * ========== 核心知识点总结（写在代码里方便复习） ==========
     * 1. 语法本质：struct 和 class 在 C++ 底层没区别，唯一不同是默认访问权限。
     *    - struct 默认 public  -> 体现“容器”意图，透明。
     *    - class 默认 private -> 体现“蓝图”意图，强制封装。
     *
     * 2. 设计意图（比语法更重要）：
     *    - 如果你的类型只是把几个变量捆在一起（比如坐标、配置参数），用 struct。
     *    - 如果你的类型需要维护某种“逻辑正确性”（比如银行账户不能透支，怪物升级必须回血），用 class。
     *
     * 3. 封装的实质：
     *    不是“把函数放在结构体里”就叫封装。
     *    真正的封装是“把数据藏起来，并通过有限的接口暴露行为”，让对象自己负责自己的状态。
     */
    return 0;
}
