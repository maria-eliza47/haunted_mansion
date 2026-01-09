#include "Game.h"
#include <iostream>
#include <limits>

Game::Game()
    : hallway("Hallway", "A long corridor with broken mirrors."),
      library("Library", "A dusty and dark room filled with ancient books"),
      basement("Basement", "Cold and dark room, underneath the house where you can hear a lot of strange noises"),
      attic("Attic", "A dusty attic filled with forgotten memories, what could it possibly hide?"),
      currentRoom(nullptr),
      gameRunning(true),
      stairsFound(false),
      atticDiscovered(false),
      casperMet(false),
      casperAngry(false),
      goodEndingUnlocked(false)
      //neutralEndingUnlocked(false),
      //badEndingUnlocked(false)
{
}
void Game::run() {
   // freopen("tastatura.txt", "r", stdin);

    printIntro();

    std::string playerName;
    std::cout << "Enter your name:";
    std::getline(std::cin, playerName);
    if (playerName.empty()) playerName = "Traveler";
    player = Player(playerName);

    std::cout << "\nWelcome, " << playerName << "! Your journey in this haunted place is about to begin...\n";
    printRules();

    setupWorld();
    placeItemsAndGhosts();

    currentRoom = &hallway;

    while (gameRunning && !std::cin.eof()) {
        std::cout << "\n You are now in the " << currentRoom->getName() << ".\n";
        showMenu();

        int choice;
        std::cout << "> ";
        if (!readIntSafe(choice)) {
            std::cout << "Invalid input. Please enter a number between 1 and 9.\n";
            continue;
        }

        handleChoice(choice);
    }
   // std::cout << "\nDEBUG:\n" << mansion;
    //std::cout << "\nDEBUG:\n" << player;


    std::cout << "\n Sfarsit Haunted Mansion  \n" << "You gave up pretty fast, the mansion is waiting for you to try again....\n" << "Later, Traveler!\n";
}

void Game::printIntro() {
    std::cout<<".....Welcome to the HAUNTED MANSION!!......\n";
}

void Game::setupWorld() {
    basement.setLocked(true);
    mansion.addRoom(hallway);
    mansion.addRoom(library);
    mansion.addRoom(basement);
}

void Game::placeItemsAndGhosts() {
    // Items
    Item key("Old Key", "A rusty key with strange symbols.", true);
    Item candle("Candle", "A flickering candle that lights the room.", true);
    Item amulet("Amulet", "A glowing charm that seems to repel spirits.", true);
    Item spellbook("Spellbook", "Ancient spells that might protect you from the evil and mistery in this mansion.", true );
    Item silverDagger("Silver Dagger", "A sharp blade that could be used as a weapon against potential enemies.", true);
    Item tonic("Healing Tonic", "A potion that restores your energy.", true );

    hallway.addItem(key);
    hallway.addItem(candle);
    basement.addItem(amulet);
    basement.addItem(tonic);
    //attic.addItem(silverDagger);
    library.addItem(spellbook);

    // Ghosts
    Ghost spirit("Whispering Shadow", "A faint figure that murmurs your name...", false);
    Ghost wraith("Wraith of the Library", "A scholar who never left his books.", true);
    Ghost kindSpirit("Casper the Friendly Ghost", "A kind and friendly spirit that watches over lost souls wanting to help them.", false);

    hallway.setGhost(spirit);
    library.setGhost(wraith);
    attic.setGhost(kindSpirit);
}

void Game::printRules() const {
    std::cout << "\n========== GAME RULES ==========\n";
    std::cout << "1. You must explore a room before picking up items.\n";
    std::cout << "2. Some rooms contain ghosts...choose wisely when they appear.\n";
    std::cout << "3. Use collected items to reveal secrets or unlock new rooms.\n";
    std::cout << "4. You can open the help menu anytime to see commands.\n";
    std::cout << "5. Win by breaking the mansion's curse!\n";
    std::cout << "================================\n\n";
}

void Game::printHelp() const {
    std::cout << "\n=== HELP MENU ===\n";
    std::cout << "1 - Look around to explore a room.\n";
    std::cout << "2 - Pick up discovered items.\n";
    std::cout << "3 - Use items to unlock secrets or fight curses.\n";
    std::cout << "4 - Move to another room.\n";
    std::cout << "5 - Exit the mansion.\n";
    std::cout << "6 - View your inventory.\n";
    std::cout << "7 - View help menu again.\n";
    std::cout << "8 - See the rules.\n";
    std::cout << "9 - See a simple map of the mansion.\n";
    std::cout << "=====================\n";
}

void Game::printMap() const {
    std::cout << "\n=== MANSION MAP ===\n";
    std::cout << "[Hallway] --- [Basement]\n";
    std::cout << "    |\n";
    std::cout << " [Library]\n";
    if (atticDiscovered) {
        std::cout << "    |\n";
        std::cout << "  [Attic]\n";
    }
    std::cout << "===================\n";
}

void Game::showMenu() const {
    std::cout << "What would you like to do?\n";
    std::cout << "1. Look around\n";
    std::cout << "2. Pick an item\n";
    std::cout << "3. Use an item\n";
    std::cout << "4. Move to another room\n";
    std::cout << "5. Exit the mansion\n";
    std::cout << "6. View inventory\n";
    std::cout << "7. Help\n";
    std::cout << "8. Rules\n";
    std::cout << "9. View map\n";
}

void Game::handleChoice(int choice) {
    switch (choice) {
        case 1: actLookAround(); break;
        case 2: actPickItem();   break;
        case 3: actUseItem();    break;
        case 4: actMove();       break;
        case 5: actExit();       break;
        case 6: actInventory();  break;
        case 7: actHelp();       break;
        case 8: actRules();      break;
        case 9: actMap();        break;
        default:
            std::cout << "Invalid choice. Try again. \n";
            break;
    }
}

void Game::actLookAround() {
    player.inspectRoom(*currentRoom);
    currentRoom->setExplored(true);

    if (currentRoom == &library) {
        handleLibraryStairsScene();
    }

    if (currentRoom->hasGhost()) {
        Ghost ghost = currentRoom->getGhost();
        std::cout << "\n The ghost " << ghost.getName() << " appears in the room.\n";

        if (ghost.isHostile()) {
            std::cout << "The ghost looks angry and intimidating....\n do you want to (1) fight it or (2) run away from it? ";
            int gChoice;
            if (!readIntSafe(gChoice)) gChoice = 2;

            if (gChoice == 1) {
                std::cout << "You try to fight it, but your hands gets through it!\n";
                std::cout << "You feel your energy being drained away....\n You are in pain... \nGAME OVER XXXXXXXXXXX.......\n RIP \n";
                gameRunning = false;

            } else if (gChoice == 2) {
                std::cout << "You run away, your heart is pounding...\n";
            } else {
                std::cout << ghost.getName() << " whispers: 'Seek the amulet in the darkness below... '\n";
            }
        }
    }
}

void Game::handleLibraryStairsScene() {
    if (player.hasItem("Candle")) {
        if (!stairsFound) {
            std::cout << "As the candlelight flickers, a hidden passage reveals itself behind a bookshelf...\n";
            stairsFound = true;
        }

        std::cout << "A spiral staircase leads upward into darkness.\n";
        std::cout << "Do you (1) Ignore it or (2) Go up the stairs?\n> ";

        int stairChoice;
        if (!readIntSafe(stairChoice)) stairChoice = 1;

        if (stairChoice == 2) {
            if (!atticDiscovered) {
                std::cout << "You push aside the heavy bookshelf and begin climbing...\n";
                atticDiscovered = true;
                mansion.addRoom(attic);
            }
            currentRoom = &attic;
            std::cout << "\nYou arrive in the " << currentRoom->getName() << ".\n";

            Ghost ghost = currentRoom->getGhost();
            std::cout << "A gentle figure appears... " << ghost.getName() << " smiles softly.\n";
            std::cout << "\"Welcome, traveler. I've been waiting for you.\"\n";
            std::cout << "Do you (1) Listen or (2) Interrupt?\n> ";

            int talk;
            if (!readIntSafe(talk)) talk = 1;

            if (talk == 1) {
                std::cout << "\"The light reveals the truth. Seek the symbol below, and the path shall open...\"\n";
                std::cout << "You feel something change around you...\n";
                casperMet = true;
            } else {
                std::cout << "Her smile fades. The attic grows cold... The air shifts ominously.\n";
                std::cout << "A dark presence seems to awaken somewhere nearby.\n";
                casperAngry = true;
            }
        } else {
            std::cout << "You decide to leave the staircase untouched... for now.\n";
        }
    } else {
        std::cout << "It is too dark to notice anything unusual... Maybe a light source would help.\n";
    }
}

void Game::actPickItem() {
    if (!currentRoom->hasBeenExplored()) {
        std::cout << "Hint: You should look around before picking up items.\n";
        return;
    }
    std::cout << "Enter the item name you want to pick up: ";
    std::string itemName;
    std::getline(std::cin, itemName);

    if (player.hasItem(itemName)) {
        std::cout << "Item already collected: " << itemName << "\n";
        return;
    }
    if (currentRoom->hasItem(itemName)) {
        Item found = currentRoom->takeItem(itemName);
        player.pickUpItem(found);
    } else {
        std::cout << "There is no item named \"" << itemName << "\" in the room.\n";
    }
}

void Game::actUseItem() {
    if (!currentRoom->hasBeenExplored()) {
        std::cout << "Hint: You should look around before using any items.\n";
        return;
    }

    std::cout << "Enter the item name to use: ";
    std::string itemName;
    std::getline(std::cin, itemName);
    if (!player.hasItem(itemName)) {
        std::cout << "You don't have an item called: " << itemName << "in your inventory.\n";
        return;
    }
    player.useItem(itemName);

    if (itemName == "Candle") {
        std::cout << "The candle flickers, revealing symbols on the wall...\n";
    }
    else if (itemName == "Old Key") {
        unlockBasementIfKeyUsedInHallway();
    }
    else if (itemName == "Amulet") {
        tryEndGameWithAmuletInBasement();
    }
    else if (itemName == "Spellbook") {
        if (currentRoom == &library || currentRoom == &attic) {
            std::cout << "You whisper the words from the Spellbook. The air trembles slightly...\n";
        } else {
            std::cout << "The pages flutter silently. Nothing happens here.\n";
        }
    }
    else if (itemName == "Healing Tonic") {
        std::cout << "You drink the tonic. Warmth spreads through your body and you feel refreshed.\n";
    }
    else if (itemName == "Silver Dagger") {
        std::cout << "You hold the dagger tight. It hums faintly in your hand.\n";
    }
    else {
        std::cout << "Nothing happens when you try to use the " << itemName << ".\n";
    }
}

void Game::unlockBasementIfKeyUsedInHallway() {
    if (currentRoom->getName() == "Hallway") {
        std::cout << "You are very close, try checking the map to see what room near by could be unlocked by this key that you have.\n";
    } else {
        std::cout << "You try the key, but nothing nearby seems to fit.\n";
    }
}

void Game::tryEndGameWithAmuletInBasement() {
    if (currentRoom->getName() == "Basement") {
        std::cout << "The amulet glows brightly! The whispers stop...\n";
        std::cout << "You feel peace. You've broken the mansion's curse.\n";
        std::cout << "\nCONGRATULATIONS! You survived the Haunted Mansion! YEYYYYYYYYY\n";
        goodEndingUnlocked = true;
        gameRunning = false;
    } else {
        std::cout << "The amulet glows faintly but nothing happens here...\n";
    }
}

void Game::actMove() {
    std::cout << "Where do you want to go?\n";
    if (currentRoom == &hallway) {
        std::cout << "(library / basement)\n> ";
    } else if (currentRoom == &library) {
        std::cout << "(hallway";
        if (atticDiscovered) std::cout << " / attic";
        std::cout << ")\n> ";
    } else if (currentRoom == &attic) {
        std::cout << "(library)\n> ";
    } else if (currentRoom == &basement) {
        std::cout << "(hallway)\n> ";
    }
    std::string roomName;
    std::getline(std::cin, roomName);
    Room* nextRoom = nullptr;
    if (currentRoom == &hallway) {
        if (roomName == "library") {
            std::cout << "Walking down the corridor... entering the Library.\n";
            nextRoom = &library;
        }
        else if (roomName == "basement") {
            if (basement.isLocked()) {
                if (player.hasItem("Old Key")) {
                    std::cout << "The basement door is locked. Use the Old Key to unlock it? (1 = Yes / 2 = No)\n> ";
                    int choice;
                    if (!readIntSafe(choice)) choice = 2;
                    if (choice == 1) {
                        basement.setLocked(false);
                        std::cout << "You unlock the heavy door... Descending slowly into the basement.\n";
                        nextRoom = &basement;
                    } else {
                        std::cout << "You step back from the cold door.\n";
                        return;
                    }
                } else {
                    std::cout << "The basement door is locked. You might need a key.\n";
                    return;
                }
            } else {
                std::cout << "You descend the creaking stairs... entering the Basement.\n";
                nextRoom = &basement;
            }
        }
        else {
            std::cout << "You can't go there directly from the hallway.\n";
            return;
        }
    }
    else if (currentRoom == &library) {
        if (roomName == "hallway") {
            std::cout << "Walking through the dusty corridor... back to the Hallway.\n";
            nextRoom = &hallway;
        }
        else if (roomName == "attic" && atticDiscovered) {
            std::cout << "You push the old shelf aside and climb the narrow stairs...\n";
            nextRoom = &attic;
        }
        else {
            std::cout << "That direction doesn't seem to make sense.\n";
            return;
        }
    }
    else if (currentRoom == &attic) {
        if (roomName == "library") {
            std::cout << "You climb down the creaking stairs... back to the Library.\n";
            nextRoom = &library;
        } else {
            std::cout << "You can only descend back to the Library.\n";
            return;
        }
    }
    else if (currentRoom == &basement) {
        if (roomName == "hallway") {
            std::cout << "You climb the damp stone steps... returning to the Hallway.\n";
            nextRoom = &hallway;
        } else {
            std::cout << "You can only go back up to the Hallway.\n";
            return;
        }
    }
    if (nextRoom) {
        currentRoom = nextRoom;
        std::cout << "\nYou are now in the " << currentRoom->getName() << ".\n";
    }
}

void Game::actExit() {
    std::cout << "\nYou leave the mansion... The doors creak shut behind you.\n";
    std::cout << "The air outside feels heavy, but you're free.\n";
    gameRunning = false;
}

void Game::actInventory() {
    std::cout << "\n===== INVENTORY =====\n";
    player.showInventory();
    std::cout << "=====================\n";
}

void Game::actHelp()  { printHelp();  }
void Game::actRules() { printRules(); }
void Game::actMap()   { printMap();   }

bool Game::readIntSafe(int& out) {
    if (!(std::cin >> out)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return true;
}
