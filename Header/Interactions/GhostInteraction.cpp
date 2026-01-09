#include "GhostInteraction.h"
#include "../Player.h"

GhostInteraction::GhostInteraction(bool h) : hostile(h) {}

void GhostInteraction::execute(Player&) {
    if (hostile)
        std::cout << "A hostile ghost attacks!\n";
    else
        std::cout << "A friendly ghost smiles.\n";
}

void GhostInteraction::print() const {
    std::cout << "[GhostInteraction] hostile = " << (hostile ? "true" : "false") << "\n";
}

std::unique_ptr<Interaction> GhostInteraction::clone() const {
    return std::make_unique<GhostInteraction>(*this);
}
