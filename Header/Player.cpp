#include "Player.h"
#include <iostream>

Player::Player() : name("Unnamed Player") {}
Player::Player(const std::string& n) : name(n) {}

void Player::inspectRoom(const Room& room) const {
    std::cout << name << " looks around the room...\n";
    room.describe();
}

void Player::pickUpItem(const Item& item) {
    inventory.push_back(item);
    std::cout << name << " picked up " << item.getName() << "!\n";
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