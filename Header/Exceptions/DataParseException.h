#ifndef DATA_PARSE_EXCEPTION_H
#define DATA_PARSE_EXCEPTION_H

#include "GameException.h"
#include <string>

class DataParseException : public GameException {
public:
    explicit DataParseException(const std::string& msg)
        : GameException("Data parse error: " + msg) {}
};

#endif // DATA_PARSE_EXCEPTION_H
