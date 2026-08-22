#ifndef OOP_UI_H
#define OOP_UI_H

#include <string>
#include <vector>

class Room;
class Player;

class UI {
public:
    // Constante de text
    static const std::string RESET;
    static const std::string BOLD;
    static const std::string RED;
    static const std::string GREEN;
    static const std::string YELLOW;
    static const std::string BLUE;
    static const std::string MAGENTA;
    static const std::string CYAN;
    static const std::string WHITE;
    static const std::string BRIGHT_BLACK;

    // Afisare minimalista si esentiala
    static void printBanner();
    static void printHUD(const std::string& playerName, int sanity, const std::string& currentRoomName, bool candleLit, bool hasAmulet);
    static void printRoomPanel(const Room& room);
    static void printMap(const std::string& currentRoomName, bool atticDiscovered, bool basementUnlocked);
    static void printMenu();
    static void printRules();
    static void printHelp();
    static void printEnding(const std::string& title, const std::string& message);
};

#endif // OOP_UI_H
