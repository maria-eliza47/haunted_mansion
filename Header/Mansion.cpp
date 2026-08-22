#include "Mansion.h"
#include <iostream>

Mansion::Mansion() = default;

void Mansion::addRoom(const Room& room) {
    for (auto& r : rooms) {
        if (r.getName() == room.getName()) {
            r = room;
            return;
        }
    }
    rooms.push_back(room);
}

Room* Mansion::findRoom(const std::string& name) {
    for (auto& room : rooms) {
        if (room.getName() == name) {
            return &room;
        }
    }
    return nullptr;
}

const Room* Mansion::findRoom(const std::string& name) const {
    for (const auto& room : rooms) {
        if (room.getName() == name) {
            return &room;
        }
    }
    return nullptr;
}

// cppcheck-suppress unusedFunction
const std::vector<Room>& Mansion::getRooms() const {
    return rooms;
}

void Mansion::describe() const {
    std::cout << "\n===== MANSION OVERVIEW =====\n";
    for (const auto& room : rooms) {
        room.describe();
        std::cout << "----------------------------\n";
    }
}

std::ostream& operator<<(std::ostream& os, const Mansion& m) {
    os << "===== Mansion Rooms =====\n";
    for (const auto& room : m.rooms)
        os << room << "\n-----------------------\n";
    return os;
}
