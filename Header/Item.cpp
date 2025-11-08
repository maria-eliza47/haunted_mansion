#include "Item.h"

Item::Item() : name("Unknown"), description("No description."), usable(false) {}

Item::Item(const std::string& n, const std::string& d, bool u)
    : name(n), description(d), usable(u) {}

Item::~Item() {}

const std::string& Item::getName() const { return name; }

const std::string& Item::getDescription() const { return description; }
bool Item::isUsable() const { return usable; }

std::ostream& operator<<(std::ostream& os, const Item& item) {
    os << item.name << " - " << item.description << (item.usable ? " (usable)" : " (not usable)");
    return os;
}