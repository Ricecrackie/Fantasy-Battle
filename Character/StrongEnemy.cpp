#include "StrongEnemy.h"
#include "../Skill/Regular_attack.h"
#include "../Skill/Defence.h"
#include "../Skill/Strengthen.h"
#include "../Skill/Sharp_attack.h"

// call constructor to create a StrongEnemy Object using default values
StrongEnemy::StrongEnemy() : Enemy(StrongEnemyHPmax, StrongEnemyHPmax,
StrongEnemyMPmax, StrongEnemyMPmax, StrongEnemyAPmax, StrongEnemyAPmax, StrongEnemyATK, StrongEnemyDEF
, StrongEnemyMoney, StrongEnemyEXP) {
    Skill** learned_skill = new Skill*[4];
    learned_skill[0] = new Regular_attack();
    learned_skill[1] = new Defence(this);
    learned_skill[2] = new Strengthen(this);
    learned_skill[3] = new Sharp_attack;
    this->Character::learned_skill = learned_skill;
}

// call constructor to create a StrongEnemy Object by passing HP and MP values to the constructor
StrongEnemy::StrongEnemy(const int& HP, const int& MP) : Enemy(HP, StrongEnemyHPmax, MP, StrongEnemyMPmax,
StrongEnemyAPmax, StrongEnemyAPmax, StrongEnemyATK, StrongEnemyDEF, StrongEnemyMoney, StrongEnemyEXP) {
    Skill** learned_skill = new Skill*[4];
    learned_skill[0] = new Regular_attack();
    learned_skill[1] = new Defence(this);
    learned_skill[2] = new Strengthen(this);
    learned_skill[3] = new Sharp_attack;
    this->Character::learned_skill = learned_skill;
}

// return the type of the StrongEnemy
Enemy::enemy_type StrongEnemy::get_type() {return Enemy::enemy_type::StrongEnemy;}

// return the name of the StrongEnemy
std::string StrongEnemy::get_name() {return StrongEnemyName;}

