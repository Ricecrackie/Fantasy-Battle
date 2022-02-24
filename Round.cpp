#include "Round.h"
#include "Action/Action.h"
#include "Character/Character.h"
#include "Item/Item.h"

// call constructor to create a Round Object
Round::Round() {}

// adds an action to the list of added actions
bool Round::add_action(Action* action) {
    if (action->doer->AP < action->get_action_APcost()) return false;
    if (action->get_type() == Action::type::USE_A_SKILL) {
        if (action->doer->MP < action->get_skill()->get_MP_cost()) return false;
    }
    for (int i = 0; i < action_list.size(); ++i) {
        if (action_list[i]->get_type() == Action::type::USE_AN_ITEM) {
            if (action_list[i]->get_item() == action->get_item()) { // if the passed item already exists in action list, return false.
                return false;
            }
        }
    }
    if (action_list.size() == 0) {
        action_list.resize(1);
        action_list[0] = action;
    }
    else {action_list.push_back(action);}
    action->doer->AP -= action->get_action_APcost();
    return true;
}

// deletes an action on the list of added actions
bool Round::delete_action(Action* action) {
    if (action == nullptr) return false;
    for (int i = 0; i < action_list.size(); ++i) {
        if (action_list[i] == action) {
            action->doer->AP += action->get_action_APcost();
            delete action;
            action_list.erase(action_list.begin()+i);
            return true;
        }
    }
    return false;
}

// swaps two actions on the list of added actions
bool Round::swap_action(Action* action1, Action* action2) {
    if (action1 == action2) return false;
    if (action_list.size() <= 1) return false;
    int position1 = -1; // initial value for not found.
    int position2 = -1;
    for (int i = 0; i < action_list.size(); ++i) {
        if (action_list[i] == action1) {position1 = i;}
        if (action_list[i] == action2) {position2 = i;}
    }
    if (position1 == -1 || position2 == -1) return false;
    else {
        Action* temp = new Action(*action1);
        iter_swap(action_list.begin()+position1, action_list.begin()+position2);
        return true;
    }
}

// returns the list of actions
std::vector<Action*> Round::get_action_list() {return action_list;}

// view the action name
std::string Round::view_action() {
    std::string s = "";
    for (int i = 0; i < action_list.size(); ++i) {
        s = s + std::to_string(i+1) + ". " + action_list[i]->get_action_name() + "\n";
    }
    return s;
}

// executes the action with a chance of power_up
std::string Round::action_doer_process(Action* action, double power_up) {
    if (action == nullptr) return "";
    action->doer_effect(power_up);
    std::string s;
    if (power_up != 0) s += "Random Power up!\n";
    if (action->get_type() == Action::type::USE_A_SKILL) {s += action->doer->get_name() + " uses " + action->get_skill()->get_name() + "!";}
    if (action->get_type() == Action::type::USE_AN_ITEM) {s += action->doer->get_name() + " uses " + action->get_item()->get_item_name() + "!";}
    return s;
}

// default destructor
Round::~Round() {}

// receives the action with a chance of power_up
std::string Round::action_receiver_process(Action* action, double power_up) {
    if (action == nullptr) return "";
    int receiver_original_HP = action->receiver->HP;
    int receiver_original_MP = action->receiver->MP;
    int receiver_original_ATK = action->receiver->ATK;
    int receiver_original_DEF = action->receiver->DEF;
    int doer_original_HP = action->doer->HP;
    int doer_original_MP = action->doer->MP;
    int doer_original_ATK = action->doer->ATK;
    int doer_original_DEF = action->doer->DEF;
    action->receiver_effect(power_up); // process the actions
    int doer_HP_diff = action->doer->HP - doer_original_HP;
    int doer_MP_diff = action->doer->MP - doer_original_MP;
    int doer_ATK_diff = action->doer->ATK - doer_original_ATK;
    int doer_DEF_diff = action->doer->DEF - doer_original_DEF;    
    int receiver_HP_diff = action->receiver->HP - receiver_original_HP;
    int receiver_MP_diff = action->receiver->MP - receiver_original_MP;
    int receiver_ATK_diff = action->receiver->ATK - receiver_original_ATK;
    int receiver_DEF_diff = action->receiver->DEF - receiver_original_DEF;
    int doer_diff[4] = {doer_HP_diff, doer_MP_diff, doer_ATK_diff, doer_DEF_diff};
    int receiver_diff[4] = {receiver_HP_diff, receiver_MP_diff, receiver_ATK_diff, receiver_DEF_diff};
    std::string str[4] = {"HP", "MP", "ATK", "DEF"};
    std::string s = "";
    for (int i = 0; i < 4; ++i) {
        if (receiver_diff[i] == 0) continue;
        if (receiver_diff[i] > 0) {
            s += action->receiver->get_name() + "'s " + str[i] + " increases by " + std::to_string(receiver_diff[i]) + "!";
        }
        if (receiver_diff[i] < 0) {
            s += action->receiver->get_name() + "'s " + str[i] + " decreases by " + std::to_string(-receiver_diff[i]) + "!";
        }
        s += "\n";
    }
    if (action->receiver != action->doer) {
        for (int i = 0; i < 4; ++i) {
            if (doer_diff[i] == 0) continue;
            if (doer_diff[i] > 0) {
                s += action->doer->get_name() + "'s " + str[i] + " increases by " + std::to_string(doer_diff[i]) + "!";
            }
            if (doer_diff[i] < 0) {
                s += action->doer->get_name() + "'s " + str[i] + " decreases by " + std::to_string(-doer_diff[i]) + "!";
            }
            s += "\n";
        }
    }
    return s;
}
