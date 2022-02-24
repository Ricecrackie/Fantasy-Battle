#include "IronArmor.h"

std::string IronArmor_name = "Iron Armor";
bool IronArmor_isUsable = false;
bool IronArmor_isEquipable = true;
int IronArmor_rarity = 3;
int IronArmor_ATKeffect = 10;
int IronArmor_DEFeffect = 10;
std::string IronArmor_description = "Increase 10 ATK and 10 DEF.";
int IronArmor_rounds_of_effect = 0;

// call constructor to create an IronArmor Object by default values
IronArmor::IronArmor() : Item(IronArmor_name, IronArmor_isUsable, IronArmor_isEquipable, IronArmor_rarity, IronArmor_rounds_of_effect) {}
std::string IronArmor::get_item_name() {return IronArmor_name;}
bool IronArmor::get_isUsable() {return IronArmor_isUsable;}
bool IronArmor::get_isEquipable() {return IronArmor_isEquipable;}
int IronArmor::get_rarity() {return IronArmor_rarity;}
std::string IronArmor::get_item_description() {return IronArmor_description;}
void IronArmor::receiver_effect(Character& receiver, double power_up) {}
Item::item_type IronArmor::get_item_type() {return Item::item_type::IRON_ARMOR;}
