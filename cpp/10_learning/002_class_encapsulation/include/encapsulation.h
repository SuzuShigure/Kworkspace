#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <string_view>

namespace encapsulation_demo {

// 适合用 struct 的场景：它只是一个公开的数据包，没有需要维护的不变性。
// 调用方可以直接读写成员，也可以使用 C++20 指定初始化。
struct PublicSnapshot {
    std::string label;
    std::int64_t value{};
};

// 普通 class：成员仍然出现在头文件中，但 private 在编译期阻止非法访问。
// 关键不在“变量前面写了 private”，而在于对象自己维护业务不变性：
// balance 永远不能为负数，存取款金额必须为正数，而且不能整数溢出。
class BankAccount {
public:
    explicit BankAccount(std::string owner, std::int64_t initial_balance = 0);

    // 返回 false 表示请求违反规则；失败时账户状态保持不变。
    bool deposit(std::int64_t cents) noexcept;
    bool withdraw(std::int64_t cents) noexcept;

    [[nodiscard]] std::int64_t balance_cents() const noexcept;
    [[nodiscard]] std::string_view owner() const noexcept;

private:
    std::string owner_;
    std::int64_t balance_cents_;
};

// Pimpl（pointer to implementation）：头文件甚至看不到姓名、血量等私有数据。
// 调用方只依赖这个稳定的接口；Impl 的字段和算法可以在 .cpp 中独立演进。
class Player {
public:
    explicit Player(std::string name);
    ~Player();

    Player(Player&&) noexcept;
    Player& operator=(Player&&) noexcept;
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;

    // 无效伤害返回 false；有效伤害会把血量限制在 [0, max_hp]。
    bool take_damage(int damage) noexcept;

    [[nodiscard]] int hp() const noexcept;
    [[nodiscard]] bool alive() const noexcept;
    [[nodiscard]] std::string_view name() const noexcept;

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

} // namespace encapsulation_demo
