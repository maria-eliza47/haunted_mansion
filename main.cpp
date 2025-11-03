#include <iostream>
#include <limits>
#include "Item.h"
#include "Room.h"
#include "Player.h"
#include "Ghost.h"
#include "Mansion.h"

int main() {
    std::cout<<".....Welcome to the HAUNTED MANSION!!......\n";
    std::string playerName;
    std::cout << "Enter your name:";
    std::getline(std::cin, playerName);

    Player player(playerName);

    std::cout << "\nWelcome, " << playerName << "! Your journey in this haunted place is about to begin...\n";
    std::cout << "\n========== GAME RULES ==========\n";
    std::cout << "1. You must explore a room before picking up items.\n";
    std::cout << "2. Some rooms contain ghosts...choose wisely when they appear.\n";
    std::cout << "3. Use collected items to reveal secrets or unlock new rooms.\n";
    std::cout << "4. You can open the help menu anytime to see commands.\n";
    std::cout << "5. Win by breaking the mansion's curse!\n";
    std::cout << "================================\n\n";


    Item key("Old Key", "A rusty key with strange symbols.", true);
    Item candle("Candle", "A flickering candle that lights the room.", true);
    Item amulet("Amulet", "A glowing charm that seems to repel spirits.", true);

    Room hallway("Hallway", "A long corridor with broken mirrors.");
    Room library("Library", "A dusty and dark room filled with ancient books");
    Room basement("Basement", "Cold and dark room, underneath the house where you can hear a lot of strange noises");
    Room attic("Attic", "A dusty attic filled with forgotten memories, what could it possibly hide?");
    bool stairsFound = false;
    bool atticDiscovered = false;

    Item spellbook("Spellbook", "Ancient spells that might protect you from the evil and mistery in this mansion.", true );
    Item silverDagger("Silver Dagger", "A sharp blade that could be used as a weapon against potential enemies.", true);
    Item tonic("Healing Tonic", "A potion that restores your energy.", true );

    library.addItem(spellbook);
    basement.addItem(tonic);
    //attic.addItem(silverDagger);

    Ghost kindSpirit("Casper the Friendly Ghost", "A kind and friendly spirit that watches over lost souls wanting to help them.", false);
    attic.setGhost(kindSpirit);

    basement.setLocked(true);

    hallway.addItem(key);
    hallway.addItem(candle);
    basement.addItem(amulet);
    Ghost spirit("Whispering Shadow", "A faint figure that murmurs your name...", false);
    Ghost wraith("Wraith of the Library", "A scholar who never left his books.", true);
    hallway.setGhost(spirit);
    library.setGhost(wraith);

    Mansion mansion;
    mansion.addRoom(hallway);
    mansion.addRoom(library);
    mansion.addRoom(basement);

    std::cout << "\nWelcome, " << playerName << " your journey in this mansion is about to begin......." << std::endl;
bool gameRunning = true;
    Room* currentRoom = &hallway;
    while (gameRunning) {
        std::cout << "\n You are now in the "<< currentRoom->getName() << ".\n";
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

        int choice;
        std::cout << "> ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number between 1 and 9.\n";
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                player.inspectRoom(*currentRoom);
                currentRoom->setExplored(true);
                if (currentRoom == &library && !stairsFound) {

                    if (player.hasItem("Candle")) {
                        std::cout << "As the candlelight flickers, a hidden passage reveals itself behind a bookshelf...\n";
                        std::cout << "A spiral staircase leads upward into darkness.\n";
                        std::cout << "Do you (1) Ignore it or (2) Go up the stairs?\n> ";

        int stairChoice;
        if (!(std::cin >> stairChoice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            stairChoice = 1;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (stairChoice == 2) {
            std::cout << "You push aside the heavy bookshelf and begin climbing...\n";
            stairsFound = true;
            atticDiscovered = true;
            mansion.addRoom(attic);
            currentRoom = &attic;
            std::cout << "\nYou arrive in the " << currentRoom->getName() << ".\n";

            Ghost ghost = currentRoom->getGhost();
            std::cout << "A gentle figure appears... " << ghost.getName() << " smiles softly.\n";
            std::cout << "\"Welcome, traveler. I’ve been waiting for you.\"\n";
            std::cout << "Do you (1) Listen or (2) Interrupt?\n> ";
            int talk;
            std::cin >> talk;
            std::cin.ignore();

            if (talk == 1) {
                std::cout << "\"The light reveals the truth. Seek the symbol below, and the path shall open...\"\n";
                std::cout << "You feel something change around you...\n";
            } else {
                std::cout << "Her smile fades. The attic grows cold... The air shifts ominously.\n";
                std::cout << "A dark presence seems to awaken somewhere nearby.\n";
            }

        } else {
            std::cout << "You decide to leave the staircase untouched... for now.\n";
            stairsFound = true;
        }
    } else {
        std::cout << "It is too dark to notice anything unusual... Maybe a light source would help.\n";
    }
}


                if (currentRoom->hasGhost()) {
                    Ghost ghost = currentRoom->getGhost();
                    std::cout << "\n The ghost " << ghost.getName() << " appears in the room.\n";

                    if (ghost.isHostile()) {
                        std::cout << "The ghost looks angry and intimidating....\n do you want to (1) fight it or (2) run away from it? ";
                        int gChoice;
                        std::cin >> gChoice;
                        std::cin.ignore();

                        if (gChoice == 1) {
                            std::cout << "You try to fight it, but your hands gets through it!\n";
                            std::cout << "You feel your energy being drained away....\n You are in pain... \nGAME OVER XXXXXXXXXXX.......\n RIP \n";
                            gameRunning = false;

                        }
                        else if (gChoice == 2) {
                            std::cout << "You run away, your heart is pounding...\n";
                        }
                        else {
                            std::cout << ghost.getName() << " whispers: 'Seek the amulet in the darkness below... '\n";
                        }
                    }
                    break;
                }
                case 2: {
                    if (!currentRoom->hasBeenExplored()) {
                        std::cout << "Hint: You should look around before picking up items.\n";
                        break;
                    }
                    std::cout << "Enter the item name you want to pick up: ";
                    std::string itemName;
                    std::getline(std::cin, itemName);

                    if (player.hasItem(itemName)) {
                        std::cout << "Item already collected: " << itemName << "\n";
                        break;
                    }
                    if (currentRoom->hasItem(itemName)) {
                        Item found = currentRoom->takeItem(itemName);
                        player.pickUpItem(found);
                    }
                    else {
                        std::cout << "There is no item named \"" << itemName << "\" in the room.\n";
                    }
                    break;
                }
                case 3: {
                    if (!currentRoom->hasBeenExplored()) {
                        std::cout << "Hint: You should look around before using any items.\n";
                        break;
                    }

                    std::cout << "Enter the item name to use: ";
                    std::string itemName;
                    std::getline(std::cin, itemName);
                    if (!player.hasItem(itemName)) {
                        std::cout << "You don't have an item called: " << itemName << "in your inventory.\n";
                        break;
                    }
                    player.useItem(itemName);

                    if (itemName == "Candle") {
                        std::cout << "The candle flickers, revealing symbols on the wall...\n";
                    }
                    else if (itemName == "Old Key") {
                        if (currentRoom->getName() == "Hallway") {
                            std::cout << "You hear a click echo from the distance... A door has unlocked somewhere.\n";
                            basement.setLocked(false);
                        } else {
                            std::cout << "You try the key, but nothing nearby seems to fit.\n";
                        }
                    }
                    else if (itemName == "Amulet") {
                        if (currentRoom->getName() == "Basement") {
                            std::cout << "The amulet glows brightly! The whispers stop...\n";
                            std::cout << "You feel peace. You've broken the mansion's curse.\n";
                            std::cout << "\nCONGRATULATIONS, " << playerName << "! You survived the Haunted Mansion! YEYYYYYYYYY\n";
                            gameRunning = false;
                        } else {
                            std::cout << "The amulet glows faintly but nothing happens here...\n";
                        }
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
                    break;

                }
                case 4: {
                    std::cout << "Where do you want to go? (hallway / library / basement";
                    if (atticDiscovered) std::cout << " / attic";
                    std::cout << ")\n> ";

                    std::string roomName;
                    std::getline(std::cin, roomName);

                    Room* nextRoom = nullptr;

                    if (roomName == "hallway") nextRoom = &hallway;
                    else if (roomName == "library") nextRoom = &library;
                    else if (roomName == "basement") nextRoom = &basement;
                    else if (roomName == "attic" && atticDiscovered) nextRoom = &attic;
                    else {
                        std::cout << "That room doesn’t exist...\n";
                        break;
                    }
                    currentRoom =nextRoom;
                    std::cout << "\nMoving to " << currentRoom->getName() << "...\n";
                    player.inspectRoom(*currentRoom);
                    break;

                }
                case 5: {
                    std::cout << "\nYou leave the mansion... The doors creak shut behind you.\n";
                    std::cout << "The air outside feels heavy, but you're free.\n";
                    gameRunning = false;
                    break;
                }
            case 6: {
                    std::cout << "\n===== INVENTORY =====\n";
                    player.showInventory();
                    std::cout << "=====================\n";
                    break;
            }
            case 7: {
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
                    break;
            }
            case 8: {
                    std::cout << "\n=== GAME RULES ===\n";
                    std::cout << "1. You must explore a room before picking items.\n";
                    std::cout << "2. Some rooms may be haunted — be careful.\n";
                    std::cout << "3. Use items wisely to survive.\n";
                    std::cout << "4. You win if you lift the mansion’s curse!\n";
                    std::cout << "==================\n";
                    break;
            }
            case 9: {
                    std::cout << "\n=== MANSION MAP ===\n";
                    std::cout << "[Hallway] --- [Library]\n";
                    std::cout << "    |\n";
                    std::cout << " [Basement]\n";
                    if (atticDiscovered) {
                        std::cout << "    ↑\n";
                        std::cout << "  [Attic]\n";
                    }
                    std::cout << "===================\n";
                    break;
            }

            default:
                std::cout << "Invalid choice. Try again. \n";
                break;
        }
    }

    //std::cout << "\n--- Mansion overview ---\n";
    //mansion.describe();

    std::cout << "\n Sfarsit Hunted Mansion  \n";
    return 0;
}
