#ifndef GHOST_H
#define GHOST_H

#include <string>
#include <iostream>


class Ghost {
private:
    std::string name;
    std::string description;
    bool hostile;

public:
    Ghost();
    Ghost(const std::string& n, const std::string& d, bool h);
    Ghost(const Ghost& other);
    Ghost& operator=(const Ghost& other);
    ~Ghost();
    void haunt() const;

    const std::string& getName() const;
    const std::string& getDescription() const { return description; }
    bool isHostile() const { return hostile; }

    friend std::ostream& operator<<(std::ostream& os, const Ghost& g);
};

#endif