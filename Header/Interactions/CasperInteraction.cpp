#include "CasperInteraction.h"
#include "../Player.h"
#include <iostream>
#include <utility>

CasperInteraction::CasperInteraction(std::string m)
    : mood(std::move(m)) {}

void CasperInteraction::execute(Player& player) {
    if (mood == "nice") {
        std::cout << "Casper smiles warmly and gives you a mysterious charm \n";
    } else if (mood == "neutral") {
        std::cout << "Casper nods silently and fades away.\n";
    } else {
        std::cout << "Casper looks hurt... the room grows cold \n";
    }
}

void CasperInteraction::print() const {
    std::cout << "[CasperInteraction] mood = " << mood << "\n";
}

std::unique_ptr<Interaction> CasperInteraction::clone() const {
    return std::make_unique<CasperInteraction>(*this);
}
