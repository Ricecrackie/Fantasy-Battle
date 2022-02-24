/*
 *  This class function is used to generate a Player Object with functions used
 *  associated with the player such as using items to change stats of the player.
*/

#ifndef PLAYER_H
#define PLAYER_H
#include "Character.h"
#include "../Item/LeatherArmor.h"
#include "../Item/IronArmor.h"
#include "../Item/DiamondArmor.h"
#include "../Item/HPpotion.h"
#include "../Item/MPpotion.h"
#include "../Skill/Regular_attack.h"
#include "../Skill/Defence.h"
#include "../Skill/Sharp_attack.h"
#include "../Skill/Strengthen.h"
#include "../Skill/Blessing.h"
#include "../Skill/Blood_sucking.h"
#include "../Skill/Greater_defence.h"
#include "../Skill/Greater_strengthen.h"
#include "../Skill/Ultimate_strike.h"
#include "../Battle.h"
#include <vector>
#include <algorithm>
#include <string>

class Tower;
class Player : public Character {
friend class Battle;
public:
    Player(Tower& tower);
    Player(Tower& tower, const int& HP, const int& HP_max, const int& MP, const int& MP_max, const int& AP_max, const int& ATK, const int& DEF,
    const int& money, const int& EXP, const int& level, Item* &equipped_item, std::vector<Item*> inventory);
    int get_level() const;
    Item* get_equipped_item() const;
    std::vector<Item*>& get_inventory();
    int get_equipment_num();
    int get_usable_item_num();
    bool use_item(Item* item);
    bool change_equipment(Item* equipment);
    bool level_up();
    std::string info();
    std::string get_name();
    void add_item_to_inventory(Item* item);
    void remove_item(Item* item);
    Tower &tower;
    Battle* battle;
private:
    int level;
    Item* equipped_item;
    std::vector<Item*> inventory;
};
#endif
