#include "Interaction.h"
#include "ItemInteraction.h"
#include <iostream>
#include <utility>

ItemInteraction::ItemInteraction(std::string itemName)
    : itemName(std::move(itemName)) {}
void ItemInteraction::execute(Game& game) {
    (void)game;
    std::cout << "Item interaction for: " << itemName << "\n";
}

bool ItemInteraction::isAvailable(const Game& game) const {
    (void)game;
    return true;
}

void ItemInteraction::print() const {
    std::cout << "[ItemInteraction] itemName = " << itemName << "\n";
}

std::unique_ptr<Interaction> ItemInteraction::clone() const {
    return std::make_unique<ItemInteraction>(*this);
}


// cppcheck-suppress unusedFunction
