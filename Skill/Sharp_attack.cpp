#include "Sharp_attack.h"
#include "../Character/Character.h"

// call constructor to create a Sharp_attack Object by passing the receiver of the action to the constructor
Sharp_attack::Sharp_attack() : Skill(Sharp_attack_AP_cost, Sharp_attack_MP_cost, Sharp_attack_unlock_level, 
Sharp_attack_name, Sharp_attack_rounds_of_effect) {};

// executes the effect of the action
void Sharp_attack::receiver_effect(Character* receiver, Character* doer, double power_up) {
    int loss = doer->ATK*5 - 5*power_up;
    if (loss < 0) {loss = 0;}
    receiver->HP = receiver->HP - loss;
}

// decrease the doer's AP and MP by the action cost
void Sharp_attack::doer_effect(Character* doer, double power_up) {
    doer->AP -= Sharp_attack_AP_cost;
    doer->MP -= Sharp_attack_MP_cost;
}

// return the description of the action
std::string Sharp_attack::get_description() {
    return Sharp_attack_description;
}

// undo the action's effects, returns the skill type, continues the effects of the action
std::string Sharp_attack::undo_effect() {return "";}
Skill::skill_type Sharp_attack::get_skill_type() {return Skill::skill_type::SHARP_ATTACK;}
std::string Sharp_attack::continuous_effect(Character* receiver, Character* doer) {return "";}
