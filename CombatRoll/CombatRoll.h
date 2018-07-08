#ifndef COMBATROLL_H
#define COMBATROLL_H

#include <stdlib.h>
#include <math.h>
#include <QMap>
#include "AttackResult.h"

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

    int get_melee_hit_result(const int, const float = 0.0);
    int get_melee_ability_result(const int,
                                 const float = 0.0,
                                 const bool include_dodge = true,
                                 const bool include_parry = true,
                                 const bool include_block = true,
                                 const bool include_miss = true);
    int get_ranged_hit_result(const int);
    int get_ranged_ability_result(const int);
    int get_spell_ability_result(void);

    WhiteHitTable* get_white_hit_table(const int);
    MeleeSpecialTable* get_melee_special_table(const int);
    void set_target(Target*);
    void set_character(Character*);

    Target* get_target() const;

    float get_white_miss_chance(const int);
    float get_yellow_miss_chance(const int wpn_skill);
    float get_glancing_blow_chance();
    float get_glancing_blow_dmg_penalty(const int);

    void update_crit_chance(const float critical);
    void update_miss_chance(const float hit);

    void dump_tables();
    void drop_tables();

    void set_new_seed(const QString& seed_str);

protected:
private:
    Character* pchar;
    Target* target;
    Random* random;
    Mechanics* mechanics;

    QMap<int, WhiteHitTable*> auto_attack_tables;
    QMap<int, MeleeSpecialTable*> melee_special_tables;
};


#endif // COMBATROLL_H
