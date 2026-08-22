#ifndef OOP_MANSION_H
#define OOP_MANSION_H

#include <vector>
#include <string>
#include "Room.h"

class Mansion {
private:
    std::vector<Room> rooms;

public:
    Mansion();

    void addRoom(const Room& room);
    Room* findRoom(const std::string& name);
    const Room* findRoom(const std::string& name) const;
    const std::vector<Room>& getRooms() const;
    void describe() const;

    friend std::ostream& operator<<(std::ostream& os, const Mansion& m);
};

#endif // OOP_MANSION_H
