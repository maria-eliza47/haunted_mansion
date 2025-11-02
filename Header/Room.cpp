#include "Room.h"
#include <iostream>

Room::Room() : name("Unnamed Room"), description("No description."), ghost(nullptr) {}
Room::Room(const std::string& n, const std::string& d) : name(n), description(d), ghost(nullptr) {}

void Room::addItem(const Item& item) {
    items.push_back(item);
}

void Room::setGhost(const Ghost& g) {
    ghost = new Ghost(g);
}

void Room::describe() const {
    std::cout << "Room: " << name << "\n" << description << "\n";
    if (ghost) std::cout << "A ghost haunts this room...\n";
    std::cout << "Items:\n";
    for (const auto& item : items) std::cout << " - " << item << "\n";
}