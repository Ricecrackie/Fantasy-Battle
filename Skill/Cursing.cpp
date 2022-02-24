#include "Cursing.h"
#include "../Character/Character.h"

// call constructor to create a Cursing Object by passing the receiver of the action to the constructor
Cursing::Cursing(Character* receiver) : Skill(Cursing_AP_cost, Cursing_MP_cost, Cursing_unlock_level, Cursing_name, Cursing_rounds_of_effect)
, receiver(receiver) {}

// executes the effect of the action
void Cursing::receiver_effect(Character* receiver, Character* doer, double power_up) {
    loss = 10+2*power_up;
    receiver->ATK -= loss;
    receiver->DEF -= loss;
}

// decrease the doer's AP and MP by the action cost
void Cursing::doer_effect(Character* doer, double power_up) {
    doer->AP -= Cursing_AP_cost;
    doer->MP -= Cursing_MP_cost;
}

// return the description of the action
std::string Cursing::get_description() {
    return Cursing_description;
}

// undo the action's effects
std::string Cursing::undo_effect() {
    receiver->ATK += loss;
    receiver->DEF += loss;
    return (receiver->get_name() + "'s ATK increases by " + std::to_string(loss) + "!" + "\n"
    + receiver->get_name() + "'s DEF increases by " + std::to_string(loss) + "!");
}

// continues the effects of the action
std::string Cursing::continuous_effect(Character* receiver, Character* doer) {
    int loss;
    if (receiver->HP >= 40) {loss = 40;}
    else {loss = receiver->HP;}
    receiver->HP -= loss;
    return (receiver->get_name() + "'s HP decreases by "+ std::to_string(loss) + "!");
}

// returns the skill type
Skill::skill_type Cursing::get_skill_type() {return Skill::skill_type::CURSING;}
