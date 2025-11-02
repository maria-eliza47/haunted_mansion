#include "Ghost.h"
#include <iostream>
#include <string>

Ghost::Ghost()
    : name("Nameless Ghost"), description("A vague apparition."), hostile(false) {
    //std::cout << "Ghost created (default)\n";
}

Ghost::Ghost(const std::string& n, const std::string& d, bool h)
    : name(n), description(d), hostile(h) {
    //std::cout << "Ghost created: " << name << "\n";
}

Ghost::Ghost(const Ghost& other)
    : name(other.name), description(other.description), hostile(other.hostile) {
    //std::cout << "Ghost copied: " << name << "\n";
}

Ghost& Ghost::operator=(const Ghost& other) {
    if (this != &other) {
        name = other.name;
        description = other.description;
        hostile = other.hostile;
    }
    //std::cout << "Ghost assigned: " << name << "\n";
    return *this;
}

Ghost::~Ghost() {
    //std::cout << "Ghost destroyed: " << name << "\n";
}

void Ghost::haunt() const {
    //std::cout << name << " whispers... 'Leave this place...'\n";
}

const std::string& Ghost::getName() const {
    return name;
}

std::ostream& operator<<(std::ostream& os, const Ghost& g) {
    os << " Ghost: " << g.name << " - " << g.description
       << (g.hostile ? " (Hostile)" : " (Friendly)");
    return os;
}