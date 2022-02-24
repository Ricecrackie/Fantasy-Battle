#include "Skill.h"

// call constructor to create a Skill Object by using passed values
Skill::Skill(const int& AP_cost, const int& MP_cost, const int& unlock_level, const std::string& name, 
const int& rounds_of_effect) : AP_cost(AP_cost), MP_cost(MP_cost), unlock_level(unlock_level),
name(name), rounds_of_effect(rounds_of_effect) {}

// returns the values called by the function
int Skill::get_AP_cost() {return AP_cost;}
int Skill::get_MP_cost() {return MP_cost;}
std::string Skill::get_name() {return name;}
int Skill::get_unlock_level() {return unlock_level;}
