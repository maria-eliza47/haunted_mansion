#include "Interaction.h"

int Interaction::interactionCount = 0;

Interaction::Interaction() {
    ++interactionCount;
}

Interaction::Interaction(const Interaction&) {
    ++interactionCount;
}

Interaction::~Interaction() {
    --interactionCount;
}

int Interaction::getCount() {
    return interactionCount;
}

void Interaction::play(Game& game) {
    execute(game);
}

// cppcheck-suppress unusedFunction
void Interaction::display() const {
    print();
}

bool Interaction::isAvailable(const Game& /*game*/) const {
    return true;
}
