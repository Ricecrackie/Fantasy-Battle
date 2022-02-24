/*
 *  This class function is used to generate a Cursing Object with functions used
 *  check its description and its effects. It is a derived class of Skill.
*/

#ifndef CURSING_H
#define CURSING_H
#include "Skill.h"
#include <iostream>
using namespace std;

const int Cursing_AP_cost = 10;
const int Cursing_MP_cost = 50;
const int Cursing_unlock_level = -1; // This skill is not available for player
const std::string Cursing_name = "Cursing";
const int Cursing_rounds_of_effect = 3;
const std::string Cursing_description = "Consume 100 MP. Decrease HP, ATK and DEF of enemy for 3 rounds.";

class Cursing : public Skill {
public:
    Cursing(Character* receiver);
    void doer_effect(Character* doer, double power_up);
    void receiver_effect(Character* receiver, Character* doer, double power_up);
    std::string get_description();
    std::string undo_effect();
    std::string continuous_effect(Character* receiver, Character* doer);
    Skill::skill_type get_skill_type();
private:
    Character* receiver;
    int loss;
};
#endif
