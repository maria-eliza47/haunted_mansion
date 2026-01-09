#ifndef INVALID_ACTION_EXCEPTION_H
#define INVALID_ACTION_EXCEPTION_H

#include "GameException.h"

class InvalidActionException : public GameException {
public:
    explicit InvalidActionException(const std::string& msg)
        : GameException(msg) {}
};

#endif
