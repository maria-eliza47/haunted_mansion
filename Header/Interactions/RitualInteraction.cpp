#include "RitualInteraction.h"
#include "../Game.h"
#include "../UI.h"
#include <iostream>

RitualInteraction::RitualInteraction()
    : altarName("Blackwood Obsidian Altar") {}

std::unique_ptr<Interaction> RitualInteraction::clone() const {
    return std::make_unique<RitualInteraction>(*this);
}

void RitualInteraction::execute(Game& game) {
    bool hasAmulet = game.getPlayer().hasItem("Amulet");
    bool hasSpellbook = game.getPlayer().hasItem("Spellbook");
    bool hasBlessedCharm = game.getPlayer().hasItem("Blessed Charm");

    std::cout << "\n[Altar Relics] Amulet: " << (hasAmulet ? "YES" : "NO")
              << " | Spellbook: " << (hasSpellbook ? "YES" : "NO")
              << " | Blessed Charm: " << (hasBlessedCharm ? "YES" : "OPTIONAL") << "\n";

    if (hasAmulet && hasSpellbook) {
        std::cout << "-> Altar is ready! Use Spellbook or Amulet from inventory to complete ritual.\n";
    }
}

void RitualInteraction::print() const {
    std::cout << "[RitualInteraction] Altar: " << altarName << "\n";
}

bool RitualInteraction::isAvailable(const Game& game) const {
    return game.getCurrentRoomName() == "Basement";
}
