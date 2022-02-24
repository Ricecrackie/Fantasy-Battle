#ifndef ITEM_H
#define ITEM_H
#include <string>

class Item {
public:
    Item(std::string item_name, bool isUsable, bool isEquipable, int rarity);
private:
    std::string item_name;
    bool isUsable;
    bool isEquipable;
    int rarity;
};
#endif