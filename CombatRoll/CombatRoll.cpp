
#include "CombatRoll.h"
#include "Character.h"
#include "CharacterStats.h"
#include "Mechanics.h"
#include "AttackResult.h"
#include "AttackTable.h"
#include "WhiteHitTable.h"
#include "MeleeSpecialTable.h"
#include "SimSettings.h"
#include "Target.h"
#include "Random.h"
#include <QDebug>

CombatRoll::CombatRoll(Character *pchar):
    pchar(pchar),
    target(pchar->get_target()),
    random(new Random(0, 9999)),
    mechanics(new Mechanics(target)) {
}

CombatRoll::~CombatRoll() {
    delete random;

    drop_tables();

    delete mechanics;
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
    // CSIM-73: Remove hardcoded critical result
    return AttackResult::CRITICAL;
}

int CombatRoll::get_ranged_ability_result(const int) {
    // CSIM-73: Remove hardcoded critical result
    return AttackResult::CRITICAL;
}

int CombatRoll::get_spell_ability_result() {
    // CSIM-60: Remove hardcoded critical result
    return AttackResult::CRITICAL;
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

    double glancing_blow_chance = pchar->get_sim_settings()->get_ruleset() == Ruleset::Loatheb ?
                0 : mechanics->get_glancing_blow_chance(pchar->get_clvl());

    auto* table = new WhiteHitTable(
                this->random,
                wpn_skill,
                miss_chance,
                mechanics->get_dodge_chance(wpn_skill),
                mechanics->get_parry_chance(wpn_skill),
                glancing_blow_chance,
                mechanics->get_block_chance());

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

    auto* table = new MeleeSpecialTable(this->random,
                                        wpn_skill,
                                        miss_chance,
                                        mechanics->get_dodge_chance(wpn_skill),
                                        mechanics->get_parry_chance(wpn_skill),
                                        mechanics->get_block_chance());
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

double CombatRoll::get_glancing_blow_dmg_penalty(const int wpn_skill) {
    return mechanics->get_glancing_blow_dmg_penalty(wpn_skill);
}

void CombatRoll::update_miss_chance(const double hit) {
    QMap<int, WhiteHitTable*>::const_iterator it_auto = auto_attack_tables.constBegin();
    auto end_auto = auto_attack_tables.constEnd();
    while(it_auto != end_auto) {
        double new_miss_chance = get_white_miss_chance(it_auto.value()->get_wpn_skill()) - hit;
        if (new_miss_chance < 0)
            new_miss_chance = 0.0;
        it_auto.value()->update_miss_chance(new_miss_chance);
        ++it_auto;
    }

    QMap<int, MeleeSpecialTable*>::const_iterator it_special = melee_special_tables.constBegin();
    auto end_special = melee_special_tables.constEnd();
    while(it_special != end_special) {
        double new_miss_chance = get_white_miss_chance(it_special.value()->get_wpn_skill()) - hit;
        if (new_miss_chance < 0)
            new_miss_chance = 0.0;
        it_special.value()->update_miss_chance(new_miss_chance);
        ++it_special;
    }
}

void CombatRoll::update_spell_crit_chance(const double) {
    // CSIM-60 Implement spell attack rolls
}

void CombatRoll::update_spell_miss_chance(const double) {
    // CSIM-60 Implement spell attack rolls
}

void CombatRoll::dump_tables() {
    QMap<int, WhiteHitTable*>::const_iterator it_auto = auto_attack_tables.constBegin();
    auto end_auto = auto_attack_tables.constEnd();
    while(it_auto != end_auto) {
        it_auto.value()->dump_table();
        ++it_auto;
    }

    QMap<int, MeleeSpecialTable*>::const_iterator it_special = melee_special_tables.constBegin();
    auto end_special = melee_special_tables.constEnd();
    while(it_special != end_special) {
        it_special.value()->dump_table();
        ++it_special;
    }
}

void CombatRoll::drop_tables() {
    QMap<int, WhiteHitTable*>::const_iterator it_auto = auto_attack_tables.constBegin();
    auto end_auto = auto_attack_tables.constEnd();
    while(it_auto != end_auto) {
        delete it_auto.value();
        ++it_auto;
    }

    QMap<int, MeleeSpecialTable*>::const_iterator it_special = melee_special_tables.constBegin();
    auto end_special = melee_special_tables.constEnd();
    while(it_special != end_special) {
        delete it_special.value();
        ++it_special;
    }

    auto_attack_tables.clear();
    melee_special_tables.clear();
}

void CombatRoll::set_new_seed(const unsigned seed) {
    this->random->set_gen_from_seed(seed);
}
