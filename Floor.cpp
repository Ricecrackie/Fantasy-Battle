#include "Floor.h"
#include "Character/Enemy.h"

// call constructor to create a Floor Object by passing the enemies to the constructor
Floor::Floor(Enemy** enemies, int number_of_enemy) : enemies_pointer(enemies) {
    for (int i = 0; i < number_of_enemy; ++i) {
        this->enemies.append(enemies[i]);
    }
}

// return the enemy's pointer
Enemy** Floor::get_enemy() const {return enemies_pointer;}

// call constructor to create a Floor Object without any enemies
Floor::Floor() : enemies_pointer(nullptr) {}

// return the enemy's HP
int Floor::get_enemy_HP() {
    int HP = 0;
    for (ListNode<Enemy*>* p = enemies.head; p != nullptr; p = p->next) {
        HP += p->data->HP;
    }
    return HP;
}

// return the number of WeakEnemy on the current Floor
int Floor::get_number_of_WeakEnemy() const {
    if (enemies.head == nullptr) return 0;
    int number = 0;
    for (ListNode<Enemy*>* p = enemies.head; p != nullptr; p = p->next) {
        if (p->data->get_type() == Enemy::enemy_type::WeakEnemy) {
            ++number;
        }
    }
    return number;
}

// return the number of StrongEnemy on the current Floor
int Floor::get_number_of_StrongEnemy() const {
    if (enemies.head == nullptr) return 0;
    int number = 0;
    for (ListNode<Enemy*>* p = enemies.head; p != nullptr; p = p->next) {
        if (p->data->get_type() == Enemy::enemy_type::StrongEnemy) {
            ++number;
        }
    }
    return number;
}

// return the number of Boss on the current Floor
int Floor::get_number_of_boss() const {
    if (enemies.head == nullptr) return 0;
    int number = 0;
    for (ListNode<Enemy*>* p = enemies.head; p != nullptr; p = p->next) {
        if (p->data->get_type() == Enemy::enemy_type::Boss) {
            ++number;
        }
    }
    return number;
}

// return the number of enemies on the current Floor
int Floor::get_number_of_enemy() const {
    return get_number_of_WeakEnemy()+get_number_of_StrongEnemy()+get_number_of_boss();
}

// checks if the floor is cleared (all enemies are defeated)
bool Floor::isClear() const {
    for (ListNode<Enemy*>* p = enemies.head; p != nullptr; p = p->next) {
        if (p->data->HP != 0) {
            return false;
        }
    }
    return true;
}

// return the amount of money the player receives after finishing the floor
int Floor::get_money_gain() const {
    int money = 0;
    for (ListNode<Enemy*>* p = enemies.head; p != nullptr; p = p->next) {
        money += p->data->money;
    }
    return money;
}

// return the amount of EXP the player receives after finishing the floor
int Floor::get_EXP_gain() const {
    int exp = 0;
    for (ListNode<Enemy*>* p = enemies.head; p != nullptr; p = p->next) {
        exp += p->data->EXP;
    }
    return exp;
}
