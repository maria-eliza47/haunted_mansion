#ifndef GHOST_INTERACTION_H
#define GHOST_INTERACTION_H

#include "Interaction.h"
class Game;
class GhostInteraction : public Interaction {
public:
    explicit GhostInteraction(bool hostile);
    std::unique_ptr<Interaction> clone() const override;

    bool isHostile() const { return hostile; }

protected:
    void execute(Game& game) override;
    void print() const override;

private:
    bool hostile;
    bool isAvailable(const Game& game) const override;

};

#endif
