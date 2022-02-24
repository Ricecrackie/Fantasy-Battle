/*
 *  This class function is used to generate a WeakEnemy Object with functions to
 *  determine the type of the enemy. It is a derived class of Enemy.
*/

#ifndef WEAKENEMY_H
#define WEAKENEMY_H

#include "Enemy.h"

const int WeakEnemyHPmax = 100;
const int WeakEnemyMPmax = 100;
const int WeakEnemyAPmax = 10;
const int WeakEnemyATK = 5;
const int WeakEnemyDEF = 5;
const int WeakEnemyMoney = 50;
const int WeakEnemyEXP = 20;
const std::string WeakEnemyName = "WeakEnemy";

class WeakEnemy : public Enemy {
public:
    WeakEnemy();
    WeakEnemy(const int& HP, const int& MP);
    WeakEnemy(Enemy& WeakEnemy);
    enemy_type get_type();
    std::string get_name();
};
#endif
