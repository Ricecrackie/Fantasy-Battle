/*
 *  This class function is used to generate a Tower Object. The Tower object is the main
 *  class that connects all the other classes together. The Tower object is generated in
 *  the MenuWindow and determines how the game is played. It contains functions such as
 *  checking the current status of the tower and what happens during the battle.
*/

#ifndef TOWER_H
#define TOWER_H
#include "Character/Player.h"
#include "Character/WeakEnemy.h"
#include "Character/StrongEnemy.h"
#include "Character/Boss.h"
#include "Floor.h"
#include <string>
#include <vector>
class Tower {
public:
    enum class Difficulty {
        EASY = 1,
        NORMAL = 2,
        HARD = 3
    };
    Tower(Tower::Difficulty difficulty, const int& size);
    Tower(const std::string& filename);
    void save(const std::string &filename) const;
    bool move_to_next_floor();
    int get_tower_size() const;
    int get_current_floor_index() const;
    bool start_battle() const;
    bool isPlayerWin() const;
    bool isPlayerLose() const;
    int getNumOfEnemyinCurrentFloor() const;
    int getBattleRound() const;
    void enemyRound() const;
    int get_money_gain() const;
    int get_EXP_gain() const;
    void player_reward() const;
    void end_battle() const;
    std::string HPpotion_drop() const;
    std::string MPpotion_drop() const;
    std::string LeatherArmor_drop() const;
    std::string IronArmor_drop() const;
    std::string DiamondArmor_drop() const;
    bool level_up();
    std::vector<Floor> get_floors() const;
    Player* player;
private:
    Tower::Difficulty difficulty;
    int tower_size;
    int current_floor;
    std::vector<Floor> floors;
};
#endif
