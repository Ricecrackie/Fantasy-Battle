#include "Regular_attack.h"
#include "../Character/Character.h"

// call constructor to create a Regular_attack Object by passing the receiver of the action to the constructor
Regular_attack::Regular_attack() : Skill(Regular_attack_AP_cost, Regular_attack_MP_cost, Regular_attack_unlock_level, 
Regular_attack_name, Regular_attack_rounds_of_effect) {};

// executes the effect of the action
void Regular_attack::receiver_effect(Character* receiver, Character* doer, double power_up) {
    int loss = doer->ATK*5 + 5*power_up - receiver->DEF*2;
    if (loss < 0) {loss = 0;}
    receiver->HP = receiver->HP - loss;
}

// decrease the doer's AP and MP by the action cost
void Regular_attack::doer_effect(Character* doer, double power_up) {
    doer->AP -= Regular_attack_AP_cost;
    doer->MP -= Regular_attack_MP_cost;
}

// return the description of the action
std::string Regular_attack::get_description() {
    return Regular_attack_description;
}

// undo the action's effects, returns the skill type, continues the effects of the action
std::string Regular_attack::undo_effect() {return "";}
Skill::skill_type Regular_attack::get_skill_type() {return Skill::skill_type::REGULAR_ATTACK;}
std::string Regular_attack::continuous_effect(Character* receiver, Character* doer) {return "";}
