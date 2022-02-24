/*
 *  This class function is used to generate a Floor Object with an Enemy object.
 *  The Floor object is used to check the number of enemies, the value of money
 *  and EXP gained by the player, and the clear status of the current floor.
*/

#ifndef FLOOR_H
#define FLOOR_H
#include "ListTemplate.h"
#include "Character/Player.h"
#include "Character/Enemy.h"


class Enemy;
class Floor {
public:
    Floor();
    Floor(Enemy** enemies, int number_of_enemy);
    int get_number_of_WeakEnemy() const;
    int get_number_of_StrongEnemy() const;
    int get_number_of_boss() const;
    int get_number_of_enemy() const;
    int get_enemy_HP();
    int get_money_gain() const;
    int get_EXP_gain() const;
    bool isClear() const;
    Enemy** get_enemy() const;
private:
    List<Enemy*> enemies; 
    Enemy** enemies_pointer;
};
#endif
