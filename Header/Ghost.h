//
// Created by PC on 11/2/2025.
//

#ifndef OOP_GHOST_H
#define OOP_GHOST_H

#include <string>
#include <iostream>


class Ghost {
    private:
    std::string name;
    std::string description;
    bool hostile;

public:
    Ghost(); // constructor default
    Ghost(const std::string& n, const std::string& d, bool h); // cu parametri
    Ghost(const Ghost& other); // copy constructor
    Ghost& operator=(const Ghost& other); // operator=
    ~Ghost(); // destructor

    void haunt() const;
    const std::string& getName() const;

    friend std::ostream& operator<<(std::ostream& os, const Ghost& g);
};

#endif //OOP_GHOST_H