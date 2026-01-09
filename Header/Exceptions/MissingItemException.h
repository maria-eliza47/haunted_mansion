#ifndef MISSING_ITEM_EXCEPTION_H
#define MISSING_ITEM_EXCEPTION_H

#include "GameException.h"

class MissingItemException : public GameException {
public:
    explicit MissingItemException(const std::string& msg)
        : GameException(msg) {}
};

#endif
