
#include "CombatRoll.h"
#include "Character.h"
#include "CharacterStats.h"
#include "Mechanics.h"
#include "AttackResult.h"
#include "AttackTable.h"
#include "WhiteHitTable.h"
#include "MeleeSpecialTable.h"
#include "Target.h"
#include "Random.h"
#include <QDebug>

CombatRoll::CombatRoll(Target* _tar):
    target(_tar), random(new Random(0, 9999)), mechanics(nullptr) {
}

CombatRoll::~CombatRoll() {
    delete random;

    drop_tables();

    if (mechanics != nullptr) {
        delete mechanics;
    }
}

int CombatRoll::get_melee_hit_result(const int wpn_skill, const double crit_mod) {
    const unsigned roll = random->get_roll();

    WhiteHitTable* attack_table = this->get_white_hit_table(wpn_skill);

    return attack_table->get_outcome(roll, crit_mod);
}

int CombatRoll::get_melee_ability_result(const int wpn_skill,
                                         const double crit_mod,
                                         const bool include_dodge,
                                         const bool include_parry,
                                         const bool include_block,
                                         const bool include_miss) {
    const unsigned roll = random->get_roll();

    MeleeSpecialTable* attack_table = this->get_melee_special_table(wpn_skill);

    return attack_table->get_outcome(roll, crit_mod, include_dodge, include_parry, include_block, include_miss);
}

int CombatRoll::get_ranged_hit_result(const int) {
    // TODO: Remove hardcoded critical result
    return AttackResult::CRITICAL;
}

int CombatRoll::get_ranged_ability_result(const int) {
    // TODO: Remove hardcoded critical result
    return AttackResult::CRITICAL;
}

int CombatRoll::get_spell_ability_result(void) {
    // TODO: Remove hardcoded critical result
    return AttackResult::CRITICAL;
}

void CombatRoll::set_character(Character* pchar) {
    this->pchar = pchar;

    if (mechanics == nullptr) {
        mechanics = new Mechanics(target);
    }
}

Target* CombatRoll::get_target() const {
    return this->target;
}

Mechanics* CombatRoll::get_mechanics() const {
    return this->mechanics;
}

WhiteHitTable* CombatRoll::get_white_hit_table(const int wpn_skill) {
    assert(this->pchar != nullptr);
    assert(this->mechanics != nullptr);

    if (auto_attack_tables.contains(wpn_skill))
        return auto_attack_tables[wpn_skill];

    double miss_chance = get_white_miss_chance(wpn_skill) - pchar->get_stats()->get_hit_chance();
    if (miss_chance < 0)
        miss_chance = 0;

    WhiteHitTable* table = new WhiteHitTable(
                this->random,
                wpn_skill,
                miss_chance,
                mechanics->get_dodge_chance(wpn_skill),
                mechanics->get_parry_chance(wpn_skill),
                get_glancing_blow_chance(),
                mechanics->get_block_chance(),
                pchar->get_stats()->get_crit_chance());

    auto_attack_tables[wpn_skill] = table;

    return table;
}

MeleeSpecialTable* CombatRoll::get_melee_special_table(const int wpn_skill) {
    assert(this->pchar != nullptr);
    assert(this->mechanics != nullptr);

    if (melee_special_tables.contains(wpn_skill))
        return melee_special_tables[wpn_skill];

    double miss_chance = get_yellow_miss_chance(wpn_skill) - pchar->get_stats()->get_hit_chance();
    if (miss_chance < 0)
        miss_chance = 0;

    MeleeSpecialTable* table = new MeleeSpecialTable(this->random,
                                                     wpn_skill,
                                                     miss_chance,
                                                     mechanics->get_dodge_chance(wpn_skill),
                                                     mechanics->get_parry_chance(wpn_skill),
                                                     mechanics->get_block_chance(),
                                                     pchar->get_stats()->get_crit_chance());
    melee_special_tables[wpn_skill] = table;

    return table;
}

double CombatRoll::get_white_miss_chance(const int wpn_skill) {
    if (pchar->is_dual_wielding())
        return mechanics->get_dw_white_miss_chance(wpn_skill);
    return mechanics->get_2h_white_miss_chance(wpn_skill);
}

double CombatRoll::get_yellow_miss_chance(const int wpn_skill) {
    return mechanics->get_yellow_miss_chance(wpn_skill);
}

double CombatRoll::get_glancing_blow_chance() {
    return mechanics->get_glancing_blow_chance(pchar->get_clvl());
}

double CombatRoll::get_glancing_blow_dmg_penalty(const int wpn_skill) {
    return mechanics->get_glancing_blow_dmg_penalty(wpn_skill);
}

void CombatRoll::update_crit_chance(const double critical) {
    for (auto it : auto_attack_tables.keys()) {
        auto_attack_tables.value(it)->update_crit_chance(critical);
    }

    for (auto it : melee_special_tables.keys()) {
        melee_special_tables.value(it)->update_crit_chance(critical);
    }
}

void CombatRoll::update_miss_chance(const double hit) {
    for (auto it : auto_attack_tables.keys()) {
        double new_miss_chance = get_white_miss_chance(auto_attack_tables.value(it)->get_wpn_skill()) - hit;
        if (new_miss_chance < 0)
            new_miss_chance = 0.0;
        auto_attack_tables.value(it)->update_miss_chance(new_miss_chance);
    }

    for (auto it : melee_special_tables.keys()) {
        double new_miss_chance = get_white_miss_chance(melee_special_tables.value(it)->get_wpn_skill()) - hit;
        if (new_miss_chance < 0)
            new_miss_chance = 0.0;
        melee_special_tables.value(it)->update_miss_chance(new_miss_chance);
    }
}

void CombatRoll::dump_tables() {
    for (auto it : auto_attack_tables.keys()) {
        auto_attack_tables.value(it)->dump_table();
    }

    for (auto it : melee_special_tables.keys()) {
        melee_special_tables.value(it)->dump_table();
    }
}

void CombatRoll::drop_tables() {
    for (auto it : auto_attack_tables.keys()) {
        delete auto_attack_tables.value(it);
    }

    for (auto it : melee_special_tables.keys()) {
        delete melee_special_tables.value(it);
    }

    auto_attack_tables.clear();
    melee_special_tables.clear();
}

void CombatRoll::set_new_seed(const QString& seed_str) {
    this->random->set_gen_from_seed(seed_str.toULong());
}
