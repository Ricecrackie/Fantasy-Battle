/*
 *  This class function is used to generate a Character Object with functions to
 *  determine the character's stats. It is also the base class for Enemy class.
*/

#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include "../Skill/Skill.h"
class Character { // This is an abstract base class.
friend class Battle;
public:
    int HP; int MP; int AP; int ATK; int DEF; int money; int EXP;
    Skill** learned_skill;
    int get_HP_max();
    int get_MP_max();
    int get_AP_max();
    void set_HP_max(int HP_max);
    void set_MP_max(int MP_max);
    void set_AP_max(int AP_max);
    void set_money(int money);
    virtual std::string info() = 0;
    virtual std::string get_name() = 0;
    Character(const int& HP, const int& HP_max, const int& MP, const int& MP_max,
              const int& AP, const int& AP_max, const int& ATK, const int& DEF, const int& money, const int& EXP);
    Character(Character& character);
private:
    int HP_max;
    int MP_max;
    int AP_max;
};
#endif
