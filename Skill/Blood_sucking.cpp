#include "Blood_sucking.h"
#include "../Character/Character.h"

// call constructor to create a Blood_sucking Object by passing the receiver of the action to the constructor
Blood_sucking::Blood_sucking() : Skill(Blood_sucking_AP_cost, Blood_sucking_MP_cost, Blood_sucking_unlock_level,
Blood_sucking_name, Blood_sucking_rounds_of_effect) {};

// executes the effect of the action
void Blood_sucking::receiver_effect(Character* receiver, Character* doer, double power_up) {
    gain = doer->ATK*5 + 5*power_up - receiver->DEF*2;
    if (gain > receiver->HP) {gain = receiver->HP;}
    receiver->HP = receiver->HP - gain;
    doer->HP += gain;
}

// decrease the doer's AP and MP by the action cost
void Blood_sucking::doer_effect(Character* doer, double power_up) {
    doer->AP -= Blood_sucking_AP_cost;
    doer->MP -= Blood_sucking_MP_cost;
}

// return the description of the action
std::string Blood_sucking::get_description() {
    return Blood_sucking_description;
}

// undo the action's effects, returns the skill type, continues the effects of the action
std::string Blood_sucking::undo_effect() {return "";}
Skill::skill_type Blood_sucking::get_skill_type() {return Skill::skill_type::BLOOD_SUCKING;}
std::string Blood_sucking::continuous_effect(Character* receiver, Character* doer) {return "";}
