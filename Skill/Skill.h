/*
 *  This class function is used to generate an Skill Object with virtual functions
 *  set up functions for overloading in derived classes. It is a derived class of Action.
*/

#ifndef SKILL_H
#define SKILL_H
#include <string>

class Character;
class Skill { // This is an abstract base class.
public:
    enum class skill_type {
        REGULAR_ATTACK = 1,
        DEFENCE = 2,
        STRENGTHEN = 3,
        SHARP_ATTACK = 4,
        BLESSING = 5, // player-owned skill
        BLOOD_SUCKING = 6,
        ULTIMATE_STRIKE = 7,
        GREATER_DEFENCE = 8,
        GREATER_STRENGTHEN = 9,
        CURSING = 10 // boss-owned skill
    };
    Skill(const int& AP_cost, const int& MP_cost, const int& unlock_level, const std::string& name, const int& rounds_of_effect);
    virtual void doer_effect(Character* doer, double power_up) = 0;
    virtual void receiver_effect(Character* receiver, Character* doer, double power_up) = 0;
    virtual std::string get_description() = 0;
    int get_AP_cost();
    int get_MP_cost();
    virtual std::string continuous_effect(Character* receiver, Character* doer) = 0;
    std::string get_name();
    int get_unlock_level();
    int rounds_of_effect;
    virtual std::string undo_effect() = 0;
    virtual Skill::skill_type get_skill_type() = 0;
private:
    int AP_cost;
    int MP_cost;
    std::string name;
    int unlock_level;
};
#endif
