#ifndef INTERACTION_H
#define INTERACTION_H

#include <memory>
#include <iostream>

class Player; // forward declaration

class Interaction {
public:
    Interaction();
    virtual ~Interaction() = default;

    // NON-virtual interface
    void play(Player& player);
    void display() const;

    virtual std::unique_ptr<Interaction> clone() const = 0;

    // static
    static int count();

protected:

    virtual void execute(Player& player) = 0;
    virtual void print() const = 0;

private:
    static int interactionCount;
};

#endif
