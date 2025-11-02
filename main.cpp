#include <iostream>
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

    Item key("Old Key", "A rusty key with strange symbols.", true);
    Item candle("Candle", "A flickering candle that lights the room.", true);
    Item amulet("Amulet", "A glowing charm that seems to repel spirits.", true);

    Room hallway("Hallway", "A long corridor with broken mirrors.");
    Room library("Library", "A dusty and dark room filled with ancient books");
    Room basement("Basement", "Cold and dark room, underneath the house where you can hear a lot of strange noises");

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
        std::cout << "> ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1:
                player.inspectRoom(*currentRoom);

                if (currentRoom->hasGhost()) {
                    Ghost ghost = currentRoom->getGhost();
                    std::cout << "\n The ghost " << ghost.getName() << " appears in the room.\n";

                    if (ghost.isHostile()) {
                        std::cout << "The ghost looks angry and intimidating.... do you want to (1) fight it or (2) run away from it? ";
                        int gChoice;
                        std::cin >> gChoice;
                        std::cin.ignore();

                        if (gChoice == 1) {
                            std::cout << "You try to fight it, but your hands gets through it!\n";
                            std::cout << "You feel your energy being drained away....\n You are in pain... \nGAME OVER XXXXXXXXXXX\n";
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
                    std::cout << "Enter the item name you want to pick up: ";
                    std::string itemName;
                    std::getline(std::cin, itemName);
                    player.pickUpItem(Item(itemName, "You found this in the " + currentRoom->getName(), true));
                    std::cout << "You picked up " << itemName << "!\n";
                    break;
                }
                case 3: {
                    std::cout << "Enter the item name to use: ";
                    std::string itemName;
                    std::getline(std::cin, itemName);
                    player.useItem(itemName);

                    if (itemName == "Candle") {
                        std::cout << "The candle flickers, revealing symbols on the wall...\n";
                    } else if (itemName == "Old Key" && currentRoom->getName() == "Basement") {
                        std::cout << "The key unlocks a hidden passage in the basement!\n";
                    } else if (itemName == "Amulet" && currentRoom->getName() == "Basement") {
                        std::cout << "The amulet glows brightly! The whispers stop...\n";
                        std::cout << "You feel peace. You've broken the mansion’s curse.\n";
                        std::cout << "\n CONGRATULATIONS, " << playerName << "! You survived the Haunted Mansion!\n";
                        gameRunning = false;
                    }
                    break;
                }
                case 4: {
                    std::cout << "Where do you want to go? (hallway / library / basement)\n> ";
                    std::string roomName;
                    std::getline(std::cin, roomName);

                    if (roomName == "hallway") currentRoom = &hallway;
                    else if (roomName == "library") currentRoom = &library;
                    else if (roomName == "basement") currentRoom = &basement;
                    else std::cout << "That room doesn’t exist...\n";

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
