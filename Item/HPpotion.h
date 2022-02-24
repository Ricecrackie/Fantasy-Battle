/*
 *  This class function is used to generate a HPpotion Object with functions used
 *  check its description and its effects. It is a derived class of Items.
*/

#ifndef HPPOTION_H
#define HPPOTION_H
#include "Item.h"
class HPpotion : public Item {
public:
    HPpotion();
    std::string get_item_name();
    bool get_isUsable();
    bool get_isEquipable();
    int get_rarity();
    void receiver_effect(Character& receiver, double power_up);
    std::string get_item_description();
    Item::item_type get_item_type();
};
#endif
