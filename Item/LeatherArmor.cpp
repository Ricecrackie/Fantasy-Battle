#include "LeatherArmor.h"

std::string LeatherArmor_name = "Leather Armor";
bool LeatherArmor_isUsable = false;
bool LeatherArmor_isEquipable = true;
int LeatherArmor_rarity = 1;
int LeatherArmor_ATKeffect = 5;
int LeatherArmor_DEFeffect = 5;
std::string LeatherArmor_description = "Increase 5 ATK and 5 DEF.";
int LeatherArmor_round_of_effects = 0;

// call constructor to create a LeatherArmor Object by default values
LeatherArmor::LeatherArmor() : Item(LeatherArmor_name, LeatherArmor_isUsable, LeatherArmor_isEquipable, LeatherArmor_rarity, LeatherArmor_round_of_effects) {}
std::string LeatherArmor::get_item_name() {return LeatherArmor_name;}
bool LeatherArmor::get_isUsable() {return LeatherArmor_isUsable;}
bool LeatherArmor::get_isEquipable() {return LeatherArmor_isEquipable;}
int LeatherArmor::get_rarity() {return LeatherArmor_rarity;}
std::string LeatherArmor::get_item_description() {return LeatherArmor_description;}
void LeatherArmor::receiver_effect(Character& receiver, double power_up) {}
Item::item_type LeatherArmor::get_item_type() {return Item::item_type::LEATHER_ARMOR;}
