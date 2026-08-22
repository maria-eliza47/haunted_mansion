#ifndef CASPER_INTERACTION_H
#define CASPER_INTERACTION_H

#include "Interaction.h"
#include <string>

class Game;

class CasperInteraction : public Interaction {
public:
    explicit CasperInteraction(std::string defaultMood = "neutral");

    std::unique_ptr<Interaction> clone() const override;
    bool isAvailable(const Game& game) const override;

    const std::string& getMood() const;

protected:
    void execute(Game& game) override;
    void print() const override;

private:
    std::string mood;
};

#endif // CASPER_INTERACTION_H
