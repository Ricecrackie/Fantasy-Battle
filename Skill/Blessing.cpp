#include "Blessing.h"
#include "../Character/Character.h"

// call constructor to create a Blessing Object by passing the receiver of the action to the constructor
Blessing::Blessing(Character* receiver) : Skill(Blessing_AP_cost, Blessing_MP_cost, Blessing_unlock_level, Blessing_name, Blessing_rounds_of_effect)
, receiver(receiver) {}

// returns the skill type
Skill::skill_type Blessing::get_skill_type() {
    return Skill::skill_type::BLESSING;
}

// executes the effect of the action
void Blessing::receiver_effect(Character* receiver, Character* doer, double power_up) {
    gain = 10+2*power_up;
    receiver->ATK += gain;
    receiver->DEF += gain;
}

// decrease the doer's AP and MP by the action cost
void Blessing::doer_effect(Character* doer, double power_up) {
    doer->AP -= Blessing_AP_cost;
    doer->MP -= Blessing_MP_cost;
}

// return the description of the action
std::string Blessing::get_description() {
    return Blessing_description;
}

// undo the action's effects
std::string Blessing::undo_effect() {
    receiver->ATK -= gain;
    receiver->DEF -= gain;
    return (receiver->get_name() + "'s ATK decreases by " + std::to_string(gain) + "!" + "\n"
    + receiver->get_name() + "'s DEF decreases by " + std::to_string(gain) + "!");
}

// continues the effects of the action
std::string Blessing::continuous_effect(Character* receiver, Character* doer) {
    int gain;
    if (receiver->get_HP_max() - receiver->HP >= 30) {gain = 30;}
    else {gain = receiver->get_HP_max() - receiver->HP;}
    receiver->HP += gain;
    return (receiver->get_name() + "'s HP increases by "+ std::to_string(gain) + "!");
}
