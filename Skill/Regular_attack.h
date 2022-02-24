/*
 *  This class function is used to generate a Regular_attack Object with functions used
 *  check its description and its effects. It is a derived class of Skill.
*/

#ifndef REGULAR_ATTACK_H
#define REGULAR_ATTACK_H
#include "Skill.h"

const int Regular_attack_AP_cost = 5;
const int Regular_attack_MP_cost = 0;
const int Regular_attack_unlock_level = 1;
const std::string Regular_attack_name = "Regular Attack";
const int Regular_attack_rounds_of_effect = 0;
const std::string Regular_attack_description = "Attack a single enemy with 5 times of ATK.";

class Regular_attack : public Skill {
public:
    Regular_attack();
    void doer_effect(Character* doer, double power_up);
    void receiver_effect(Character* receiver, Character* doer, double power_up);
    std::string get_description();
    std::string undo_effect();
    std::string continuous_effect(Character* receiver, Character* doer);
    Skill::skill_type get_skill_type();
};
#endif
