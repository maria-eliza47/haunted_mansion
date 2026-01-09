#ifndef ROOM_INTERACTION_H
#define ROOM_INTERACTION_H

#include "Interaction.h"
#include <string>
#include <memory>

class RoomInteraction : public Interaction {
public:
    RoomInteraction() = default;   // 👈 ADAUGĂ ASTA
    explicit RoomInteraction(std::string roomName);

    std::unique_ptr<Interaction> clone() const override;

protected:
    void execute(Player& player) override;
    void print() const override;

private:
    std::string room;
};


#endif
