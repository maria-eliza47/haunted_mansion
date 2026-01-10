#ifndef OOP_INTERACTION_H
#define OOP_INTERACTION_H

#include <memory>

class Game;

class Interaction {
public:
    Interaction();
    virtual ~Interaction() = default;

    static int count();

    void play(Game& game) {
        execute(game);
    }

    void display() const { print(); }

    virtual void execute(Game& game) = 0;
    virtual bool isAvailable(const Game& game) const { (void)game; return true; }
    virtual void print() const = 0;
    virtual std::unique_ptr<Interaction> clone() const = 0;

private:
    static int interactionCount;
};

#endif