//
// Created by PC on 11/2/2025.
//

#ifndef OOP_ROOM_H
#define OOP_ROOM_H

#include <string>
#include <vector>
#include "Item.h"
#include "Ghost.h"

class Room {
private:
    std::string name;
    std::string description;
    std::vector<Item> items;
    Ghost* ghost;
    public:
    Room();
    Room(const std::string& n, const std::string& d);

    void addItem(const Item& item);
    void setGhost(const Ghost& g);
    void describe() const;

};


#endif //OOP_ROOM_H