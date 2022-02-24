#include "Battle.h"
#include "Tower.h"
#include "Character/Boss.h"
#include "Character/StrongEnemy.h"
#include "Character/WeakEnemy.h"
#include <random>
#include "QRandomGenerator"

extern int random_number(const int&, const int&);
extern const int BossATK;
extern const int BossDEF;
extern const int StrongEnemyATK;
extern const int StrongEnemyDEF;
extern const int WeakEnemyATK;
extern const int WeakEnemyDEF;

// generates a random power up
int random_power_up(const int begin, const int end) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(begin,end);
    return dist6(rng);
}

// call constructor to create a Battle Object by passing the player and enemy objects to the constructor
Battle::Battle(Character* player, Enemy** enemy) : player(player), playerOriginalATK(player->ATK), playerOriginalDEF(player->DEF) {
    Player* play = dynamic_cast<Player*>(player);
    int num_of_enemy = play->tower.get_floors()[play->tower.get_current_floor_index()].get_number_of_enemy();
    this->enemy = enemy;
    current_round = new Round();
}

// returns the character's status
std::string Battle::view_status(Character& chara) const {
    return chara.info();
}

// returns the values called by the function
bool Battle::get_isPlayerWin() const {return isPlayerWin;}
bool Battle::get_isPlayerLose() const {return isPlayerLose;}
Round*& Battle::get_current_round() {return current_round;}
int Battle::get_round_counter() const {return round_counter;}
Enemy** Battle::get_enemy() const {return enemy;}

// Check if the player has defeated all the enemies or lost all their health
bool Battle::isSomebodyWin() {
    Player* temp = dynamic_cast<Player*>(player);
    if (player->HP == 0) {
        isPlayerLose = true;
        return true;
    }
    else if (temp->tower.get_floors()[temp->tower.get_current_floor_index()].get_enemy_HP() == 0) {
        isPlayerWin = true;
        return true;
    }
    else {
        return false;
    }
}

// Battle proceeds to the next round and outputs the actions done on each turn
void Battle::go_to_next_round() { // The winning condition is always checked.
    player->AP = player->get_AP_max(); // Restore the AP of players & enemies.
    Player* play = dynamic_cast<Player*>(player);
    for (int i = 0; i < play->tower.get_floors()[play->tower.get_current_floor_index()].get_number_of_enemy(); ++i) {
        enemy[i]->AP = enemy[i]->get_AP_max();
    } //
    for (int i = 0; i < action_effect.size(); ++i) { // Execute post-action effect of skills from previous rounds.
        if (isSomebodyWin()) return;
        if (action_effect[i]->skill != nullptr) {
            std::string continuous_effect = action_effect[i]->skill->continuous_effect(action_effect[i]->receiver, action_effect[i]->doer);
            if (continuous_effect != "") {cout << continuous_effect << endl;}
            --action_effect_count[i];
        }
    } //
    if (isSomebodyWin()) return;
    cout << "Round " << round_counter << endl; // Execute and display actions in the current round's action list.
    for (int j = 0; j < current_round->action_list.size(); ++j) {
        if (isSomebodyWin()) return;
        int isPowerup = QRandomGenerator::global()->bounded(4);
        int PowerUp_index = QRandomGenerator::global()->bounded(1, 6);
        if (isPowerup != 3) {
            PowerUp_index = 0;
        }
        cout << current_round->action_doer_process(current_round->action_list[j], power_up[PowerUp_index]) << endl;
        cout << current_round->action_receiver_process(current_round->action_list[j], power_up[PowerUp_index]) << endl;
        if (current_round->action_list[j]->get_type() == Action::type::USE_A_SKILL) { // Add actions in action list to action effect list
            if (action_effect.size() != 0) {
                action_effect.push_back(current_round->action_list[j]);
                action_effect_count.push_back(current_round->action_list[j]->get_skill()->rounds_of_effect);
            }
            else {
                action_effect.resize(1);
                action_effect[0] = current_round->action_list[j];
                action_effect_count.resize(1);
                action_effect_count[0] = current_round->action_list[j]->get_skill()->rounds_of_effect;
            }
        }
    } //
    if (isSomebodyWin()) return;
    int i = 0;
    while (i < action_effect.size()) { // Clear actions that finish all post-action effect execution from the action effect list
        if (action_effect_count[i] == 0) {
            std::string undo = action_effect[i]->get_skill()->undo_effect();
            if (undo != "") {cout << undo << endl;}
            delete action_effect[i];
            action_effect.erase(action_effect.begin()+i);
            action_effect_count.erase(action_effect_count.begin()+i);
            continue;
        }
        else {
            ++i;
            continue;
        }
    }
    delete current_round;
    current_round = new Round;
    player->AP = player->get_AP_max();
    round_counter++;
}

// sets the status of Win or Lose
void Battle::setIsPlayerWin(bool isPlayerWin) {this->isPlayerWin = isPlayerWin;}
void Battle::setIsPlayerLose(bool isPlayerLose) {this->isPlayerLose = isPlayerLose;}

// returns the player pointer
Character* Battle::get_player() const{return player;}

// To determine whether the enemy would use buff skills like Strengthen or Defence. The chances are 20% (1/5).
bool useBuffSkill() {
    int temp = QRandomGenerator::global()->bounded(1, 6);
    if (temp == 1) return true;
    else return false;
}

// checks if the Enemy has enough MP to use the skill
bool Battle::isEnemyMPenough(Enemy* enemy, Skill* skill) {
    if (enemy->MP >= skill->get_MP_cost()) return true;
    else return false;
}

// generates a random action by the enemy
Action* Battle::enemy_random_action(Enemy* enemy) {
    int WeakEnemyBuffSkillIndices = 1;
    int WeakEnemyAttackSkillIndices = 0;
    int StrongEnemyBuffSkillIndices[2] = {1, 2};
    int StrongEnemyAttackSkillIndices[2] = {0, 3};
    int BossBuffSkillIndices[4] = {1, 2, 7, 8};
    int BossAttackSkillIndices[5] = {0, 3, 4, 5, 6};
    int pick;
    while (true) {
        switch (enemy->get_type()) {
            case Enemy::enemy_type::WeakEnemy:
                if (useBuffSkill()) {
                    if (isEnemyMPenough(enemy, enemy->learned_skill[WeakEnemyBuffSkillIndices]))
                    return new Action(enemy, enemy, enemy->learned_skill[WeakEnemyBuffSkillIndices]);
                    else break;
                }
                else {
                    return new Action(enemy, player, enemy->learned_skill[WeakEnemyAttackSkillIndices]);
                }
            case Enemy::enemy_type::StrongEnemy:
                if (useBuffSkill()) {
                    pick = QRandomGenerator::global()->bounded(2);
                    if (isEnemyMPenough(enemy, enemy->learned_skill[StrongEnemyBuffSkillIndices[pick]]))
                        return new Action(enemy, enemy, enemy->learned_skill[StrongEnemyBuffSkillIndices[pick]]);
                    else break;
                }
                else {
                    pick = QRandomGenerator::global()->bounded(2);
                    if (isEnemyMPenough(enemy, enemy->learned_skill[StrongEnemyAttackSkillIndices[pick]]))
                        return new Action(enemy, player, enemy->learned_skill[StrongEnemyAttackSkillIndices[pick]]);
                    else break;
                }
            case Enemy::enemy_type::Boss:
                if (useBuffSkill()) {
                    pick = QRandomGenerator::global()->bounded(4);
                    if (isEnemyMPenough(enemy, enemy->learned_skill[BossBuffSkillIndices[pick]]))
                        return new Action(enemy, enemy, enemy->learned_skill[BossBuffSkillIndices[pick]]);
                    else break;
                }
                else {
                    pick = QRandomGenerator::global()->bounded(5);
                    if (isEnemyMPenough(enemy, enemy->learned_skill[BossAttackSkillIndices[pick]]))
                        return new Action (enemy, player, enemy->learned_skill[BossAttackSkillIndices[pick]]);
                    else break;
                }
        }
    }
}

// generates the list of actions of the enemy
void Battle::generate_enemy_actionlist() {
    Enemy** enemies = dynamic_cast<Player*>(player)->tower.get_floors()[dynamic_cast<Player*>(player)->tower.get_current_floor_index()].get_enemy();
    for (int i = 0; i < dynamic_cast<Player*>(player)->tower.get_floors()[dynamic_cast<Player*>(player)->tower.get_current_floor_index()].get_number_of_enemy(); ++i) {
        if (enemies[i]->HP == 0) continue;
        Action* action = enemy_random_action(enemies[i]);
        if (current_round->action_list.size() == 0) {
            current_round->action_list.resize(1);
            current_round->action_list[0] = action;
        }
        else {
            current_round->action_list.push_back(action);
        }
    }
}

// destructor of Battle Object, deallocates the memory of current round and resets the values
Battle::~Battle() {
    player->ATK = playerOriginalATK;
    player->DEF = playerOriginalDEF;
    Player* play = dynamic_cast<Player*>(player);
    for (int i = 0; i < play->tower.get_floors()[play->tower.get_current_floor_index()].get_number_of_enemy(); ++i) {
        int ATK; int DEF;
        switch(static_cast<int>(play->tower.get_floors()[play->tower.get_current_floor_index()].get_enemy()[i]->get_type())) {
            case 1: ATK = WeakEnemyATK; DEF = WeakEnemyDEF; break;
            case 2: ATK = StrongEnemyATK; DEF = StrongEnemyDEF; break;
            case 3: ATK = BossATK; DEF = BossDEF; break;
        }
        play->tower.get_floors()[play->tower.get_current_floor_index()].get_enemy()[i]->ATK = ATK;
        play->tower.get_floors()[play->tower.get_current_floor_index()].get_enemy()[i]->DEF = DEF;
    }
    delete current_round;
}
