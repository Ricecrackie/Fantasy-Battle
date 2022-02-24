/*
 *  This class function is used to generate a Blessing Object with functions used
 *  check its description and its effects. It is a derived class of Skill.
*/

#ifndef BLESSING_H
#define BLESSING_H
#include "Skill.h"

const int Blessing_AP_cost = 10;
const int Blessing_MP_cost = 100;
const int Blessing_unlock_level = 3;
const std::string Blessing_name = "Blessing";
const int Blessing_rounds_of_effect = 5;
const std::string Blessing_description = "Consume 100 MP. Increase HP, ATK and DEF for 5 rounds.";

class Blessing : public Skill {
public:
    Blessing(Character* receiver);
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
