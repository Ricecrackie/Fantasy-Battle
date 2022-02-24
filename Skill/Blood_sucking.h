/*
 *  This class function is used to generate a Blood_sucking Object with functions used
 *  check its description and its effects. It is a derived class of Skill.
*/

#ifndef BLOOD_SUCKING_H
#define BLOOD_SUCKING_H
#include "Skill.h"

const int Blood_sucking_AP_cost = 7;
const int Blood_sucking_MP_cost = 40;
const int Blood_sucking_unlock_level = 4;
const std::string Blood_sucking_name = "Blood Sucking";
const int Blood_sucking_rounds_of_effect = 0;
const std::string Blood_sucking_description = "Consume 40 MP. Attack an enemy and gain the HP it loses.";

class Blood_sucking : public Skill {
public:
    Blood_sucking();
    void doer_effect(Character* doer, double power_up);
    void receiver_effect(Character* receiver, Character* doer, double power_up);
    std::string get_description();
    std::string undo_effect();
    std::string continuous_effect(Character* receiver, Character* doer);
    Skill::skill_type get_skill_type();
private:
    int gain;
};
#endif
