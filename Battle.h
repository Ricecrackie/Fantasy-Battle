/*
 *  This class function is used to generate a Battle Object with functions for
 *  the battle such as checking if the battle is over, checking the stats of the
 *  enemy or the player, generate actions, and progress through different rounds.
*/

#ifndef BATTLE_H
#define BATTLE_H
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <iostream>
#include "Round.h"
#include "ListTemplate.h"
#include "Action/Action.h"
using namespace std;

class Battle {
public:
    Battle(Character* player, Enemy** enemy); // new battle
    ~Battle();
    std::string view_status(Character& chara) const;
    std::string battle_messages;
    void go_to_next_round();
    void generate_enemy_actionlist();
    void save_game(std::string filename);
    bool get_isPlayerWin() const;
    bool get_isPlayerLose() const;
    Round*& get_current_round();
    int get_round_counter() const;
    int get_enemy_HP();
    bool isSomebodyWin();
    Character* get_player() const;
    Enemy** get_enemy() const;
    void setIsPlayerWin(bool isPlayerWin);
    void setIsPlayerLose(bool isPlayerLose);
    int playerOriginalATK;
    int playerOriginalDEF;
    Action* enemy_random_action(Enemy* enemy);
    bool isEnemyMPenough(Enemy* enemy, Skill* skill);
private:
    int round_counter = 0;
    std::vector<Action*> action_effect;
    std::vector<int> action_effect_count;
    Round* current_round;
    Character* player;
    Enemy** enemy;
    bool isPlayerWin {false};
    bool isPlayerLose {false};
    double power_up[6] {0, 1.0, 1.5, 2, 2.5, 3};
};

#endif
