#include "ItemInteraction.h"
#include "../Game.h"
#include "../UI.h"
#include <iostream>
#include <utility>

ItemInteraction::ItemInteraction(std::string itemName)
    : itemName(std::move(itemName)) {}

std::unique_ptr<Interaction> ItemInteraction::clone() const {
    return std::make_unique<ItemInteraction>(*this);
}

// cppcheck-suppress unusedFunction
const std::string& ItemInteraction::getItemName() const {
    return itemName;
}

void ItemInteraction::execute(Game& game) {
    if (itemName == "Candle") {
        std::cout << "-> Lit the Candle.\n";
        game.setCandleLit(true);
        if (game.getCurrentRoomName() == "Library" && !game.isAtticDiscovered()) {
            std::cout << "-> Candlelight reveals hidden stairs to the Attic!\n";
            game.discoverAttic();
        }
    } else if (itemName == "Old Key") {
        if (game.getCurrentRoomName() == "Hallway") {
            if (game.isBasementLocked()) {
                std::cout << "-> Unlocked the Basement door with the Old Key.\n";
                game.unlockBasement();
            } else {
                std::cout << "The Basement is already unlocked.\n";
            }
        } else {
            std::cout << "No matching lock in this room.\n";
        }
    } else if (itemName == "Healing Tonic") {
        std::cout << "-> Drank Healing Tonic (+40 Sanity).\n";
        game.restorePlayerSanity(40);
        game.removePlayerItem("Healing Tonic");
    } else if (itemName == "Spellbook" || itemName == "Amulet") {
        if (game.getCurrentRoomName() == "Basement") {
            game.tryAltarRitual();
        } else {
            std::cout << "-> " << itemName << " is ready for the basement altar ritual.\n";
        }
    } else if (itemName == "Silver Dagger") {
        std::cout << "-> Brandished Silver Dagger.\n";
        if (game.currentRoomHasGhost() && game.getCurrentRoomGhostHostile()) {
            std::cout << "-> Banished the hostile ghost!\n";
            game.removeCurrentGhost();
        }
    } else {
        std::cout << "Nothing happened.\n";
    }
}

void ItemInteraction::print() const {
    std::cout << "[ItemInteraction] Target item: " << itemName << "\n";
}

bool ItemInteraction::isAvailable(const Game& /*game*/) const {
    return false; // Activated on demand via useItem
}
