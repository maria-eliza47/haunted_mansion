#include "RoomInteraction.h"
#include "../Game.h"
#include "../UI.h"
#include <iostream>
#include <utility>

RoomInteraction::RoomInteraction(std::string roomName)
    : roomName(std::move(roomName)) {}

std::unique_ptr<Interaction> RoomInteraction::clone() const {
    return std::make_unique<RoomInteraction>(*this);
}

// cppcheck-suppress unusedFunction
const std::string& RoomInteraction::getRoomName() const {
    return roomName;
}

void RoomInteraction::execute(Game& game) {
    if (roomName == "Library" && !game.isCandleLit()) {
        std::cout << "[Hint] It's very dark. Light a Candle to inspect hidden spots.\n";
    }
}

void RoomInteraction::print() const {
    std::cout << "[RoomInteraction] Room target: " << roomName << "\n";
}

bool RoomInteraction::isAvailable(const Game& game) const {
    return game.getCurrentRoomName() == roomName;
}
