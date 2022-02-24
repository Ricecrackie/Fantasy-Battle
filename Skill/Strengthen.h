/*
 *  This class function is used to generate a Strengthen Object with functions used
 *  check its description and its effects. It is a derived class of Skill.
*/

#ifndef STRENGTHEN_H
#define STRENGTHEN_H
#include "Skill.h"

const int Strengthen_AP_cost = 5;
const int Strengthen_MP_cost = 10;
const int Strengthen_unlock_level = 2;
const std::string Strengthen_name = "Strengthen";
const int Strengthen_rounds_of_effect = 1;
const std::string Strengthen_description = "Consume 10 MP. Increase 5 ATK for one round.";

class Strengthen : public Skill {
public:
    Strengthen(Character* receiver);
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
