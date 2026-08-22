#include "DataLoader.h"
#include "Exceptions/DataParseException.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

Mansion DataLoader::loadMansion(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw DataParseException("Could not open file: " + filePath);
    }

    nlohmann::json data;
    try {
        file >> data;
    } catch (const nlohmann::json::parse_error& e) {
        throw DataParseException(std::string("JSON parse error: ") + e.what());
    }

    if (!data.contains("rooms") || !data["rooms"].is_array()) {
        throw DataParseException("Invalid data format: missing 'rooms' array.");
    }

    Mansion mansion;

    for (const auto& rJson : data["rooms"]) {
        std::string rName = rJson.value("name", "Unknown Room");
        std::string rDesc = rJson.value("description", "");
        bool rLocked = rJson.value("locked", false);

        Room room(rName, rDesc, rLocked);

        if (rJson.contains("items") && rJson["items"].is_array()) {
            for (const auto& iJson : rJson["items"]) {
                std::string iName = iJson.value("name", "Unknown Item");
                std::string iDesc = iJson.value("description", "");
                bool iUsable = iJson.value("usable", true);
                room.addItem(Item(iName, iDesc, iUsable));
            }
        }

        if (rJson.contains("ghost") && rJson["ghost"].is_object()) {
            const auto& gJson = rJson["ghost"];
            std::string gName = gJson.value("name", "Spirit");
            std::string gDesc = gJson.value("description", "");
            bool gHostile = gJson.value("hostile", false);
            room.setGhost(Ghost(gName, gDesc, gHostile));
        }

        if (rJson.contains("connections") && rJson["connections"].is_array()) {
            for (const auto& cJson : rJson["connections"]) {
                room.addConnection(cJson.get<std::string>());
            }
        }

        mansion.addRoom(room);
    }

    return mansion;
}
