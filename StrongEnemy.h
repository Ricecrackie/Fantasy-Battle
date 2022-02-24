/*
 *  This class function is used to generate a StrongEnemy Object with functions to
 *  determine the type of the enemy. It is a derived class of Enemy.
*/

#ifndef STRONGENEMY_H
#define STRONGENEMY_H

#include "Enemy.h"

const int StrongEnemyHPmax = 500;
const int StrongEnemyMPmax = 500;
const int StrongEnemyAPmax = 10;
const int StrongEnemyATK = 15;
const int StrongEnemyDEF = 15;
const int StrongEnemyMoney = 100;
const int StrongEnemyEXP = 50;
const std::string StrongEnemyName = "StrongEnemy";

class StrongEnemy : public Enemy {
public:
    StrongEnemy();
    StrongEnemy(const int& HP, const int& MP);
    enemy_type get_type();
    std::string get_name();
};
#endif
