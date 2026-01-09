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
      goodEndingUnlocked(false),
      spellbookActivated(false),
      spellbookRead(false),
      premiumItemGiven(false)

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
    interactions.clear();
    interactions.push_back(std::make_unique<RoomInteraction>());
    interactions.push_back(std::make_unique<ItemInteraction>("Old Key"));
    interactions.push_back(std::make_unique<GhostInteraction>());
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
    interactions.push_back(std::make_unique<ItemInteraction>("Candle"));
    interactions.push_back(std::make_unique<GhostInteraction>(true));
    interactions.push_back(std::make_unique<RoomInteraction>("Library"));

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
    for (auto& inter : interactions) {
        inter->play(player);

    }
    for (auto& inter : interactions) {
        if (auto* gi = dynamic_cast<GhostInteraction*>(inter.get())) {
            // (momentan, doar demo)
            // std::cout << "Dynamic cast: this is a GhostInteraction\n";
            (void)gi;
        }
    }


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
    if (currentRoom == &attic) {
        interactWithCasper();
    }

}

void Game::handleLibraryStairsScene() {
    if (!player.hasItem("Candle")) {
        std::cout << "It is too dark to notice anything unusual... Maybe a light source would help.\n";
        return;
    }

    if (!stairsFound) {
        std::cout << "As the candlelight flickers, a hidden passage reveals itself behind a bookshelf...\n";
        std::cout << "A spiral staircase leads upward into darkness.\n";
        stairsFound = true;
    }

    std::cout << "Do you (1) Ignore the staircase or (2) Go up the stairs?\n> ";

    int stairChoice;
    if (!readIntSafe(stairChoice)) stairChoice = 1;

    if (stairChoice == 1) {
        std::cout << "You decide not to climb the stairs right now.\n";
        return;
    }

     if (!atticDiscovered) {
        std::cout << "You push aside the heavy bookshelf and begin climbing...\n";
        atticDiscovered = true;
        mansion.addRoom(attic);
    }

    currentRoom = &attic;
    std::cout << "\nYou arrive in the Attic.\n";

    // interactiunea cu Casper
    Ghost ghost = currentRoom->getGhost();
    std::cout << "A gentle figure appears... " << ghost.getName() << " floats before you.\n";

    if (!casperMet && !casperAngry) {
        std::cout << "\"Welcome, traveler. How will you speak to me?\"\n";
        std::cout << "1. Speak kindly\n";
        std::cout << "2. Stay neutral\n";
        std::cout << "3. Insult Casper\n> ";

        int talk;
        if (!readIntSafe(talk)) talk = 2;

        if (talk == 1) {
            std::cout << "Casper smiles softly.\n";
            std::cout << "\"Kindness still exists... You may yet escape this place.\"\n";
            casperMet = true;
        }
        else if (talk == 2) {
            std::cout << "Casper nods silently and steps aside.\n";
            // neutral path
        }
        else {
            std::cout << "Casper's expression darkens.\n";
            std::cout << "\"Then this mansion shall be your tomb.\"\n";
            casperAngry = true;
            std::cout << "\n BAD ENDING \n";
            gameRunning = false;
        }
    }
    else {
        std::cout << "Casper is still here, watching you quietly...\n";
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
        if (currentRoom != &attic) {
            std::cout << "The spellbook hums faintly... This is not the right place.\n";
            return;
        }

        if (casperAngry) {
            std::cout << "The spellbook burns your hands!\n";
            std::cout << "Casper's curse consumes you...\n";
            std::cout << "\n BAD ENDING \n";
            gameRunning = false;
            return;
        }

        if (!spellbookRead) {
            std::cout << "You read the ancient symbols aloud...\n";
            std::cout << "The attic trembles. Casper turns toward you.\n";
            spellbookRead = true;
        }

        if (casperMet && !premiumItemGiven) {
            std::cout << "Casper smiles warmly.\n";
            std::cout << "\"You have chosen wisdom over fear. Take this.\"\n";

            Item relic("Ethereal Relic",
                       "A powerful artifact blessed by Casper himself.",
                       true);

            player.pickUpItem(relic);
            premiumItemGiven = true;
        }
        else if (!casperMet) {
            std::cout << "A whisper echoes:\n";
            std::cout << "\"Words alone are meaningless without kindness.\"\n";
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

void Game::actHelp()  { printHelp();for (const auto& it : interactions) {
    it->display();
    it->play(player);

}
}
void Game::actRules() { printRules(); }
void Game::actMap()   { printMap();   }
void Game::interactWithCasper() {
    if (!currentRoom->hasGhost()) return;

    Ghost ghost = currentRoom->getGhost();
    if (ghost.getName() != "Casper the Friendly Ghost") return;

    std::cout << "\nCasper floats closer...\n";
    std::cout << "How do you talk to him?\n";
    std::cout << "1. Speak kindly\n";
    std::cout << "2. Stay neutral\n";
    std::cout << "3. Be rude\n> ";

    int choice;
    if (!readIntSafe(choice)) choice = 2;

    if (choice == 1) {
        if (!player.hasItem("Blessed Charm")) {
            Item premium("Blessed Charm",
                "A powerful charm gifted by Casper. It radiates warmth.", true);
            player.pickUpItem(premium);
        }
        std::cout << "Casper smiles warmly and blesses you.\n";
        casperMet = true;
    }
    else if (choice == 2) {
        std::cout << "Casper nods silently and fades a little...\n";
    }
    else {
        std::cout << "Casper's face twists in pain...\n";
        std::cout << "The attic grows cold. You feel your soul tearing apart.\n";
        std::cout << "\nBAD ENDING — You angered the only friendly spirit.\n";
        gameRunning = false;
    }
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
