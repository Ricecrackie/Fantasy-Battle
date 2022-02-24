#include "HPpotion.h"
#include <iostream>
using namespace std;

std::string HPpotion_name = "HP potion";
bool HPpotion_isUsable = true;
bool HPpotion_isEquipable = false;
int HPpotion_rarity = 1;
std::string HPpotion_description = "Recover 50 HP.";
int HPpotion_rounds_of_effect = 0;

// call constructor to create a HPpotion Object by default values
HPpotion::HPpotion() : Item(HPpotion_name, HPpotion_isUsable, 
HPpotion_isEquipable, HPpotion_rarity, HPpotion_rounds_of_effect) {}
std::string HPpotion::get_item_name() {return HPpotion_name;}
bool HPpotion::get_isUsable() {return HPpotion_isUsable;}
bool HPpotion::get_isEquipable() {return HPpotion_isEquipable;}
int HPpotion::get_rarity() {return HPpotion_rarity;}
std::string HPpotion::get_item_description() {return HPpotion_description;}
void HPpotion::receiver_effect(Character& receiver, double power_up) {
    receiver.HP += 50*(1+power_up);
}
Item::item_type HPpotion::get_item_type() {return Item::item_type::HP_POTION;}
