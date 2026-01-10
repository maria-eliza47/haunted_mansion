#include "RoomInteraction.h"
#include "../Player.h"
#include "../Game.h"
#include <iostream>
#include <utility>

RoomInteraction::RoomInteraction(std::string roomName)
    : room(std::move(roomName)) {}

std::unique_ptr<Interaction> RoomInteraction::clone() const {
    return std::make_unique<RoomInteraction>(*this);
}

void RoomInteraction::execute(Game&) {
    std::cout << "You feel the atmosphere of the room: " << room << "\n";
}

void RoomInteraction::print() const {
    std::cout << "[RoomInteraction] room = " << room << "\n";
}
bool RoomInteraction::isAvailable(const Game& game) const {
    return game.getCurrentRoomName() == room;
}