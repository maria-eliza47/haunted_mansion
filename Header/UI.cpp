#include "UI.h"
#include "Room.h"
#include "Item.h"
#include "Ghost.h"
#include <iostream>

const std::string UI::RESET        = "";
const std::string UI::BOLD         = "";
const std::string UI::RED          = "";
const std::string UI::GREEN        = "";
const std::string UI::YELLOW       = "";
const std::string UI::BLUE         = "";
const std::string UI::MAGENTA      = "";
const std::string UI::CYAN         = "";
const std::string UI::WHITE        = "";
const std::string UI::BRIGHT_BLACK = "";

void UI::printBanner() {
    std::cout << "\n+--------------------------------------------------+\n";
    std::cout << "|                 HAUNTED MANSION                  |\n";
    std::cout << "|          The Curse of Blackwood Manor            |\n";
    std::cout << "+--------------------------------------------------+\n";
    std::cout << "| Goal: Explore the rooms, gather sacred relics,   |\n";
    std::cout << "| and purify the basement altar to break the curse.|\n";
    std::cout << "+--------------------------------------------------+\n\n";
}

void UI::printHUD(const std::string& playerName, int sanity, const std::string& currentRoomName, bool candleLit, bool hasAmulet) {
    std::cout << "\n--------------------------------------------------\n";
    std::cout << "[" << playerName << " | Sanity: " << sanity << "% | Room: " << currentRoomName << "]\n";
    std::cout << "Status: " << (candleLit ? "[Candle: ON] " : "[Candle: OFF] ")
              << (hasAmulet ? "[Ward: Sacred Amulet]" : "[Ward: None]") << "\n";
}

void UI::printRoomPanel(const Room& room) {
    std::cout << room.getDescription() << "\n";

    if (room.hasGhost()) {
        const Ghost& g = room.getGhost();
        std::cout << "Ghost: " << g.getName() << " (" << (g.isHostile() ? "Hostile!" : "Peaceful") << ")\n";
    }

    const auto& items = room.getItems();
    std::cout << "Items here: ";
    if (items.empty()) {
        std::cout << "None\n";
    } else {
        for (size_t i = 0; i < items.size(); ++i) {
            std::cout << "[" << items[i].getName() << "]" << (i + 1 < items.size() ? ", " : "\n");
        }
    }

    const auto& conns = room.getConnections();
    std::cout << "Exits: ";
    for (size_t i = 0; i < conns.size(); ++i) {
        std::cout << "[" << conns[i] << "]" << (i + 1 < conns.size() ? ", " : "\n");
    }
    std::cout << "--------------------------------------------------\n";
}

void UI::printMap(const std::string& currentRoomName, bool atticDiscovered, bool basementUnlocked) {
    std::cout << "\n=== MAP ===\n";
    auto mark = [&](const std::string& name) {
        return (name == currentRoomName) ? ("[* " + name + " *]") : ("[" + name + "]");
    };

    std::cout << mark("Hallway") << " --- " << (basementUnlocked ? mark("Basement") : "[Locked Basement]") << "\n";
    std::cout << "  |       \\\n";
    std::cout << mark("Conservatory") << "  " << mark("Library") << "\n";
    if (atticDiscovered) {
        std::cout << "            |\n";
        std::cout << "          " << mark("Attic") << "\n";
    }
    std::cout << "===========\n\n";
}

void UI::printEnding(const std::string& title, const std::string& message) {
    std::cout << "\n\n=== " << title << " ===\n";
    std::cout << message << "\n\n";
}

void UI::printRules() {
    std::cout << "\n=== RULES ===\n";
    std::cout << "1. Look around rooms to find items and secrets.\n";
    std::cout << "2. Keep Sanity > 0%. Hostile ghosts reduce it.\n";
    std::cout << "3. Candle reveals the Attic stairs in the Library.\n";
    std::cout << "4. Use Key for Basement, and Amulet + Spellbook on Altar to win.\n\n";
}

void UI::printHelp() {
    std::cout << "\n=== COMMANDS ===\n";
    std::cout << "1. Look around   2. Pick item     3. Use item\n";
    std::cout << "4. Move to room  5. Inventory     6. Map\n";
    std::cout << "7. Rules         8. Help          9. Exit\n\n";
}

void UI::printMenu() {
    std::cout << "Options: 1.Look 2.Pick 3.Use 4.Move 5.Inv 6.Map 7.Rules 8.Help 9.Exit\n";
}
