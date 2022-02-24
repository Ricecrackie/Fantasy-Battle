/*
 *  This class function is used to generate a Action Object with functions to
 *  determine the effects of the action by the player or the enemies. This is a
 *  base class for the Skills and the Items.
*/

#ifndef ACTION_H
#define ACTION_H
#include <string>
class Skill;
class Item;
class Character;
class Action {
public:
friend class Battle;
    enum class type {
        USE_A_SKILL, USE_AN_ITEM, FLEE
    };
    Action(Character* doer, Character* receiver, Skill* skill);
    Action(Character* doer, Character* receiver, Item* item);
    Action(Character* doer);
    Action(Action& action);
    ~Action();
    bool operator==(Action& action);
    int get_action_APcost();
    int get_action_MPcost();
    Skill* get_skill();
    Item* get_item();
    Action::type get_type();
    std::string get_action_name();
    void doer_effect(double power_up);
    void receiver_effect(double power_up);
    Character* doer;
    Character* receiver;
    void attribute_outofbound_check();
private:
    Skill* skill;
    Item* item;
    Action::type action_type;
};
#endif
