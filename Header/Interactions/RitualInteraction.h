#ifndef RITUAL_INTERACTION_H
#define RITUAL_INTERACTION_H

#include "Interaction.h"
#include <string>

class Game;

class RitualInteraction : public Interaction {
public:
    RitualInteraction();

    std::unique_ptr<Interaction> clone() const override;
    bool isAvailable(const Game& game) const override;

protected:
    void execute(Game& game) override;
    void print() const override;

private:
    std::string altarName;
};

#endif // RITUAL_INTERACTION_H
