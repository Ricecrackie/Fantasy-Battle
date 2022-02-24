#include "Action.h"
#include "../Skill/Regular_attack.h"
#include "../Skill/Defence.h"
#include "../Skill/Blessing.h"
#include "../Skill/Blood_sucking.h"
#include "../Skill/Cursing.h"
#include "../Skill/Greater_defence.h"
#include "../Skill/Greater_strengthen.h"
#include "../Skill/Sharp_attack.h"
#include "../Skill/Strengthen.h"
#include "../Skill/Ultimate_strike.h"
#include "../Item/HPpotion.h"
#include "../Item/MPpotion.h"

int use_item_APcost = 2;

// call constructor to create an Action Object (depending on the action is skill or item)
Action::Action(Character* doer, Character* receiver, Skill* skill) : doer(doer), receiver(receiver), skill(skill), item(nullptr), action_type(type::USE_A_SKILL) {}
Action::Action(Character* doer, Character* receiver, Item* item) : doer(doer), receiver(receiver), skill(nullptr), action_type(type::USE_AN_ITEM) {
    switch(item->get_item_type()) {
        case Item::item_type::HP_POTION:
            this->item = new HPpotion;
            break;
        case Item::item_type::MP_POTION:
            this->item = new MPpotion;
            break;
    }
}
Action::Action(Character* doer) : doer(doer), receiver(nullptr), skill(nullptr), item(nullptr), action_type(type::FLEE) {}

// returns the AP cost of the action
int Action::get_action_APcost() {
    if (skill != nullptr) return skill->get_AP_cost();
    if (item != nullptr) return use_item_APcost;
    else return 0;
}

// returns the MP cost of the action
int Action::get_action_MPcost() {
    if (skill != nullptr) return skill->get_MP_cost();
    if (item != nullptr) return 0;
    else return 0;
}

// returns the pointers or type called by the code
Skill* Action::get_skill() {return skill;}
Item* Action::get_item() {return item;}
Action::type Action::get_type() {return action_type;}

// destricutor to delete the contents pointed by the item pointer
Action::~Action() {
    if (item != nullptr) {
        delete item;
    }
}

// return the name of the action
std::string Action::get_action_name() {
    if (skill != nullptr) {return "use "+skill->get_name()+" on "+receiver->get_name();}
    if (item != nullptr) {return "use a "+item->get_item_name()+" on "+receiver->get_name();}
    if (skill == nullptr && item == nullptr) {return "flee";}
    return "";
}

// operator overloading to return if true or false
bool Action::operator==(Action& action) {
    return (this->skill == action.skill && this->item == action.item && this->action_type == action.action_type && this->doer == action.doer
    && this->receiver == action.receiver);
}

// call constructor to create an Action Object
Action::Action(Action& action) {
    this->doer = action.doer;
    this->receiver = action.receiver;
    this->skill = action.get_skill();
    /*switch(action.get_skill()->get_skill_type()) {
        case Skill::skill_type::REGULAR_ATTACK:
            this->skill = new Regular_attack;
            break;
        case Skill::skill_type::DEFENCE:
            this->skill = new Defence(receiver);
            break;
        case Skill::skill_type::STRENGTHEN:
            this->skill = new Strengthen(receiver);
            break;
        case Skill::skill_type::SHARP_ATTACK:
            this->skill = new Sharp_attack;
            break;
        case Skill::skill_type::BLESSING:
            this->skill = new Blessing(receiver);
            break;
        case Skill::skill_type::CURSING:
            this->skill = new Cursing(receiver);
            break;
        case Skill::skill_type::ULTIMATE_STRIKE:
            this->skill = new Ultimate_strike;
            break;
        case Skill::skill_type::BLOOD_SUCKING:
            this->skill = new Blood_sucking;
            break;
        case Skill::skill_type::GREATER_DEFENCE:
            this->skill = new Greater_defence(receiver);
            break;
        case Skill::skill_type::GREATER_STRENGTHEN:
            this->skill = new Greater_strengthen(receiver);
            break;
    }*/
}

// executes the code for doer effect
void Action::doer_effect(double power_up) {
    if (skill != nullptr) {
        skill->doer_effect(doer, power_up); 
        attribute_outofbound_check();
    return;}
}

// checks if the attribute (e.g. HP and MP) is out of bound
void Action::attribute_outofbound_check() {
    if (doer->HP > doer->get_HP_max()) {doer->HP = doer->get_HP_max();}
    if (doer->MP > doer->get_MP_max()) {doer->MP = doer->get_MP_max();}
    if (doer->HP < 0) {doer->HP = 0;}
    if (doer->MP < 0) {doer->MP = 0;}
    if (receiver->HP > receiver->get_HP_max()) {receiver->HP = receiver->get_HP_max();}
    if (receiver->MP > receiver->get_MP_max()) {receiver->MP = receiver->get_MP_max();}
    if (receiver->HP < 0) {receiver->HP = 0;}
    if (receiver->MP < 0) {receiver->MP = 0;}
}

// executes the code for the receiver effect
void Action::receiver_effect(double power_up) {
    if (skill != nullptr) {skill->receiver_effect(receiver, doer, power_up);}
    if (item != nullptr) {item->receiver_effect(*receiver, power_up);}
    attribute_outofbound_check();
    return;
}
