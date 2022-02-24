/*
 *  This class function is used to generate a Ultimate_strike Object with functions used
 *  check its description and its effects. It is a derived class of Skill.
*/

#ifndef ULTIMATE_STRIKE_H
#define ULTIMATE_STRIKE_H
#include "Skill.h"

const int Ultimate_strike_AP_cost = 15;
const int Ultimate_strike_MP_cost = 125;
const int Ultimate_strike_unlock_level = 4;
const std::string Ultimate_strike_name = "Ultimate Strike";
const int Ultimate_strike_rounds_of_effect = 0;
const std::string Ultimate_strike_description = "Consume 125 MP. Attack a single enemy with 50 times of ATK. ";

class Ultimate_strike : public Skill {
public:
    Ultimate_strike();
    void doer_effect(Character* doer, double power_up);
    void receiver_effect(Character* receiver, Character* doer, double power_up);
    std::string get_description();
    std::string undo_effect();
    std::string continuous_effect(Character* receiver, Character* doer);
    Skill::skill_type get_skill_type();
};
#endif
