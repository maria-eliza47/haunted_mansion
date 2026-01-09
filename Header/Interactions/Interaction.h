#ifndef INTERACTION_H
#define INTERACTION_H

#include <memory>
#include <string>
#include <iostream>

class Player;

class Interaction {
public:
    Interaction() = default;
    virtual ~Interaction() = default;

    virtual void execute(Player& player) = 0;

    void display() const { print(); }

    virtual std::unique_ptr<Interaction> clone() const = 0;

    static int count();

protected:
    virtual void print() const = 0;

    static int interactionCount;
};

#endif
