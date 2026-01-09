#ifndef GHOST_INTERACTION_H
#define GHOST_INTERACTION_H

#include "Interaction.h"

class GhostInteraction : public Interaction {
public:
    explicit GhostInteraction(bool hostile);

    void execute(Player& player) override;
    std::unique_ptr<Interaction> clone() const override;

protected:
    void print() const override;

private:
    bool hostile;
};

#endif
