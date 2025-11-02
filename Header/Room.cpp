#include "Room.h"
#include <iostream>

Room::Room(const std::string& n, const std::string& d)
    : name(n), description(d), ghostPresent(false) {}

void Room::addItem(const Item& item) {
    items.push_back(item);
}

void Room::setGhost(const Ghost& g) {
    ghost = g;
    ghostPresent = true;
}

bool Room::hasGhost() const {
    return ghostPresent;
}

Ghost Room::getGhost() const {
    return ghost;
}

void Room::describe() const {
    std::cout << "Room: " << name << "\n" << description << "\n";
    if (ghostPresent) std::cout << "A ghost haunts this room...\n";
    std::cout << "Items:\n";
    for (const auto& item : items) {
        std::cout << " - " << item.getName() << "\n";
    }
}
