#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H

#include <string>
#include <vector>
#include <iostream>
#include "Item.h"
#include "Room.h"

class Player {
private:
    std::string name;
    std::vector<Item> inventory;
    int sanity;

public:
    Player();
    explicit Player(std::string n, int initialSanity = 100);
    Player(const Player& other);
    Player& operator=(Player other);
    ~Player() = default;

    friend void swap(Player& a, Player& b) noexcept;

    const std::string& getName() const;
    int getSanity() const;
    void modifySanity(int delta);
    bool isAlive() const;

    void inspectRoom(const Room& room) const;
    void pickUpItem(const Item& item);
    bool useItem(const std::string& itemName);
    bool hasItem(const std::string& itemName) const;
    bool removeItem(const std::string& itemName);
    void showInventory() const;
    const std::vector<Item>& getInventory() const;

    friend std::ostream& operator<<(std::ostream& os, const Player& p);
};

#endif // OOP_PLAYER_H
