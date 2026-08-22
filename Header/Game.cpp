#include "Game.h"
#include "DataLoader.h"
#include "UI.h"
#include "Exceptions/InvalidActionException.h"
#include "Exceptions/MissingItemException.h"
#include "Exceptions/RoomLockedException.h"
#include "Exceptions/GameException.h"
#include "Interactions/GhostInteraction.h"
#include "Interactions/CasperInteraction.h"
#include "Interactions/ItemInteraction.h"
#include "Interactions/RoomInteraction.h"
#include "Interactions/RitualInteraction.h"

#include <iostream>
#include <limits>
#include <utility>

Game::Game()
    : mansion(),
      player(),
      currentRoom(nullptr),
      gameRunning(true),
      candleLit(false),
      atticDiscovered(false),
      casperMet(false),
      casperAngry(false),
      ritualCompleted(false),
      interactions() {}

void Game::initialize(const std::string& dataPath) {
    mansion = DataLoader::loadMansion(dataPath);
    currentRoom = mansion.findRoom("Hallway");
    if (!currentRoom) {
        throw GameException("Starting room 'Hallway' not found in mansion data.");
    }
    setupInteractions();
}

void Game::setupInteractions() {
    interactions.clear();

    // Room atmospheric interactions
    interactions.push_back(std::make_unique<RoomInteraction>("Hallway"));
    interactions.push_back(std::make_unique<RoomInteraction>("Library"));
    interactions.push_back(std::make_unique<RoomInteraction>("Conservatory"));
    interactions.push_back(std::make_unique<RoomInteraction>("Basement"));
    interactions.push_back(std::make_unique<RoomInteraction>("Attic"));

    // Ghost interactions
    interactions.push_back(std::make_unique<GhostInteraction>("Whispering Shadow", false));
    interactions.push_back(std::make_unique<GhostInteraction>("Wraith of the Library", true));
    interactions.push_back(std::make_unique<GhostInteraction>("Guardian of the Crypt", true));

    // Casper special interaction
    interactions.push_back(std::make_unique<CasperInteraction>("neutral"));

    // Ritual special interaction (4th derived hierarchy member)
    interactions.push_back(std::make_unique<RitualInteraction>());

    // Item interactions
    interactions.push_back(std::make_unique<ItemInteraction>("Candle"));
    interactions.push_back(std::make_unique<ItemInteraction>("Old Key"));
    interactions.push_back(std::make_unique<ItemInteraction>("Healing Tonic"));
    interactions.push_back(std::make_unique<ItemInteraction>("Spellbook"));
    interactions.push_back(std::make_unique<ItemInteraction>("Amulet"));
    interactions.push_back(std::make_unique<ItemInteraction>("Silver Dagger"));
}

const std::string& Game::getCurrentRoomName() const {
    static const std::string unknown = "Unknown";
    return currentRoom ? currentRoom->getName() : unknown;
}

bool Game::currentRoomHasItem(const std::string& itemName) const {
    return currentRoom && currentRoom->hasItem(itemName);
}

bool Game::currentRoomHasGhost() const {
    return currentRoom && currentRoom->hasGhost();
}

std::string Game::getCurrentRoomGhostName() const {
    return (currentRoom && currentRoom->hasGhost()) ? currentRoom->getGhost().getName() : "";
}

bool Game::getCurrentRoomGhostHostile() const {
    return currentRoom && currentRoom->hasGhost() && currentRoom->getGhost().isHostile();
}

Player& Game::getPlayer() {
    return player;
}

const Player& Game::getPlayer() const {
    return player;
}

void Game::damagePlayerSanity(int amount) {
    player.modifySanity(-amount);
    std::cout << "[!] Sanity decreased by " << amount << ". Current Sanity: " << player.getSanity() << "%\n";
    if (!player.isAlive()) {
        UI::printEnding("GAME OVER - YOUR MIND WAS CONSUMED BY MADNESS",
                        "The terror of the haunted mansion was too great. Your soul now wanders the halls forever.");
        gameRunning = false;
    }
}

void Game::restorePlayerSanity(int amount) {
    player.modifySanity(amount);
    std::cout << "[+] Sanity restored by " << amount << ". Current Sanity: " << player.getSanity() << "%\n";
}

void Game::givePlayerItem(const Item& item) {
    player.pickUpItem(item);
}

void Game::removePlayerItem(const std::string& itemName) {
    player.removeItem(itemName);
}

void Game::pacifyCurrentGhost() {
    if (currentRoom) {
        currentRoom->pacifyGhost();
    }
}

void Game::removeCurrentGhost() {
    if (currentRoom) {
        currentRoom->removeGhost();
    }
}

void Game::setCandleLit(bool lit) {
    candleLit = lit;
}

bool Game::isCandleLit() const {
    return candleLit;
}

void Game::unlockBasement() {
    Room* b = mansion.findRoom("Basement");
    if (b) {
        b->unlock();
    }
}

bool Game::isBasementLocked() const {
    const Room* b = mansion.findRoom("Basement");
    return b ? b->isLocked() : false;
}

void Game::discoverAttic() {
    atticDiscovered = true;
    Room* lib = mansion.findRoom("Library");
    if (lib && !lib->hasConnection("Attic")) {
        lib->addConnection("Attic");
    }
}

bool Game::isAtticDiscovered() const {
    return atticDiscovered;
}

void Game::setCasperMet(bool met) {
    casperMet = met;
}

bool Game::isCasperMet() const {
    return casperMet;
}

void Game::setCasperAngry(bool angry) {
    casperAngry = angry;
}

bool Game::isCasperAngry() const {
    return casperAngry;
}

void Game::tryAltarRitual() {
    if (getCurrentRoomName() != "Basement") {
        std::cout << "Altar ritual can only be performed in the Basement.\n";
        return;
    }

    bool hasAmulet = player.hasItem("Amulet");
    bool hasSpellbook = player.hasItem("Spellbook");
    bool hasBlessedCharm = player.hasItem("Blessed Charm");

    if (hasAmulet && hasSpellbook && hasBlessedCharm) {
        ritualCompleted = true;
        gameRunning = false;
        UI::printEnding("TRUE VICTORY - THE MANSION IS PURIFIED!",
                        "You place the Amulet, chant from the Spellbook, and activate Casper's Blessed Charm.\n"
                        "A golden light cleanses the entire mansion! The curse is broken forever.\n"
                        "You walk free under the morning sun!");
    } else if (hasAmulet && hasSpellbook) {
        ritualCompleted = true;
        gameRunning = false;
        UI::printEnding("VICTORY - THE CURSE IS BROKEN!",
                        "Using the Amulet and Spellbook, you shatter the altar's demonic seals.\n"
                        "You escape victorious into the night!");
    } else if (hasAmulet) {
        std::cout << "Amulet placed on altar, but you still need the Spellbook to finish the ritual.\n";
    } else {
        std::cout << "The altar pulses with dark energy. You need the Sacred Amulet.\n";
    }
}

void Game::triggerAvailableInteractions() {
    for (const auto& inter : interactions) {
        if (!inter->isAvailable(*this)) {
            continue;
        }

        // Dynamic Cast Demonstration with logical domain purpose:
        // Identify if an active interaction is a GhostInteraction to warn the player
        if (const auto* ghostInter = dynamic_cast<const GhostInteraction*>(inter.get())) {
            if (ghostInter->isHostile() && !player.hasItem("Amulet")) {
                std::cout << "[Sense Dread] You feel spiritual danger from " << ghostInter->getGhostName() << "...\n";
            }
        }

        inter->play(*this);
    }
}

void Game::run() {
    initialize("data/mansion.json");

    UI::printBanner();

    std::string playerName;
    std::cout << "Enter player name: ";
    std::getline(std::cin, playerName);

    try {
        if (playerName.empty()) {
            throw InvalidActionException("Player name empty. Defaulting to 'Traveler'.");
        }
        player = Player(playerName);
    } catch (const GameException& e) {
        std::cout << "[Notice] " << e.what() << "\n";
        player = Player("Traveler");
    }

    while (gameRunning && player.isAlive() && !std::cin.eof()) {
        UI::printHUD(player.getName(),
                    player.getSanity(),
                    getCurrentRoomName(),
                    candleLit,
                    player.hasItem("Amulet"));

        if (currentRoom) {
            UI::printRoomPanel(*currentRoom);
        }

        UI::printMenu();

        int choice;
        std::cout << "> ";
        if (!readIntSafe(choice)) {
            std::cout << "Enter a number 1-9.\n";
            continue;
        }

        try {
            handleChoice(choice);
        } catch (const GameException& e) {
            std::cout << "[!] " << e.what() << "\n";
        }
    }

    if (!player.isAlive()) {
        std::cout << "\n=== GAME OVER: You were consumed by the darkness. ===\n";
    } else if (!ritualCompleted) {
        std::cout << "\nThank you for playing Haunted Mansion!\n";
    }
}

void Game::handleChoice(int choice) {
    switch (choice) {
        case 1: actLookAround(); break;
        case 2: actPickItem();   break;
        case 3: actUseItem();    break;
        case 4: actMove();       break;
        case 5: actInventory();  break;
        case 6: actMap();        break;
        case 7: actRules();      break;
        case 8: actHelp();       break;
        case 9: actExit();       break;
        default:
            std::cout << "Invalid option. Choose 1-9.\n";
            break;
    }
}

void Game::actLookAround() {
    if (!currentRoom) return;

    currentRoom->setExplored(true);

    // Trigger polymorphic interactions for current context
    triggerAvailableInteractions();
}

void Game::actPickItem() {
    if (!currentRoom) return;

    if (!currentRoom->hasBeenExplored()) {
        throw InvalidActionException("Look around (1) before picking up items.");
    }

    const auto& items = currentRoom->getItems();
    if (items.empty()) {
        std::cout << "No items on the floor.\n";
        return;
    }

    std::cout << "\nPick item:\n";
    for (size_t i = 0; i < items.size(); ++i) {
        std::cout << " " << (i + 1) << ". " << items[i].getName() << "\n";
    }
    std::cout << " 0. Cancel\n> ";

    int choice;
    if (!readIntSafe(choice) || choice == 0) return;

    if (choice < 1 || static_cast<size_t>(choice) > items.size()) {
        std::cout << "Invalid selection.\n";
        return;
    }

    std::string selectedName = items[static_cast<size_t>(choice - 1)].getName();
    Item item = currentRoom->takeItem(selectedName);
    player.pickUpItem(item);
}

void Game::actUseItem() {
    const auto& inventory = player.getInventory();
    if (inventory.empty()) {
        throw MissingItemException("Inventory is empty.");
    }

    std::cout << "\nUse item:\n";
    for (size_t i = 0; i < inventory.size(); ++i) {
        std::cout << " " << (i + 1) << ". " << inventory[i].getName() << "\n";
    }
    std::cout << " 0. Cancel\n> ";

    int choice;
    if (!readIntSafe(choice) || choice == 0) return;

    if (choice < 1 || static_cast<size_t>(choice) > inventory.size()) {
        std::cout << "Invalid selection.\n";
        return;
    }

    std::string selectedName = inventory[static_cast<size_t>(choice - 1)].getName();
    ItemInteraction itemInter(selectedName);
    itemInter.play(*this);
}

void Game::actMove() {
    if (!currentRoom) return;

    const auto& connections = currentRoom->getConnections();
    if (connections.empty()) {
        std::cout << "No exits available.\n";
        return;
    }

    std::cout << "\nMove to:\n";
    for (size_t i = 0; i < connections.size(); ++i) {
        std::cout << " " << (i + 1) << ". " << connections[i];
        const Room* target = mansion.findRoom(connections[i]);
        if (target && target->isLocked()) {
            std::cout << " (Locked)";
        }
        std::cout << "\n";
    }
    std::cout << " 0. Cancel\n> ";

    int choice;
    if (!readIntSafe(choice) || choice == 0) return;

    if (choice < 1 || static_cast<size_t>(choice) > connections.size()) {
        std::cout << "Invalid choice.\n";
        return;
    }

    std::string targetRoomName = connections[static_cast<size_t>(choice - 1)];
    Room* nextRoom = mansion.findRoom(targetRoomName);
    if (!nextRoom) {
        std::cout << "Cannot enter that room.\n";
        return;
    }

    if (nextRoom->isLocked()) {
        if (player.hasItem("Old Key")) {
            nextRoom->unlock();
            std::cout << "-> Unlocked " << nextRoom->getName() << " with Old Key.\n";
        } else {
            throw RoomLockedException("Locked! Find the Old Key.");
        }
    }

    currentRoom = nextRoom;
}

void Game::actInventory() {
    player.showInventory();
}

void Game::actMap() {
    UI::printMap(getCurrentRoomName(), atticDiscovered, !isBasementLocked());
}

void Game::actRules() {
    UI::printRules();
}

void Game::actHelp() {
    UI::printHelp();
    std::cout << "[Engine Info] Active interaction objects in memory: " << Interaction::getCount() << "\n";
}

void Game::actExit() {
    gameRunning = false;
    std::cout << "You left the mansion.\n";
}

bool Game::readIntSafe(int& out) {
    if (!(std::cin >> out)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return true;
}
