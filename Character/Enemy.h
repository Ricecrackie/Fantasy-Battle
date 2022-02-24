/*
 *  This class function is used to generate a Enemy Object. It contains virutual
 *  functions for derived classes such as WeakEnemy to overload. It is a derived
 *  class of Character.
*/

#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"
class Enemy : public Character { // ABC
public:
    enum class enemy_type {
        WeakEnemy = 1,
        StrongEnemy = 2,
        Boss = 3
    };
    Enemy(const int& HP, const int& HP_max, const int& MP, const int& MP_max,
          const int& AP, const int& AP_max, const int& ATK, const int& DEF, const int& money, const int& EXP);
    Enemy(Enemy& enemy);
    virtual Enemy::enemy_type get_type() = 0;
    std::string info();
    virtual std::string get_name() = 0;
};
#endif
