#ifndef CASPER_INTERACTION_H
#define CASPER_INTERACTION_H

#include "Interaction.h"
#include <string>

class CasperInteraction : public Interaction {
    std::string mood; // "nice", "neutral", "rude"

public:
    explicit CasperInteraction(std::string mood);

    std::unique_ptr<Interaction> clone() const override;
    void execute(Player& player) override;
    void print() const override;
};

#endif
