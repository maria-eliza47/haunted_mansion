#ifndef CASPER_INTERACTION_H
#define CASPER_INTERACTION_H

#include "Interaction.h"
#include <string>

class Game;

class CasperInteraction : public Interaction {
    std::string mood; // "nice", "neutral", "rude"

public:
    explicit CasperInteraction(std::string mood);

    std::unique_ptr<Interaction> clone() const override;
    void execute(Game& game) override;
    void print() const override;
    bool isAvailable(const Game& game) const override;

};

#endif
