#include "Greater_defence.h"
#include "../Character/Character.h"

// call constructor to create a Greater_defence Object by passing the receiver of the action to the constructor
Greater_defence::Greater_defence(Character* receiver) : Skill(Greater_defence_AP_cost, Greater_defence_MP_cost, Greater_defence_unlock_level, Greater_defence_name, Greater_defence_rounds_of_effect),
receiver(receiver) {}

// executes the effect of the action
void Greater_defence::receiver_effect(Character* receiver, Character* doer, double power_up) {
    gain = 10+2*power_up;
    receiver->DEF += gain;
}

// decrease the doer's AP and MP by the action cost
void Greater_defence::doer_effect(Character* doer, double power_up) {
    doer->AP -= Greater_defence_AP_cost;
    doer->MP -= Greater_defence_MP_cost;
}

// return the description of the action
std::string Greater_defence::get_description() {
    return Greater_defence_description;
}

// undo the action's effects
std::string Greater_defence::undo_effect() {
    receiver->DEF -= gain;
    return (receiver->get_name() + "'s DEF decreases by " + std::to_string(gain)) + "!";
}

// continues the effects of the action
std::string Greater_defence::continuous_effect(Character* receiver, Character* doer) {return "";}

// returns the skill type
Skill::skill_type Greater_defence::get_skill_type() {return Skill::skill_type::GREATER_DEFENCE;}
