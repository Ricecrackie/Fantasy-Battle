#include "Enemy.h"

// call constructor to create a Enemy Object with passed values
Enemy::Enemy(const int& HP, const int& HP_max, const int& MP, const int& MP_max,
             const int& AP, const int& AP_max, const int& ATK, const int& DEF, const int& money, const int& EXP) : 
             Character(HP, HP_max, MP, MP_max,
             AP, AP_max, ATK, DEF, money, EXP) {
             }
Enemy::Enemy(Enemy& enemy) : Character(enemy) {}

// returns the info of the enemy
std::string Enemy::info() {
    std::string s = "";
    s = "Name: " + get_name() + "\n"
    + "HP: " + std::to_string(HP) + "/" + std::to_string(get_HP_max()) + "\n"
    + "MP: " + std::to_string(MP) + "/" + std::to_string(get_MP_max()) + "\n"
    + "ATK: " + std::to_string(ATK) + "\n"
    + "DEF: " + std::to_string(DEF);
    return s;
}
