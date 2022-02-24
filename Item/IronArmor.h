/*
 *  This class function is used to generate a IronArmor Object with functions used
 *  check its description and its effects. It is a derived class of Items.
*/

#ifndef IRON_ARMOR_H
#define IRON_ARMOR_H
#include "Item.h"
#include <string>
class IronArmor : public Item {
public:
    IronArmor();
    std::string get_item_name();
    bool get_isUsable();
    bool get_isEquipable();
    int get_rarity();
    void receiver_effect(Character& receiver, double power_up);
    std::string get_item_description();
    Item::item_type get_item_type();
};
#endif
