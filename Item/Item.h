/*
 *  This class function is used to generate an Item Object with virtual functions
 *  set up functions for overloading in derived classes. It is a derived class of Action.
*/

#ifndef ITEM_H
#define ITEM_H
#include "../Character/Character.h"
#include <string>

class Item {
friend class Battle;
public:
    enum class item_type {
        HP_POTION = 1,
        MP_POTION = 2,
        LEATHER_ARMOR = 3,
        IRON_ARMOR = 4,
        DIAMOND_ARMOR = 5
    };
    Item(std::string item_name, bool isUsable, bool isEquipable, int rarity, int round_of_effects);
    virtual std::string get_item_name() = 0;
    virtual bool get_isUsable() = 0;
    virtual bool get_isEquipable() = 0;
    virtual int get_rarity() = 0;
    virtual void receiver_effect(Character& receiver, double power_up) = 0;
    virtual std::string get_item_description() = 0;
    virtual Item::item_type get_item_type() = 0;
private:
    std::string item_name;
    bool isUsable;
    bool isEquipable;
    int rarity;
    int rounds_of_effect;
};
#endif
