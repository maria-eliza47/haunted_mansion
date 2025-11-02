//
// Created by PC on 11/2/2025.
//

#include "Ghost.h"
Ghost::Ghost() : name("Nameless Ghost"), description("A vague apparition."), hostile(false) {}

Ghost::Ghost(const std::string& n, const std::string& d, bool h)
    : name(n), description(d), hostile(h) {}

Ghost::~Ghost() {}

void Ghost::haunt() const {
    std::cout << name << " whispers: " << description << std::endl;
}

const std::string& Ghost::getName() const { return name; }

std::ostream& operator<<(std::ostream& os, const Ghost& g) {
    os << g.name << " - " << g.description << (g.hostile ? " (hostile)" : " (friendly)");