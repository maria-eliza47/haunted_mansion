#include <iostream>
#include "Header/Item.h"
#include "Header/Room.h"
#include "Header/Player.h"
#include "Header/Ghost.h"
#include "Header/Mansion.h"

int main() {
    Item key("Old Key", "A rusty key with strange symbols.", true);
    Item candle("Candle", "A flickering candle that lights the room.", true);

    Room hallway("Hallway", "A long corridor with broken mirrors.");
    hallway.addItem(key);
    hallway.addItem(candle);

    Ghost spirit("Whispering Shadow", "A faint figure that murmurs your name...", false);
    hallway.setGhost(spirit);

    Player player("Maria");
    player.inspectRoom(hallway);
    player.pickUpItem(key);
    player.pickUpItem(candle);
    player.useItem("Candle");

    Mansion mansion;
    mansion.addRoom(hallway);
    mansion.describe();

    std::cout << "\n--- End of Haunted Mansion: Test Scenario ---\n";
