/*
 *  This class function is used to generate a Sharp_attack Object with functions used
 *  check its description and its effects. It is a derived class of Skill.
*/

#ifndef SHARP_ATTACK_H
#define SHARP_ATTACK_H
#include "Skill.h"

const int Sharp_attack_AP_cost = 7;
const int Sharp_attack_MP_cost = 20;
const int Sharp_attack_unlock_level = 2;
const std::string Sharp_attack_name = "Sharp_attack";
const int Sharp_attack_rounds_of_effect = 0;
const std::string Sharp_attack_description = "Consume 20 MP. Regular attack but ignore enemy's DEF.";

class Sharp_attack : public Skill {
public:
    Sharp_attack();
    void doer_effect(Character* doer, double power_up);
    void receiver_effect(Character* receiver, Character* doer, double power_up);
    std::string get_description();
    std::string undo_effect();
    std::string continuous_effect(Character* receiver, Character* doer);
    Skill::skill_type get_skill_type();
};
#endif
