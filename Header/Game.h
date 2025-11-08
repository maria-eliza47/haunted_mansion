#ifndef OOP_GAME_H
#define OOP_GAME_H

#include <string>
#include "Item.h"
#include "Room.h"
#include "Player.h"
#include "Ghost.h"
#include "Mansion.h"

class Game {
public:
    Game();
    void run();

private:
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
    bool neutralEndingUnlocked;
    bool badEndingUnlocked;

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

    void handleLibraryStairsScene();
    void unlockBasementIfKeyUsedInHallway();
    void tryEndGameWithAmuletInBasement();

    bool readIntSafe(int& out);
};

#endif //OOP_GAME_H