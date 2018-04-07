#ifndef COMBATROLL_H
#define COMBATROLL_H

#include <stdlib.h>
#include <math.h>
#include <map>

class AttackResult;
class Character;
class Target;
class Random;
class WhiteHitTable;
class MeleeSpecialTable;
class Mechanics;

class CombatRoll {
public:
    CombatRoll(Target* _tar);
    ~CombatRoll();

    AttackResult* get_melee_hit_result(const int);
    AttackResult* get_melee_ability_result(const int);
    AttackResult* get_ranged_hit_result(const int);
    AttackResult* get_ranged_ability_result(const int);
    AttackResult* get_spell_ability_result(void);

    WhiteHitTable* get_white_hit_table(const int);
    MeleeSpecialTable* get_melee_special_table(const int);
    void set_target(Target*);
    void set_character(Character*);

    float get_white_miss_chance(const int);
    float get_glancing_blow_chance();
    float get_glancing_blow_dmg_penalty(const int);

protected:
private:
    Character* pchar;
    Target* target;
    Random* random;
    Mechanics* mechanics;

    std::map<int, WhiteHitTable*> auto_attack_tables;
    std::map<int, MeleeSpecialTable*> melee_special_tables;
};


#endif // COMBATROLL_H
