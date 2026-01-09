#ifndef ROOM_LOCKED_EXCEPTION_H
#define ROOM_LOCKED_EXCEPTION_H

#include "GameException.h"

class RoomLockedException : public GameException {
public:
    explicit RoomLockedException(const std::string& msg)
        : GameException(msg) {}
};

#endif
