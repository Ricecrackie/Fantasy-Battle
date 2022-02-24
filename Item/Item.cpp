#include "Item.h"

// call constructor to create an Item Object by using passed values
Item::Item(std::string item_name, bool isUsable, bool isEquipable, int rarity, int rounds_of_effect) : 
item_name(item_name), isUsable(isUsable), isEquipable(isEquipable), rarity(rarity), rounds_of_effect(rounds_of_effect) {}
