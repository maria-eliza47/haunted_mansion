#ifndef ROOM_INTERACTION_H
#define ROOM_INTERACTION_H

#include "Interaction.h"
#include <string>
class Game;
class RoomInteraction : public Interaction {
public:
    explicit RoomInteraction(std::string roomName);
    std::unique_ptr<Interaction> clone() const override;

protected:
    void execute(Game& game) override;
    void print() const override;

private:
    std::string room;
    bool isAvailable(const Game& game) const override;

};

#endif
