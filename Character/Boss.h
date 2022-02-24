/*
 *  This class function is used to generate a Boss Object with functions to
 *  determine the type of the enemy. It is a derived class of Enemy.
*/

#ifndef BOSS_H
#define BOSS_H
#include "Enemy.h"

const int BossHPmax = 5000;
const int BossMPmax = 500;
const int BossAPmax = 20;
const int BossATK = 20;
const int BossDEF = 20;
const int BossMoney = 500;
const int BossEXP = 500;
const std::string BossName = "Boss";

class Boss : public Enemy {
public:
    Boss();
    Boss(Boss& boss);
    Boss(const int& HP, const int& MP);
    enemy_type get_type();
    std::string get_name();
};
#endif
