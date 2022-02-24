/*
 *  This class function is used to generate a Defence Object with functions used
 *  check its description and its effects. It is a derived class of Skill.
*/

#ifndef DEFENCE_H
#define DEFENCE_H
#include "Skill.h"

const int Defence_AP_cost = 5;
const int Defence_MP_cost = 5;
const int Defence_unlock_level = 1;
const std::string Defence_name = "Defence";
const int Defence_rounds_of_effect = 1;
const std::string Defence_description = "Consume 5 MP. Increase 5 DEF for one round.";

class Defence : public Skill {
public:
    Defence(Character* receiver);
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
