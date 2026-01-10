#include "GhostInteraction.h"
#include "../Player.h"
#include <iostream>
#include "../Game.h"


GhostInteraction::GhostInteraction(bool h) : hostile(h) {}

std::unique_ptr<Interaction> GhostInteraction::clone() const {
    return std::make_unique<GhostInteraction>(*this);
}

void GhostInteraction::execute(Game&) {
    if (hostile) {
        std::cout << "The ghost attacks your mind... you feel weaker.\n";
    } else {
        std::cout << "The ghost seems calm... watching you.\n";
    }
}

void GhostInteraction::print() const {
    std::cout << "[GhostInteraction] hostile = " << (hostile ? "true" : "false") << "\n";
}
bool GhostInteraction::isAvailable(const Game& game) const {
    return game.currentRoomHasGhost();
}
