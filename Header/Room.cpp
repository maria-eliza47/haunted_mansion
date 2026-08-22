#include "Room.h"
#include <iostream>
#include <utility>

Room::Room()
    : name("Unknown Room"), description("A dark empty space."), ghostPresent(false), explored(false), locked(false) {}

Room::Room(std::string n, std::string d, bool isLocked)
    : name(std::move(n)), description(std::move(d)), ghostPresent(false), explored(false), locked(isLocked) {}

const std::string& Room::getName() const {
    return name;
}

const std::string& Room::getDescription() const {
    return description;
}

void Room::addItem(const Item& item) {
    items.push_back(item);
}

bool Room::hasItem(const std::string& itemName) const {
    for (const auto& item : items) {
        if (item.getName() == itemName) {
            return true;
        }
    }
    return false;
}

Item Room::takeItem(const std::string& itemName) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->getName() == itemName) {
            Item found = *it;
            items.erase(it);
            return found;
        }
    }
    return Item("None", "Invalid item", false);
}

const std::vector<Item>& Room::getItems() const {
    return items;
}

void Room::setGhost(const Ghost& g) {
    ghost = g;
    ghostPresent = true;
}

void Room::removeGhost() {
    ghostPresent = false;
}

bool Room::hasGhost() const {
    return ghostPresent;
}

const Ghost& Room::getGhost() const {
    return ghost;
}

void Room::pacifyGhost() {
    if (ghostPresent) {
        ghost.pacify();
    }
}

bool Room::hasBeenExplored() const {
    return explored;
}

void Room::setExplored(bool val) {
    explored = val;
}

bool Room::isLocked() const {
    return locked;
}

void Room::setLocked(bool isLocked) {
    locked = isLocked;
}

void Room::unlock() {
    locked = false;
}

void Room::addConnection(const std::string& roomName) {
    for (const auto& conn : connections) {
        if (conn == roomName) return;
    }
    connections.push_back(roomName);
}

bool Room::hasConnection(const std::string& roomName) const {
    for (const auto& conn : connections) {
        if (conn == roomName) return true;
    }
    return false;
}

const std::vector<std::string>& Room::getConnections() const {
    return connections;
}

void Room::describe() const {
    std::cout << description << "\n";
    if (ghostPresent) {
        std::cout << "Ghost: " << ghost.getName() << " ("
                  << (ghost.isHostile() ? "Hostile!" : "Peaceful") << ")\n";
    }
}

std::ostream& operator<<(std::ostream& os, const Room& r) {
    os << "Room: " << r.name << "\nDescription: " << r.description << "\n";
    if (r.ghostPresent) {
        os << " Haunted by: " << r.ghost << "\n";
    }
    if (!r.items.empty()) {
        os << " Items in room:\n";
        for (const auto& item : r.items) {
            os << "  - " << item << "\n";
        }
    } else {
        os << " No items here.\n";
    }
    return os;
}
