#include "Interaction.h"
#include "../Player.h"

int Interaction::interactionCount = 0;

Interaction::Interaction() {
    ++interactionCount;
}
// cppcheck-suppress unusedFunction
int Interaction::count() {
    return interactionCount;
}

void Interaction::display() const {
    print();
}

void Interaction::play(Player& player) {
    print();
    execute(player);
}