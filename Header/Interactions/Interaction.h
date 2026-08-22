#ifndef OOP_INTERACTION_H
#define OOP_INTERACTION_H

#include <memory>
#include <iostream>

class Game;

class Interaction {
public:
    Interaction();
    Interaction(const Interaction&);
    Interaction& operator=(const Interaction&) = default;
    virtual ~Interaction();

    // Non-Virtual Interface (NVI)
    void play(Game& game);
    void display() const;

    virtual std::unique_ptr<Interaction> clone() const = 0;
    virtual bool isAvailable(const Game& game) const;

    static int getCount();

protected:
    virtual void execute(Game& game) = 0;
    virtual void print() const = 0;

private:
    static int interactionCount;
};

#endif // OOP_INTERACTION_H
