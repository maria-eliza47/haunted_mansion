#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>
#include <iostream>
#include "Item.h"
#include "Ghost.h"

class Room {
private:
    std::string name;
    std::string description;
    std::vector<Item> items;
    bool ghostPresent = false;
    Ghost ghost;
    bool explored = false;
    bool locked = false;
    std::vector<std::string> connections;

public:
    Room();
    Room(std::string n, std::string d, bool isLocked = false);

    const std::string& getName() const;
    const std::string& getDescription() const;

    void addItem(const Item& item);
    bool hasItem(const std::string& itemName) const;
    Item takeItem(const std::string& itemName);
    const std::vector<Item>& getItems() const;

    void setGhost(const Ghost& g);
    void removeGhost();
    bool hasGhost() const;
    const Ghost& getGhost() const;
    void pacifyGhost();

    bool hasBeenExplored() const;
    void setExplored(bool val);

    bool isLocked() const;
    void setLocked(bool isLocked);
    void unlock();

    void addConnection(const std::string& roomName);
    bool hasConnection(const std::string& roomName) const;
    const std::vector<std::string>& getConnections() const;

    void describe() const;

    friend std::ostream& operator<<(std::ostream& os, const Room& r);
};

#endif // ROOM_H
