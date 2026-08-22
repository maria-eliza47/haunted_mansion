#ifndef OOP_GAME_H
#define OOP_GAME_H

#include <string>
#include <vector>
#include <memory>
#include "Mansion.h"
#include "Player.h"
#include "Room.h"
#include "Item.h"
#include "Ghost.h"
#include "Interactions/Interaction.h"

class Game {
public:
    Game();
    ~Game() = default;

    void run();
    void initialize(const std::string& dataPath = "data/mansion.json");

    const std::string& getCurrentRoomName() const;
    bool currentRoomHasItem(const std::string& itemName) const;
    bool currentRoomHasGhost() const;
    std::string getCurrentRoomGhostName() const;
    bool getCurrentRoomGhostHostile() const;

    Player& getPlayer();
    const Player& getPlayer() const;

    void damagePlayerSanity(int amount);
    void restorePlayerSanity(int amount);
    void givePlayerItem(const Item& item);
    void removePlayerItem(const std::string& itemName);
    void pacifyCurrentGhost();
    void removeCurrentGhost();

    void setCandleLit(bool lit);
    bool isCandleLit() const;

    void unlockBasement();
    bool isBasementLocked() const;

    void discoverAttic();
    bool isAtticDiscovered() const;

    void setCasperMet(bool met);
    bool isCasperMet() const;

    void setCasperAngry(bool angry);
    bool isCasperAngry() const;

    void tryAltarRitual();

    bool readIntSafe(int& out);

private:
    Mansion mansion;
    Player player;
    Room* currentRoom;

    bool gameRunning;
    bool candleLit;
    bool atticDiscovered;
    bool casperMet;
    bool casperAngry;
    bool ritualCompleted;

    std::vector<std::unique_ptr<Interaction>> interactions;

    void setupInteractions();
    void triggerAvailableInteractions();

    void handleChoice(int choice);
    void actLookAround();
    void actPickItem();
    void actUseItem();
    void actMove();
    void actInventory();
    void actMap();
    void actRules();
    void actHelp();
    void actExit();
};

#endif // OOP_GAME_H
