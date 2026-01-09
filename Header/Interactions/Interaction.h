#ifndef INTERACTION_H
#define INTERACTION_H

#include <memory>
#include <iostream>

class Player;

class Interaction {
public:
    Interaction() = default;
    virtual ~Interaction() = default;

    void play(Player& player) {
        print();
        execute(player);
    }

    void display() const {
        print();
    }

    virtual std::unique_ptr<Interaction> clone() const = 0;

protected:
    virtual void execute(Player& player) = 0;
    virtual void print() const = 0;
};

#endif
