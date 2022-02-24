#include "Boss.h"
#include "../Skill/Regular_attack.h"
#include "../Skill/Defence.h"
#include "../Skill/Sharp_attack.h"
#include "../Skill/Strengthen.h"
#include "../Skill/Cursing.h"
#include "../Skill/Blood_sucking.h"
#include "../Skill/Greater_defence.h"
#include "../Skill/Greater_strengthen.h"
#include "../Skill/Ultimate_strike.h"

// call constructor to create a Boss Object using default values
Boss::Boss() : Enemy(BossHPmax, BossHPmax,
BossMPmax, BossMPmax, BossAPmax, BossAPmax, BossATK, BossDEF
, BossMoney, BossEXP) {
    Skill** learned_skill = new Skill*[9];
    learned_skill[0] = new Regular_attack();
    learned_skill[1] = new Defence(this);
    learned_skill[2] = new Strengthen(this);
    learned_skill[3] = new Sharp_attack;
    learned_skill[4] = new Cursing(this);
    learned_skill[5] = new Blood_sucking;
    learned_skill[6] = new Ultimate_strike;
    learned_skill[7] = new Greater_defence(this);
    learned_skill[8] = new Greater_strengthen(this);
    this->Character::learned_skill = learned_skill;
}

// call constructor to create a Boss Object by passing HP and MP values to the constructor
Boss::Boss(const int& HP, const int& MP) : Enemy(HP, BossHPmax, MP, BossMPmax,
BossAPmax, BossAPmax, BossATK, BossDEF, BossMoney, BossEXP) {
    Skill** learned_skill = new Skill*[9];
    learned_skill[0] = new Regular_attack();
    learned_skill[1] = new Defence(this);
    learned_skill[2] = new Strengthen(this);
    learned_skill[3] = new Sharp_attack;
    learned_skill[4] = new Cursing(this);
    learned_skill[5] = new Blood_sucking;
    learned_skill[6] = new Ultimate_strike;
    learned_skill[7] = new Greater_defence(this);
    learned_skill[8] = new Greater_strengthen(this);
    this->Character::learned_skill = learned_skill;
}

// calls constructor and stores the Boss in Enemy
Boss::Boss(Boss& boss) : Enemy(boss) {}

// return the type of the Boss
Enemy::enemy_type Boss::get_type() {return Enemy::enemy_type::Boss;}

// return the name of the Boss
std::string Boss::get_name() {return BossName;}
