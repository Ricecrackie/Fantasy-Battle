#include "MPpotion.h"

std::string MPpotion_name = "MP potion";
bool MPpotion_isUsable = true;
bool MPpotion_isEquipable = false;
int MPpotion_rarity = 1;
std::string MPpotion_description = "Recover 50 MP.";
int MPpotion_rounds_of_effect = 0;

// call constructor to create a MPpotion Object by default values
MPpotion::MPpotion() : Item(MPpotion_name, MPpotion_isUsable, 
MPpotion_isEquipable, MPpotion_rarity, MPpotion_rounds_of_effect) {}
std::string MPpotion::get_item_name() {return MPpotion_name;}
bool MPpotion::get_isUsable() {return MPpotion_isUsable;}
bool MPpotion::get_isEquipable() {return MPpotion_isEquipable;}
int MPpotion::get_rarity() {return MPpotion_rarity;}
std::string MPpotion::get_item_description() {return MPpotion_description;}
void MPpotion::receiver_effect(Character& receiver, double power_up) {
    receiver.MP += 20*(1+power_up);
}
Item::item_type MPpotion::get_item_type() {return Item::item_type::MP_POTION;}
