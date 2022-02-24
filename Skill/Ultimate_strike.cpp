#include "Ultimate_strike.h"
#include "../Character/Character.h"

// call constructor to create a Ultimate_strike Object by passing the receiver of the action to the constructor
Ultimate_strike::Ultimate_strike() : Skill(Ultimate_strike_AP_cost, Ultimate_strike_MP_cost, Ultimate_strike_unlock_level, 
Ultimate_strike_name, Ultimate_strike_rounds_of_effect) {};

// executes the effect of the action
void Ultimate_strike::receiver_effect(Character* receiver, Character* doer, double power_up) {
    receiver->HP = receiver->HP - doer->ATK*50 - 5*power_up + receiver->DEF*2;
}

// decrease the doer's AP and MP by the action cost
void Ultimate_strike::doer_effect(Character* doer, double power_up) {
    doer->AP -= Ultimate_strike_AP_cost;
    doer->MP -= Ultimate_strike_MP_cost;
}

// return the description of the action
std::string Ultimate_strike::get_description() {
    return Ultimate_strike_description;
}

// undo the action's effects, returns the skill type, continues the effects of the action
std::string Ultimate_strike::undo_effect() {return "";}
Skill::skill_type Ultimate_strike::get_skill_type() {return Skill::skill_type::ULTIMATE_STRIKE;}
std::string Ultimate_strike::continuous_effect(Character* receiver, Character* doer) {return "";}
