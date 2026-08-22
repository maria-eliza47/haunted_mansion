#include "CasperInteraction.h"
#include "../Game.h"
#include "../UI.h"
#include <iostream>
#include <utility>

CasperInteraction::CasperInteraction(std::string defaultMood)
    : mood(std::move(defaultMood)) {}

std::unique_ptr<Interaction> CasperInteraction::clone() const {
    return std::make_unique<CasperInteraction>(*this);
}

// cppcheck-suppress unusedFunction
const std::string& CasperInteraction::getMood() const {
    return mood;
}

void CasperInteraction::execute(Game& game) {
    if (game.isCasperAngry()) {
        std::cout << "Casper ignores you with cold eyes.\n";
        return;
    }

    if (game.isCasperMet()) {
        std::cout << "Casper: 'Take the Amulet and Spellbook to the basement altar.'\n";
        return;
    }

    std::cout << "\nCasper appears: 'Welcome, traveler. How will you speak to me?'\n";
    std::cout << " 1. Speak kindly  2. Inquire neutrally  3. Threaten\n> ";

    int choice;
    if (!game.readIntSafe(choice)) choice = 2;

    if (choice == 1) {
        mood = "friendly";
        std::cout << "Casper: 'Your kindness is a blessing.' (+20 Sanity, received [Blessed Charm])\n";
        game.restorePlayerSanity(20);
        game.setCasperMet(true);
        if (!game.getPlayer().hasItem("Blessed Charm")) {
            game.givePlayerItem(Item("Blessed Charm", "A sacred charm radiating peace.", true));
        }
    } else if (choice == 2) {
        mood = "neutral";
        std::cout << "Casper: 'Search the library for the Spellbook, and the crypt for the Amulet.'\n";
        game.setCasperMet(true);
    } else {
        mood = "angry";
        std::cout << "Casper: 'Then perish in darkness!' (-50 Sanity)\n";
        game.setCasperAngry(true);
        game.damagePlayerSanity(50);
    }
}

void CasperInteraction::print() const {
    std::cout << "[CasperInteraction] Mood state: " << mood << "\n";
}

bool CasperInteraction::isAvailable(const Game& game) const {
    return game.getCurrentRoomName() == "Attic";
}
