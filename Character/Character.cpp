#include "Character.h"
#include <iostream>
using namespace std;

// call constructor to create a Character Object with passed values
Character::Character(const int& HP, const int& HP_max, const int& MP, const int& MP_max,
              const int& AP, const int& AP_max, const int& ATK, const int& DEF, const int& money, const int& EXP) : HP(HP),
              HP_max(HP_max), MP(MP), MP_max(MP_max), AP(AP), AP_max(AP_max), ATK(ATK), DEF(DEF), money(money), EXP(EXP) {
                  
              }
Character::Character(Character& character) : HP(character.HP), HP_max(character.get_HP_max()), MP(character.MP), MP_max(character.get_MP_max()),
AP(character.AP), AP_max(character.get_AP_max()), ATK(character.ATK), DEF(character.DEF), money(character.money), EXP(character.EXP) {
}
void Character::set_AP_max(int AP_max) {this->AP_max = AP_max;}
void Character::set_HP_max(int HP_max) {this->HP_max = HP_max;}
void Character::set_MP_max(int MP_max) {this->MP_max = MP_max;}
int Character::get_HP_max() {return HP_max;}
int Character::get_MP_max() {return MP_max;}
int Character::get_AP_max() {return AP_max;}
