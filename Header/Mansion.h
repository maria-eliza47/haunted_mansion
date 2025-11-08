#ifndef OOP_MANSION_H
#define OOP_MANSION_H

#include <vector>
#include "Room.h"

class Mansion {
private:
    std::vector<Room> rooms;

public:
    Mansion();
    void addRoom(const Room& room);
    void describe() const;

    friend std::ostream& operator<<(std::ostream& os, const Mansion& m);
};

#endif
