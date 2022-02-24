#include "Defence.h"
#include "../Character/Character.h"

// call constructor to create a Defence Object by passing the receiver of the action to the constructor
Defence::Defence(Character* receiver) : Skill(Defence_AP_cost, Defence_MP_cost, Defence_unlock_level, Defence_name, Defence_rounds_of_effect),
receiver(receiver) {
    gain = 0;
}

// executes the effect of the action
void Defence::receiver_effect(Character* receiver, Character* doer, double power_up) {
    gain = 5+2*power_up;
    receiver->DEF += gain;
}

// decrease the doer's AP and MP by the action cost
void Defence::doer_effect(Character* doer, double power_up) {
    doer->AP -= Defence_AP_cost;
    doer->MP -= Defence_MP_cost;
}

// returns the skill type
Skill::skill_type Defence::get_skill_type() {return Skill::skill_type::DEFENCE;}

// return the description of the action
std::string Defence::get_description() {
    return Defence_description;
}

// undo the action's effects
std::string Defence::undo_effect() {
    receiver->DEF -= gain;
    return (receiver->get_name() + "'s DEF decreases by " + std::to_string(gain)) + "!";
}

// continues the effects of the action
std::string Defence::continuous_effect(Character* receiver, Character* doer) {return "";}
