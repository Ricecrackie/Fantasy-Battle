#include "WeakEnemy.h"
#include "../Skill/Regular_attack.h"
#include "../Skill/Defence.h"
#include "../Skill/Strengthen.h"

// call constructor to create a WeakEnemy Object using default values
WeakEnemy::WeakEnemy() : Enemy(WeakEnemyHPmax, WeakEnemyHPmax,
WeakEnemyMPmax, WeakEnemyMPmax, WeakEnemyAPmax, WeakEnemyAPmax, WeakEnemyATK, WeakEnemyDEF
, WeakEnemyMoney, WeakEnemyEXP) {
    Skill** learned_skill = new Skill*[2];
    learned_skill[0] = new Regular_attack();
    learned_skill[1] = new Defence(this);
    this->Character::learned_skill = learned_skill;
}

// call constructor to create a WeakEnemy Object by passing HP and MP values to the constructor
WeakEnemy::WeakEnemy(const int& HP, const int& MP) : Enemy(HP, WeakEnemyHPmax, MP, WeakEnemyMPmax,
WeakEnemyAPmax, WeakEnemyAPmax, WeakEnemyATK, WeakEnemyDEF, WeakEnemyMoney, WeakEnemyEXP) {
    Skill** learned_skill = new Skill*[2];
    learned_skill[0] = new Regular_attack();
    learned_skill[1] = new Defence(this);
    this->Character::learned_skill = learned_skill;
}

// calls constructor and stores the WeakEnemy in Enemy
WeakEnemy::WeakEnemy(Enemy& WeakEnemy) : Enemy(WeakEnemy) {}

// return the type of the WeakEnemy
Enemy::enemy_type WeakEnemy::get_type() {return Enemy::enemy_type::WeakEnemy;}

// return the name of the WeakEnemy
std::string WeakEnemy::get_name() {return WeakEnemyName;}
