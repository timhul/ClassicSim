#ifndef COMBATROLL_H
#define COMBATROLL_H

#include <QMap>
#include <math.h>
#include <stdlib.h>

#include "MagicSchools.h"

class Character;
class MagicAttackTable;
class Mechanics;
class MeleeSpecialTable;
class MeleeWhiteHitTable;
class Random;
class RangedWhiteHitTable;
class Target;

class CombatRoll {
public:
    CombatRoll(Character* pchar);
    ~CombatRoll();

    int get_melee_hit_result(const int wpn_skill, const unsigned crit_mod);
    int get_melee_ability_result(const int wpn_skill,
                                 const unsigned crit_mod,
                                 const bool include_dodge = true,
                                 const bool include_parry = true,
                                 const bool include_block = true,
                                 const bool include_miss = true);
    int get_ranged_hit_result(const int wpn_skill, const unsigned crit_chance);
    int get_ranged_ability_result(const int wpn_skill, const unsigned crit_chance);
    int get_spell_ability_result(const MagicSchool, const unsigned);
    int get_spell_resist_result(const MagicSchool);
    int get_pet_hit_result(const int wpn_skill, const unsigned crit_mod);
    int get_pet_ability_result(const int wpn_skill, const unsigned crit_mod);

    MeleeWhiteHitTable* get_melee_white_table(const int);
    MeleeSpecialTable* get_melee_special_table(const int);
    RangedWhiteHitTable* get_ranged_white_table(const int);
    MagicAttackTable* get_magic_attack_table(const MagicSchool);
    MeleeWhiteHitTable* get_pet_white_table(const int wpn_skill);
    MeleeSpecialTable* get_pet_ability_table(const int wpn_skill);

    Mechanics* get_mechanics() const;

    double get_white_miss_chance(const int);
    double get_yellow_miss_chance(const int wpn_skill);
    double get_glancing_blow_dmg_penalty(const int);

    void update_melee_miss_chance();
    void update_ranged_miss_chance();
    void update_spell_miss_chance(const unsigned spell_hit);

    void drop_tables();

    void set_new_seed(const unsigned seed);

private:
    Character* pchar;
    Target* target;
    Random* random;
    Mechanics* mechanics;

    QMap<int, MeleeWhiteHitTable*> melee_white_tables;
    QMap<int, MeleeSpecialTable*> melee_special_tables;
    QMap<int, RangedWhiteHitTable*> ranged_white_tables;
    QMap<MagicSchool, MagicAttackTable*> magic_attack_tables;
    QMap<int, MeleeWhiteHitTable*> pet_white_tables;
    QMap<int, MeleeSpecialTable*> pet_special_tables;

    unsigned get_suppressed_crit(const unsigned crit_chance) const;
};

#endif // COMBATROLL_H
