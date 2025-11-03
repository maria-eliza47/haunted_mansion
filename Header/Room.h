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
    bool explored = false;

public:
    Room(const std::string& n, const std::string& d);

    const std::string& getName() const { return name; }
    const std::string& getDescription() const { return description; }

    void addItem(const Item& item);
    void setGhost(const Ghost& g);
    bool hasGhost() const;
    Ghost getGhost() const;
    void describe() const;

    bool hasBeenExplored() const { return explored; }
    void setExplored(bool val) { explored = val; }

    bool hasItem( const std::string& itemName) const {
        for (const auto& item : items) {
            if (item.getName() == itemName) {
                return true;
            }
        }
        return false;
    }
        Item takeItem( const std::string& itemName ) {
        for (auto it = items.begin(); it != items.end(); it++) {
            if ((*it).getName() == itemName) {
                Item found = *it;
                items.erase(it);
                return found;
            }
        }
        return Item("None", "Invalid item", false);
    }
};

#endif
