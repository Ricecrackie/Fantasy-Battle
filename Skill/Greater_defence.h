/*
 *  This class function is used to generate a Greater_defence Object with functions used
 *  check its description and its effects. It is a derived class of Skill.
*/

#ifndef GREATER_DEFENCE_H
#define GREATER_DEFENCE_H
#include "Skill.h"

const int Greater_defence_AP_cost = 8;
const int Greater_defence_MP_cost = 75;
const int Greater_defence_unlock_level = 5;
const std::string Greater_defence_name = "Greater Defence";
const int Greater_defence_rounds_of_effect = 5;
const std::string Greater_defence_description = "Consume 75 MP. Increase 10 DEF for 5 rounds.";

class Greater_defence : public Skill {
public:
    Greater_defence(Character* receiver);
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
