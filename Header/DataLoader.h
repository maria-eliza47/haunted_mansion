#ifndef DATA_LOADER_H
#define DATA_LOADER_H

#include <string>
#include "Mansion.h"

class DataLoader {
public:
    static Mansion loadMansion(const std::string& filePath);
};

#endif // DATA_LOADER_H
