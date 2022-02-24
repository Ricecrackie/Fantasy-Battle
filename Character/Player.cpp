#include <iostream>
#include "Player.h"
using namespace std;

int PlayerDefaultHPmax = 100;
int PlayerDefaultMPmax = 100;
int PlayerDefaultAPmax = 15;
int PlayerDefaultATK = 10;
int PlayerDefaultDEF = 10;
int PlayerDefaultMoney = 0;
int PlayerDefaultEXP = 0;
int PlayerDefaultLevel = 1;
int PlayerDebugHPmax = 300;
int PlayerDebugMPmax = 300;
int PlayerDebugAPmax = 20;
int PlayerDebugATK = 30;
int PlayerDebugDEF = 30;
int PlayerDebugMoney = 0;
int PlayerDebugEXP = 0;
int PlayerDebugLevel = 5;
int EXPforLevel2 = 100;
int EXPforLevel3 = 150;
int EXPforLevel4 = 200;
int EXPforLevel5 = 250;
extern int LeatherArmor_ATKeffect;
extern int LeatherArmor_DEFeffect;
extern int IronArmor_ATKeffect;
extern int IronArmor_DEFeffect;
extern int DiamondArmor_ATKeffect;
extern int DiamondArmor_DEFeffect;
std::string PlayerDefaultName = "Player";

// call constructor to create a Player Object with passed values
Player::Player(Tower& tower, const int& HP, const int& HP_max, const int& MP, const int& MP_max, const int& AP_max, const int& ATK, const int& DEF,
    const int& money, const int& EXP, const int& level, Item* &equipped_item, std::vector<Item*> inventory) : Character(HP, HP_max, MP, MP_max, 
    AP_max, AP_max, ATK, DEF, money, EXP), equipped_item(equipped_item), inventory(inventory), level(level), battle(nullptr), tower(tower) {
        Skill** learned_skill = new Skill*[10];
        for (int i = 0; i < 10; ++i) {
        learned_skill[i] = nullptr;
        }
        learned_skill[0] = new Regular_attack();
        learned_skill[1] = new Defence(this);
        if (level >= 2) {
            learned_skill[2] = new Strengthen(this);
            learned_skill[3] = new Sharp_attack;
        }
        if (level >= 3) {
            learned_skill[4] = new Blessing(this);
        }
        if (level >= 4) {
            learned_skill[5] = new Blood_sucking;
            learned_skill[6] = new Ultimate_strike;
        }
        if (level == 5) {
            learned_skill[7] = new Greater_defence(this);
            learned_skill[8] = new Greater_strengthen(this);
        }
        this->learned_skill = learned_skill;
    }

// call constructor to create a Boss Object by passing a Tower object to the constructor
Player::Player(Tower& tower) : Character(PlayerDefaultHPmax, PlayerDefaultHPmax, PlayerDefaultMPmax, PlayerDefaultMPmax
, PlayerDefaultAPmax, PlayerDefaultAPmax, PlayerDefaultATK, PlayerDefaultDEF, PlayerDefaultMoney, PlayerDefaultEXP), tower(tower)
//Character(PlayerDebugHPmax, PlayerDebugHPmax, PlayerDebugMPmax, PlayerDebugMPmax, PlayerDebugAPmax, PlayerDebugAPmax, PlayerDebugATK, PlayerDebugDEF, PlayerDebugMoney, PlayerDefaultEXP), tower(tower)
{
    level = 1;
    equipped_item = nullptr;
    battle = nullptr;
    Skill** learned_skill = new Skill*[10];
    for (int i = 0; i < 10; ++i) {
        learned_skill[i] = nullptr;
    }
    learned_skill[0] = new Regular_attack();
    learned_skill[1] = new Defence(this);
    /*learned_skill[2] = new Strengthen(this);
    learned_skill[3] = new Sharp_attack;
    learned_skill[4] = new Blessing(this);
    learned_skill[5] = new Blood_sucking;
    learned_skill[6] = new Ultimate_strike;
    learned_skill[7] = new Greater_defence(this);
    learned_skill[8] = new Greater_strengthen(this);*/
    this->learned_skill = learned_skill;
}

// remove item from player's inventory
void Player::remove_item(Item* item) {
    auto it = find(inventory.begin(), inventory.end(), item);
    if (it != inventory.end()) {
        delete item;
        inventory.erase(it);
    }
}

// return the player's level, pointer to an Item, or the inventory
int Player::get_level() const {
    return level;
}
Item* Player::get_equipped_item() const {
    return equipped_item;
}
std::vector<Item*>& Player::get_inventory() {
    return inventory;
}

// add an item to the player's inventory
void Player::add_item_to_inventory(Item* item) {
    if (inventory.size() == 0) {
        inventory.resize(1);
        inventory[0] = item;
    }
    else {
        inventory.push_back(item);
    }
}

// check if the player has leveled up
bool Player::level_up() {
    if ((level == 1 && EXP < EXPforLevel2) || (level == 2 && EXP < EXPforLevel3) || (level == 3 && EXP < EXPforLevel4) || (level == 4 && EXP < EXPforLevel5) || level == 5) {
        return false;
    }
    ATK += 5;
    DEF += 5;
    set_HP_max(get_HP_max()+50);
    set_MP_max(get_MP_max()+50);
    set_AP_max(get_AP_max()+1);
    HP = get_HP_max();
    MP = get_MP_max();
    AP = get_AP_max();
    if (level == 1 && EXP >= EXPforLevel2) {
        EXP -= EXPforLevel2;
        learned_skill[2] = new Strengthen(this);
        learned_skill[3] = new Sharp_attack;
    }
    if (level == 2 && EXP >= EXPforLevel3) {
        EXP -= EXPforLevel3;
        learned_skill[4] = new Blessing(this);
    }
    if (level == 3 && EXP >= EXPforLevel4) {
        EXP -= EXPforLevel4;
        learned_skill[5] = new Blood_sucking;
        learned_skill[6] = new Ultimate_strike;
    }
    if (level == 4 && EXP >= EXPforLevel5) {
        EXP -= EXPforLevel5;
        learned_skill[7] = new Greater_defence(this);
        learned_skill[8] = new Greater_strengthen(this);
    }
    level++;
    return true;
}

// check the number of equipment in player's inventory
int Player::get_equipment_num() {
    int num = 0;
    for (int i = 0; i < inventory.size(); ++i) {
        if (inventory[i]->get_isEquipable()) {
            ++num;
        }
    }
    return num;
}

// check the number of usuable items in the player's inventory
int Player::get_usable_item_num() {
    int num = 0;
    for (int i = 0; i < inventory.size(); ++i) {
        if (inventory[i]->get_isUsable()) {
            ++num;
        }
    }
    return num;
}

// check if the item is equipable and changes equipment if true
bool Player::change_equipment(Item* equipment) {
    if (!equipment->get_isEquipable()) return false;
    int index;
    for (int i = 0; i < inventory.size(); ++i) {
        if (inventory[i]->get_item_name() == equipment->get_item_name()) {
            index = i;
            break;
        }
    }
    if (equipped_item != nullptr) {
        std::string old_equipment = equipped_item->get_item_name();
        if (old_equipment == "Leather Armor") {
            ATK -= LeatherArmor_ATKeffect;
            DEF -= LeatherArmor_DEFeffect;
        }
        else if (old_equipment == "Iron Armor") {
            ATK -= IronArmor_ATKeffect;
            DEF -= IronArmor_DEFeffect;
        }
        else if (old_equipment == "Diamond Armor") {
            ATK -= DiamondArmor_ATKeffect;
            DEF -= DiamondArmor_DEFeffect;
        }
    }
    Item* temp;
    if (equipment->get_item_name() == "Leather Armor") {
        temp = new LeatherArmor;
        ATK += LeatherArmor_ATKeffect;
        DEF += LeatherArmor_DEFeffect;
    }
    else if (equipment->get_item_name() == "Iron Armor") {
        temp = new IronArmor;
        ATK += IronArmor_ATKeffect;
        DEF += IronArmor_DEFeffect;
    }
    else if (equipment->get_item_name() == "Diamond Armor") {
        temp = new DiamondArmor;
        ATK += DiamondArmor_ATKeffect;
        DEF += DiamondArmor_DEFeffect;
    }
    delete inventory[index];
    inventory.erase(inventory.begin() + index);
    if (equipped_item != nullptr) {
        if (inventory.size() == 0) {
            inventory.resize(1);
            inventory[0] = equipped_item;
        }
        else {inventory.push_back(equipped_item);}
    }
    equipped_item = temp;
    return true;
}

// checks if the item is usable and uses the item if true
bool Player::use_item(Item* item) {
    if (!item->get_isUsable()) return false;
    int index;
    for (int i = 0; i < inventory.size(); ++i) {
        if (inventory[i]->get_item_name() == item->get_item_name()) {
            index = i;
            break;
        }
    }
    item->receiver_effect(*this, 0);
    if (HP > get_HP_max()) {HP = get_HP_max();}
    if (MP > get_MP_max()) {MP = get_MP_max();}
    delete inventory[index];
    inventory.erase(inventory.begin()+index);
    return true;
}

// return the player's info
std::string Player::info() {
    std::string s = "";
    s = "Name: " + get_name() + "\n" +
    "Level: " + std::to_string(get_level()) + "\n" +
    "EXP: ";
    switch(get_level()) {
        case 1: s += std::to_string(EXP) + "/" + std::to_string(EXPforLevel2); break;
        case 2: s += std::to_string(EXP) + "/" + std::to_string(EXPforLevel3); break;
        case 3: s += std::to_string(EXP) + "/" + std::to_string(EXPforLevel4); break;
        case 4: s += std::to_string(EXP) + "/" + std::to_string(EXPforLevel5); break;
        case 5: s += "MAX"; break;
    }
    s += "\n";
    s = s + "Amount: $" + std::to_string(money) + "\n"
    + "HP: " + std::to_string(HP) + "/" + std::to_string(get_HP_max()) + "\n"
    + "MP: " + std::to_string(MP) + "/" + std::to_string(get_MP_max()) + "\n"
    + "AP: " + std::to_string(AP) + "/" + std::to_string(get_AP_max()) + "\n"
    + "ATK: " + std::to_string(ATK) + "\n"
    + "DEF: " + std::to_string(DEF);
    return s;
}
std::string Player::get_name() {return PlayerDefaultName;}
