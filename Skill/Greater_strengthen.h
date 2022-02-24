/*
 *  This class function is used to generate a Greater_strengthen Object with functions used
 *  check its description and its effects. It is a derived class of Skill.
*/

#ifndef GREATER_STRENGTHEN_H
#define GREATER_STRENGTHEN_H
#include "Skill.h"

const int Greater_strengthen_AP_cost = 8;
const int Greater_strengthen_MP_cost = 75;
const int Greater_strengthen_unlock_level = 5;
const std::string Greater_strengthen_name = "Greater Strengthen";
const int Greater_strengthen_rounds_of_effect = 5;
const std::string Greater_strengthen_description = "Consume 75 MP. Increase 10 ATK for 5 rounds.";

class Greater_strengthen : public Skill {
public:
    Greater_strengthen(Character* receiver);
    void doer_effect(Character* doer, double power_up);
    void receiver_effect(Character* receiver, Character* doer, double power_up);
    std::string get_description();
    std::string undo_effect();
    std::string continuous_effect(Character* receiver, Character* doer);
    Skill::skill_type get_skill_type();
private:
    Character* receiver;
    int gain;
};
#endif
