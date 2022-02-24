#include "Greater_strengthen.h"
#include "../Character/Character.h"

// call constructor to create a Greater_strengthen Object by passing the receiver of the action to the constructor
Greater_strengthen::Greater_strengthen(Character* receiver) : Skill(Greater_strengthen_AP_cost, Greater_strengthen_MP_cost, Greater_strengthen_unlock_level, Greater_strengthen_name, Greater_strengthen_rounds_of_effect),
receiver(receiver) {}

// executes the effect of the action
void Greater_strengthen::receiver_effect(Character* receiver, Character* doer, double power_up) {
    gain = 10+2*power_up;
    receiver->ATK += gain;
}

// decrease the doer's AP and MP by the action cost
void Greater_strengthen::doer_effect(Character* doer, double power_up) {
    doer->AP -= Greater_strengthen_AP_cost;
    doer->MP -= Greater_strengthen_MP_cost;
}

// return the description of the action
std::string Greater_strengthen::get_description() {
    return Greater_strengthen_description;
}

// undo the action's effects
std::string Greater_strengthen::undo_effect() {
    receiver->ATK -= gain;
    return (receiver->get_name() + "'s ATK decreases by " + std::to_string(gain));
}

// continues the effects of the action
std::string Greater_strengthen::continuous_effect(Character* receiver, Character* doer) {return "";}

// returns the skill type
Skill::skill_type Greater_strengthen::get_skill_type() {return Skill::skill_type::GREATER_STRENGTHEN;}
