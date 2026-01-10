#include "ItemInteraction.h"
#include "../Player.h"
#include <utility>
#include <iostream>

ItemInteraction::ItemInteraction(std::string itemName)
    : item(std::move(itemName)) {}

std::unique_ptr<Interaction> ItemInteraction::clone() const {
    return std::make_unique<ItemInteraction>(*this);
}

void ItemInteraction::execute(Player&) {
    std::cout << "You interact with item: " << item << "\n";
}

void ItemInteraction::print() const {
    std::cout << "[ItemInteraction] item = " << item << "\n";
}
