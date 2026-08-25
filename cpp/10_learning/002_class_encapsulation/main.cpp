#include "encapsulation.h"

#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

using encapsulation_demo::BankAccount;
using encapsulation_demo::Player;
using encapsulation_demo::PublicSnapshot;

namespace {

void configure_console_encoding() {
#ifdef _WIN32
    // 窄字符串字面量使用 UTF-8；同步设置 Windows 控制台的输出代码页。
    // 如果输出被重定向到文件或 IDE 管道，设置失败也不影响程序运行。
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
}

void print_account(const BankAccount& account) {
    std::cout << account.owner() << " 的余额: " << account.balance_cents() << " 分\n";
}

} // namespace

int main() {
    configure_console_encoding();

    std::cout << "========== 1. struct：公开数据，没有封装 ==========" << '\n';
    PublicSnapshot snapshot{.label = "演示数据", .value = 100};
    snapshot.value = -999; // 合法：struct 不负责阻止调用方破坏数据。
    std::cout << snapshot.label << " = " << snapshot.value << "（外部可直接改写）\n";

    std::cout << "\n========== 2. class：接口维护不变性 ==========" << '\n';
    BankAccount account("小明", 1'000);
    print_account(account);

    std::cout << "存入 500 分: " << (account.deposit(500) ? "成功" : "拒绝") << '\n';
    std::cout << "尝试取出 2,000 分: "
              << (account.withdraw(2'000) ? "成功" : "拒绝（余额不足，状态不变）") << '\n';
    std::cout << "尝试存入 -1 分: "
              << (account.deposit(-1) ? "成功" : "拒绝（金额必须为正）") << '\n';
    print_account(account);

    // account.balance_cents_ = -1; // 编译失败：private 成员是访问边界。
    // 调用方不能绕过 deposit/withdraw，只能通过受控操作改变状态。

    std::cout << "\n========== 3. Pimpl：把实现细节移出头文件 ==========" << '\n';
    Player player("封装勇者");
    std::cout << player.name() << " 初始 HP: " << player.hp() << '\n';
    std::cout << "受到 30 点伤害: " << (player.take_damage(30) ? "已处理" : "无效")
              << ", HP = " << player.hp() << '\n';
    std::cout << "尝试造成 -5 点伤害: "
              << (player.take_damage(-5) ? "已处理" : "拒绝（状态不变）") << '\n';
    const bool lethal_damage = player.take_damage(1'000);
    std::cout << "造成致命伤害（请求 " << (lethal_damage ? "有效" : "无效")
              << "）后: HP = " << player.hp()
              << ", alive = " << (player.alive() ? "true" : "false") << '\n';

    std::cout << R"(

========== 封装的三层含义 ==========
1. 访问控制：private 让非法状态在编译期就无法直接写入。
2. 行为边界：只暴露 deposit、withdraw、take_damage 等有意义的操作，
   每个操作都检查前置条件并维护不变性；失败时状态不变。
3. 实现隐藏：Pimpl 让字段、算法和第三方依赖留在 .cpp，修改它们时，
   只要头文件中的接口不变，使用方源文件无需重新编译（重新链接仍是构建流程的一部分），
   也看不到内部布局。

选择建议：只有一组独立数据时用 struct；需要守护规则或资源时用 class；
还需要稳定 ABI、缩短编译依赖或隐藏实现时，再使用 Pimpl。
)";

    return 0;
}
