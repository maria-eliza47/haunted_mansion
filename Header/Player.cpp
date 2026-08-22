#include "Player.h"
#include <iostream>
#include <utility>

Player::Player() : name("Traveler"), inventory(), sanity(100) {}

Player::Player(std::string n, int initialSanity)
    : name(std::move(n)), inventory(), sanity(initialSanity) {}

Player::Player(const Player& other)
    : name(other.name), inventory(other.inventory), sanity(other.sanity) {}

void swap(Player& a, Player& b) noexcept {
    using std::swap;
    swap(a.name, b.name);
    swap(a.inventory, b.inventory);
    swap(a.sanity, b.sanity);
}

Player& Player::operator=(Player other) {
    swap(*this, other);
    return *this;
}

const std::string& Player::getName() const {
    return name;
}

int Player::getSanity() const {
    return sanity;
}

void Player::modifySanity(int delta) {
    sanity += delta;
    if (sanity > 100) sanity = 100;
    if (sanity < 0) sanity = 0;
}

bool Player::isAlive() const {
    return sanity > 0;
}

// cppcheck-suppress unusedFunction
void Player::inspectRoom(const Room& room) const {
    std::cout << "\n" << name << " carefully observes the surroundings...\n";
    room.describe();
}

void Player::pickUpItem(const Item& item) {
    if (item.getName() == "None") {
        std::cout << "You cannot pick that up.\n";
        return;
    }

    if (hasItem(item.getName())) {
        std::cout << "You already have " << item.getName() << " in your inventory.\n";
        return;
    }

    inventory.push_back(item);
    std::cout << "-> Added to inventory: [" << item.getName() << "]\n";
}

// cppcheck-suppress unusedFunction
bool Player::useItem(const std::string& itemName) {
    for (const auto& i : inventory) {
        if (i.getName() == itemName && i.isUsable()) {
            std::cout << name << " uses [" << i.getName() << "].\n";
            return true;
        }
    }
    std::cout << name << " does not possess a usable item called \"" << itemName << "\".\n";
    return false;
}

bool Player::hasItem(const std::string& itemName) const {
    for (const auto& i : inventory) {
        if (i.getName() == itemName)
            return true;
    }
    return false;
}

bool Player::removeItem(const std::string& itemName) {
    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        if (it->getName() == itemName) {
            inventory.erase(it);
            return true;
        }
    }
    return false;
}

void Player::showInventory() const {
    std::cout << "\n=== " << name << "'s Inventory ===\n";
    std::cout << "Sanity: " << sanity << "/100\n";
    if (inventory.empty()) {
        std::cout << "  (Empty)\n";
    } else {
        for (const auto& i : inventory)
            std::cout << "  - " << i << "\n";
    }
    std::cout << "===========================\n";
}

const std::vector<Item>& Player::getInventory() const {
    return inventory;
}

std::ostream& operator<<(std::ostream& os, const Player& p) {
    os << "Player: " << p.name << " (Sanity: " << p.sanity << "/100)\nInventory:\n";
    if (p.inventory.empty()) {
        os << " (empty)\n";
    } else {
        for (const auto& item : p.inventory)
            os << "  - " << item << "\n";
    }
    return os;
}
