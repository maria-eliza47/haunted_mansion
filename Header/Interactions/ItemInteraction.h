#ifndef ITEM_INTERACTION_H
#define ITEM_INTERACTION_H

#include "Interaction.h"
#include <string>
class Game;

class ItemInteraction : public Interaction {
public:
    explicit ItemInteraction(std::string itemName);

    std::unique_ptr<Interaction> clone() const override;

protected:
    void execute(Game& game) override;
    void print() const override;

private:
    std::string item;
    std::string itemName;
    bool isAvailable(const Game& game) const override;

};

#endif
