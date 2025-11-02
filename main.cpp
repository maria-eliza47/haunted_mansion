#include <iostream>
#include "Item.h"
#include "Room.h"
#include "Player.h"
#include "Ghost.h"
#include "Mansion.h"

int main() {
    std::cout<<".....Welcome to the HAUNTED MANSION!!......";
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
    player.inspectRoom(hallway);
    player.pickUpItem(key);
    player.useItem("Old key");

    std::cout << "\nNow entering another room......\n\n";
    player.inspectRoom(library);
    player.pickUpItem(candle);
    player.useItem("Candle");

    std::cout << "\n--- Mansion overview ---\n";
    mansion.describe();

    std::cout << "\n Sfarsit Hunted Mansion: TESTESTTEST  \n";
    return 0;
}
