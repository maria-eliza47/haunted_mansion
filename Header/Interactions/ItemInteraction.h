#ifndef ITEMINTERACTION_H
#define ITEMINTERACTION_H

#include "Interaction.h"
#include <string>
#include <memory>

class ItemInteraction : public Interaction {
public:
    explicit ItemInteraction(std::string itemName);

    std::unique_ptr<Interaction> clone() const override;

protected:
    void execute(Player& player) override;
    void print() const override;

private:
    std::string item;   // 👈 OBLIGATORIU
};

#endif

