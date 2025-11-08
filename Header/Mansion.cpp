#include "Mansion.h"
#include <iostream>

Mansion::Mansion() {}

void Mansion::addRoom(const Room& room) {
    rooms.push_back(room);
}

void Mansion::describe() const {
    std::cout << "Mansion overview:\n";
    for (const auto& room : rooms) {
        room.describe();
        std::cout << "-----------------------\n";
    }
}
std::ostream& operator<<(std::ostream& os, const Mansion& m) {
    os << "===== Mansion Overview =====\n";
    for (const auto& room : m.rooms)
        os << room << "\n-----------------------\n";
    return os;
}