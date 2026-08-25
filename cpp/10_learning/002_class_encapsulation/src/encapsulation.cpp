#include "encapsulation.h"

#include <limits>
#include <stdexcept>
#include <utility>

namespace encapsulation_demo {

BankAccount::BankAccount(std::string owner, std::int64_t initial_balance)
    : owner_(std::move(owner)), balance_cents_(initial_balance) {
    if (owner_.empty()) {
        throw std::invalid_argument("账户所有者不能为空");
    }
    if (initial_balance < 0) {
        throw std::invalid_argument("初始余额不能为负数");
    }
}

bool BankAccount::deposit(std::int64_t cents) noexcept {
    if (cents <= 0 || cents > std::numeric_limits<std::int64_t>::max() - balance_cents_) {
        return false;
    }
    balance_cents_ += cents;
    return true;
}

bool BankAccount::withdraw(std::int64_t cents) noexcept {
    if (cents <= 0 || cents > balance_cents_) {
        return false;
    }
    balance_cents_ -= cents;
    return true;
}

std::int64_t BankAccount::balance_cents() const noexcept {
    return balance_cents_;
}

std::string_view BankAccount::owner() const noexcept {
    return owner_;
}

struct Player::Impl {
    static constexpr int max_hp = 100;

    explicit Impl(std::string player_name) : name(std::move(player_name)) {}

    std::string name;
    int current_hp = max_hp;
};

Player::Player(std::string name) : impl_(std::make_unique<Impl>(std::move(name))) {
    if (impl_->name.empty()) {
        throw std::invalid_argument("玩家名称不能为空");
    }
}

Player::~Player() = default;
Player::Player(Player&&) noexcept = default;
Player& Player::operator=(Player&&) noexcept = default;

bool Player::take_damage(int damage) noexcept {
    if (damage <= 0 || !impl_) {
        return false;
    }
    impl_->current_hp = damage >= impl_->current_hp ? 0 : impl_->current_hp - damage;
    return true;
}

int Player::hp() const noexcept {
    return impl_ ? impl_->current_hp : 0;
}

bool Player::alive() const noexcept {
    return hp() > 0;
}

std::string_view Player::name() const noexcept {
    return impl_ ? std::string_view{impl_->name} : std::string_view{};
}

} // namespace encapsulation_demo
