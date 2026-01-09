#include "RoomInteraction.h"
#include "../Player.h"
#include <utility>

RoomInteraction::RoomInteraction(std::string roomName)
    : room(std::move(roomName)) {}

void RoomInteraction::execute(Player&) {
    std::cout << "You interact with the room: " << room << "\n";
}

void RoomInteraction::print() const {
    std::cout << "[RoomInteraction] room = " << room << "\n";
}

std::unique_ptr<Interaction> RoomInteraction::clone() const {
    return std::make_unique<RoomInteraction>(*this);
}
