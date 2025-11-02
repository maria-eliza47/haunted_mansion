#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>
#include "Item.h"
#include "Ghost.h"

class Room {
private:
    std::string name;
    std::string description;
    std::vector<Item> items;
    bool ghostPresent;
    Ghost ghost;

public:
    Room(const std::string& n, const std::string& d);

    const std::string& getName() const { return name; }
    const std::string& getDescription() const { return description; }

    void addItem(const Item& item);
    void setGhost(const Ghost& g);
    bool hasGhost() const;
    Ghost getGhost() const;
    void describe() const;
};

#endif
