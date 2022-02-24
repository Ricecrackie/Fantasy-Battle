#include "DiamondArmor.h"

std::string DiamondArmor_name = "Diamond Armor";
bool DiamondArmor_isUsable = false;
bool DiamondArmor_isEquipable = true;
int DiamondArmor_rarity = 5;
int DiamondArmor_ATKeffect = 20;
int DiamondArmor_DEFeffect = 20;
std::string DiamondArmor_description = "Increase 20 ATK and 20 DEF.";
int DiamondArmor_rounds_of_effect = 0;

// call constructor to create a DiamondArmor Object by default values
DiamondArmor::DiamondArmor() : Item(DiamondArmor_name, DiamondArmor_isUsable, DiamondArmor_isEquipable, DiamondArmor_rarity, DiamondArmor_rounds_of_effect) {}
std::string DiamondArmor::get_item_name() {return DiamondArmor_name;}
bool DiamondArmor::get_isUsable() {return DiamondArmor_isUsable;}
bool DiamondArmor::get_isEquipable() {return DiamondArmor_isEquipable;}
int DiamondArmor::get_rarity() {return DiamondArmor_rarity;}
std::string DiamondArmor::get_item_description() {return DiamondArmor_description;}
void DiamondArmor::receiver_effect(Character& receiver, double power_up) {}
Item::item_type DiamondArmor::get_item_type() {return Item::item_type::DIAMOND_ARMOR;}
