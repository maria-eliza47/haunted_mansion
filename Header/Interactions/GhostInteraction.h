#ifndef GHOST_INTERACTION_H
#define GHOST_INTERACTION_H

#include "Interaction.h"
#include <memory>


class GhostInteraction : public Interaction {
public:
    GhostInteraction() = default;  // 👈
    explicit GhostInteraction(bool hostile);

    std::unique_ptr<Interaction> clone() const override;

protected:
    void execute(Player& player) override;
    void print() const override;

private:
    bool hostile = false;
};


#endif
