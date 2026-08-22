#include "Item.h"
#include <utility>

Item::Item() : name("Unknown"), description("No description."), usable(false) {}

Item::Item(std::string name, std::string description, bool usable)
    : name(std::move(name)), description(std::move(description)), usable(usable) {}

const std::string& Item::getName() const {
    return name;
}

const std::string& Item::getDescription() const {
    return description;
}

bool Item::isUsable() const {
    return usable;
}

std::ostream& operator<<(std::ostream& os, const Item& item) {
    os << item.name << " (" << item.description << ")" << (item.usable ? " [usable]" : " [passive]");
    return os;
}
