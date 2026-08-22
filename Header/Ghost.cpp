#include "Ghost.h"
#include <iostream>
#include <string>

Ghost::Ghost()
    : name("Nameless Ghost"), description("A vague ethereal silhouette."), hostile(false) {}

Ghost::Ghost(const std::string& n, const std::string& d, bool h)
    : name(n), description(d), hostile(h) {}

Ghost::Ghost(const Ghost& other)
    : name(other.name), description(other.description), hostile(other.hostile) {}

Ghost& Ghost::operator=(const Ghost& other) {
    if (this != &other) {
        name = other.name;
        description = other.description;
        hostile = other.hostile;
    }
    return *this;
}

Ghost::~Ghost() = default;

void Ghost::haunt() const {
    std::cout << name << " whispers: 'Turn back before the shadows claim your soul...'\n";
}

void Ghost::pacify() {
    hostile = false;
}

const std::string& Ghost::getName() const {
    return name;
}

const std::string& Ghost::getDescription() const {
    return description;
}

bool Ghost::isHostile() const {
    return hostile;
}

std::ostream& operator<<(std::ostream& os, const Ghost& g) {
    os << "Ghost: " << g.getName() << " - " << g.getDescription()
       << (g.isHostile() ? " [Hostile]" : " [Passive]");
    return os;
}
