#ifndef GHOST_INTERACTION_H
#define GHOST_INTERACTION_H

#include "Interaction.h"
#include <string>

class Game;

class GhostInteraction : public Interaction {
public:
    explicit GhostInteraction(std::string ghostName, bool hostile);

    std::unique_ptr<Interaction> clone() const override;
    bool isAvailable(const Game& game) const override;

    bool isHostile() const;
    const std::string& getGhostName() const;

protected:
    void execute(Game& game) override;
    void print() const override;

private:
    std::string ghostName;
    bool hostile;
};

#endif // GHOST_INTERACTION_H
