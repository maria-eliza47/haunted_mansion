#ifndef GHOST_INTERACTION_H
#define GHOST_INTERACTION_H

#include "Interaction.h"

class GhostInteraction : public Interaction {
public:
    explicit GhostInteraction(bool hostile);
    std::unique_ptr<Interaction> clone() const override;

    bool isHostile() const { return hostile; }

protected:
    void execute(Player& player) override;
    void print() const override;

private:
    bool hostile;
};

#endif
