#include "GhostInteraction.h"
#include "../Game.h"
#include "../UI.h"
#include <iostream>
#include <utility>

GhostInteraction::GhostInteraction(std::string ghostName, bool hostile)
    : ghostName(std::move(ghostName)), hostile(hostile) {}

std::unique_ptr<Interaction> GhostInteraction::clone() const {
    return std::make_unique<GhostInteraction>(*this);
}

bool GhostInteraction::isHostile() const {
    return hostile;
}

const std::string& GhostInteraction::getGhostName() const {
    return ghostName;
}

void GhostInteraction::execute(Game& game) {
    if (hostile) {
        std::cout << "[!] " << ghostName << " attacks! ";
        if (game.getPlayer().hasItem("Amulet")) {
            std::cout << "Amulet repels and pacifies the spirit.\n";
            game.pacifyCurrentGhost();
        } else if (game.getPlayer().hasItem("Candle")) {
            std::cout << "Candle softens the blow (-10 Sanity).\n";
            game.damagePlayerSanity(10);
        } else {
            std::cout << "No protection! (-25 Sanity).\n";
            game.damagePlayerSanity(25);
        }
    } else {
        std::cout << "The " << ghostName << " watches you peacefully.\n";
    }
}

void GhostInteraction::print() const {
    std::cout << "[GhostInteraction] Target: " << ghostName << " | Hostile: " << (hostile ? "Yes" : "No") << "\n";
}

bool GhostInteraction::isAvailable(const Game& game) const {
    return game.currentRoomHasGhost() && game.getCurrentRoomGhostName() == ghostName;
}
