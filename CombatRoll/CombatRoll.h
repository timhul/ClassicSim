#ifndef COMBATROLL_H
#define COMBATROLL_H

#include <stdlib.h>
#include <math.h>
#include <map>

#include "Character.h"
#include "AttackResult.h"
#include "AttackTable.h"
#include "WhiteHitTable.h"
#include "MeleeSpecialTable.h"
#include "Target.h"
#include "Random.h"

class CombatRoll {
public:
    CombatRoll(Target* _tar, Random* _rand):
        target(_tar), random(_rand) {}

    ~CombatRoll() {
        auto_attack_tables.clear();
        melee_special_tables.clear();
    }  
    AttackResult* get_melee_hit_result(const int);
    AttackResult* get_melee_ability_result(const int);
    AttackResult* get_ranged_hit_result(const int);
    AttackResult* get_ranged_ability_result(const int);
    AttackResult* get_spell_ability_result(void);

    WhiteHitTable* get_white_hit_table(const int);
    MeleeSpecialTable* get_melee_special_table(const int);
    void set_target(Target*);
    void set_character(Character*);

    float get_yellow_miss_chance(const int) const;
    float get_white_miss_chance(const int) const;
    float get_white_miss_chance_defense_diff_low(const int) const;
    float get_white_miss_chance_defense_diff_high(const int) const;

    float get_glancing_blow_chance(void) const;
    float get_dodge_chance(const int) const;
    float get_parry_chance(const int) const;
    float get_block_chance(void) const;

protected:
private:
    Character* pchar;
    Target* target;
    Random* random;

    std::map<int, WhiteHitTable*> auto_attack_tables;
    std::map<int, MeleeSpecialTable*> melee_special_tables;
};


#endif // COMBATROLL_H
