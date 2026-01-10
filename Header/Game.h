#ifndef OOP_GAME_H
#define OOP_GAME_H

#include <string>
#include "Item.h"
#include "Room.h"
#include "Player.h"
#include "Ghost.h"
#include "Mansion.h"
#include <memory>
#include <vector>
#include "Interactions/Interaction.h"
#include "Interactions/CasperInteraction.h"
#include "Interactions/ItemInteraction.h"
#include "Interactions/GhostInteraction.h"
#include "Interactions/RoomInteraction.h"

class Game {
public:
    Game();
    void run();
    const std::string& getCurrentRoomName() const;
    bool currentRoomHasItem(const std::string& itemName) const;
    bool currentRoomHasGhost() const;
    bool playerHasFlag(const std::string& flag) const;


private:
    std::vector<std::unique_ptr<Interaction>> interactions;
    std::unique_ptr<Interaction> currentInteraction;

    Mansion mansion;
    Room hallway;
    Room library;
    Room basement;
    Room attic;

    Player player;

    Room* currentRoom;
    bool gameRunning;

    bool stairsFound;
    bool atticDiscovered;
    bool casperMet;
    bool casperAngry;
    bool goodEndingUnlocked;
    //bool neutralEndingUnlocked;
    //bool badEndingUnlocked;

    void printIntro();
    void setupWorld();
    void placeItemsAndGhosts();

    void printRules() const;
    void printHelp() const;
    void printMap() const;
    void showMenu() const;
    void handleChoice(int choice);

    void actLookAround();
    void actPickItem();
    void actUseItem();
    void actMove();
    void actExit();
    void actInventory();
    void actHelp();
    void actRules();
    void actMap();
    void interactWithCasper();
    void handleLibraryStairsScene();
    void unlockBasementIfKeyUsedInHallway();
    void tryEndGameWithAmuletInBasement();
    [[maybe_unused]] bool spellbookActivated;
    bool spellbookRead;
    bool premiumItemGiven;



    bool readIntSafe(int& out);
};

#endif //OOP_GAME_H