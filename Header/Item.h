//
// Created by PC on 11/2/2025.
//

#ifndef OOP_ITEM_H
#define OOP_ITEM_H

#include <string>
#include <iostream>

class Item {
private:
    std::string name;
    std::string description;
    bool usable;
public:
    Item();
    Item(const std::string& name, const std::string& description, bool usable);

    ~Item();

    const std::string& getName() const;
    const std::string& getDescription() const;
    bool isUsable() const;

    friend std::ostream& operator<<(std::ostream& os, const Item& item);
};

#endif //OOP_ITEM_H
