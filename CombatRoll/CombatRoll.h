#ifndef COMBATROLL_H
#define COMBATROLL_H

#include <QMap>
#include <stdlib.h>
#include <math.h>

#include "MagicSchools.h"

class Character;
class MagicAttackTable;
class MeleeSpecialTable;
class Mechanics;
class Target;
class Random;
class WhiteHitTable;

class CombatRoll {
public:
    CombatRoll(Character* pchar);
    ~CombatRoll();

    int get_melee_hit_result(const int, const double);
    int get_melee_ability_result(const int,
                                 const double,
                                 const bool include_dodge = true,
                                 const bool include_parry = true,
                                 const bool include_block = true,
                                 const bool include_miss = true);
    int get_ranged_hit_result(const int);
    int get_ranged_ability_result(const int);
    int get_spell_ability_result(const MagicSchool, const double);
    int get_spell_resist_result(const MagicSchool);

    WhiteHitTable* get_white_hit_table(const int);
    MeleeSpecialTable* get_melee_special_table(const int);
    MagicAttackTable* get_magic_attack_table(const MagicSchool);

    Mechanics* get_mechanics() const;

    double get_white_miss_chance(const int);
    double get_yellow_miss_chance(const int wpn_skill);
    double get_glancing_blow_dmg_penalty(const int);

    void update_miss_chance(const double hit);
    void update_spell_miss_chance(const double spell_hit);

    void dump_tables();
    void drop_tables();

    void set_new_seed(const unsigned seed);

private:
    Character* pchar;
    Target* target;
    Random* random;
    Mechanics* mechanics;

    QMap<int, WhiteHitTable*> auto_attack_tables;
    QMap<int, MeleeSpecialTable*> melee_special_tables;
    QMap<MagicSchool, MagicAttackTable*> magic_attack_tables;
};

#endif // COMBATROLL_H
