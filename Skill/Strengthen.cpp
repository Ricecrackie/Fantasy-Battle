#include "Strengthen.h"
#include "../Character/Character.h"

// call constructor to create a Strengthen Object by passing the receiver of the action to the constructor
Strengthen::Strengthen(Character* receiver) : Skill(Strengthen_AP_cost, Strengthen_MP_cost, Strengthen_unlock_level, Strengthen_name, Strengthen_rounds_of_effect),
receiver(receiver) {}

// executes the effect of the action
void Strengthen::receiver_effect(Character* receiver, Character* doer, double power_up) {
    gain = 5+2*power_up;
    receiver->ATK += gain;
}

// decrease the doer's AP and MP by the action cost
void Strengthen::doer_effect(Character* doer, double power_up) {
    doer->AP -= Strengthen_AP_cost;
    doer->MP -= Strengthen_MP_cost;
}

// return the description of the action
std::string Strengthen::get_description() {
    return Strengthen_description;
}

// undo the action's effects
std::string Strengthen::undo_effect() {
    receiver->ATK -= gain;
    return (receiver->get_name() + "'s ATK decreases by " + std::to_string(gain));
}

// continues the effects of the action, returns the skill type
std::string Strengthen::continuous_effect(Character* receiver, Character* doer) {return "";}
Skill::skill_type Strengthen::get_skill_type() {return Skill::skill_type::STRENGTHEN;}
