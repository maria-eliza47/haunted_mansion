#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H

#include <string>
#include <vector>
#include "Item.h"
#include "Room.h"

class Player {
private:
    std::string name;
    std::vector<Item> inventory;

public:
    Player();
    explicit Player(const std::string& n);

    void inspectRoom(const Room& room) const;
    void pickUpItem(const Item& item);
    void useItem(const std::string& itemName);
    void showInventory() const;

    bool hasItem(const std::string& itemName) const {
        for (const auto& i : inventory) {
            if (i.getName() == itemName)
                return true;
        }
        return false;
    }
};

#endif
