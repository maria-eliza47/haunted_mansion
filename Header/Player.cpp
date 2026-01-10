#include "Player.h"
#include <iostream>

Player::Player() : name("Unnamed Player") {}
Player::Player(const std::string& n) : name(n) {}
Player::Player(const Player& other)
    : name(other.name), inventory(other.inventory) {}

void swap(Player& a, Player& b) noexcept {
    using std::swap;
    swap(a.name, b.name);
    swap(a.inventory, b.inventory);
}

Player& Player::operator=(Player other) {
    swap(*this, other);
    return *this;
}

void Player::inspectRoom(const Room& room) const {
    std::cout << name << " looks around the room...\n";
    room.describe();
}

void Player::pickUpItem(const Item& item) {
    if (item.getName() == "None") {
        std::cout << "You can't pick that up.\n";
        return;
    }

    for (const auto& i : inventory) {
        if (item.getName() == i.getName()) {
            std::cout << "Item already collected: \n" << item.getName() <<  "\n";
            return;
        }
    }

    inventory.push_back(item);
    std::cout << "You picked up " << item.getName() << "!\n";
}

void Player::useItem(const std::string& itemName) {
    for (const auto& i : inventory) {
        if (i.getName() == itemName && i.isUsable()) {
            std::cout << name << " used " << i.getName() << " successfully.\n";
            return;
        }
    }
    std::cout << name << " doesn't have a usable item named " << itemName << ".\n";
}

void Player::showInventory() const {
    std::cout << name << "'s Inventory:\n";
    for (const auto& i : inventory)
        std::cout << " - " << i << "\n";
}
std::ostream& operator<<(std::ostream& os, const Player& p) {
    os << "Player: " << p.name << "\nInventory:\n";
    if (p.inventory.empty()) {
        os << " (empty)\n";
    } else {
        for (const auto& item : p.inventory)
            os << "  - " << item << "\n";
    }
    return os;
}