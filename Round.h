/*
 *  This class function is used to generate a Round Object with functions for
 *  for the current round such as adding actions, deleting action, swapping actions,
 *  executing the effects of the actions, as well as listing all the actions in a list.
*/

#ifndef ROUND_H
#define ROUND_H
#include <vector>
#include <algorithm>
#include <string>

class Character;
class Action;
class Enemy;
class Round {
friend class Battle;
public:
    Round();
    ~Round();
    bool add_action(Action* action);
    bool delete_action(Action* action);
    bool swap_action(Action* action1, Action* action2);
    std::string view_action();
    std::string action_doer_process(Action* action, double power_up);
    std::string action_receiver_process(Action* action, double power_up);
    Character** get_activeTeam() const;
    std::vector<Action*> get_action_list();
private:
    std::vector<Action*> action_list;
};
#endif
