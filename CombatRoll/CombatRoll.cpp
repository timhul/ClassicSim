
#include "CombatRoll.h"
#include "Character.h"
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

    for (auto it : auto_attack_tables.keys()) {
        delete auto_attack_tables.value(it);
    }

    for (auto it : melee_special_tables.keys()) {
        delete melee_special_tables.value(it);
    }

    auto_attack_tables.clear();
    melee_special_tables.clear();

    if (mechanics != nullptr) {
        delete mechanics;
    }
}

AttackResult* CombatRoll::get_melee_hit_result(const int wpn_skill, const float crit_mod) {
    const int roll = random->get_roll();

    WhiteHitTable* attack_table = this->get_white_hit_table(wpn_skill);
    AttackResult* result = new AttackResult(attack_table->get_outcome(roll, crit_mod));

    return result;
}

AttackResult* CombatRoll::get_melee_ability_result(const int wpn_skill, const float crit_mod) {
    const int roll = random->get_roll();

    MeleeSpecialTable* attack_table = this->get_melee_special_table(wpn_skill);
    AttackResult* result = new AttackResult(attack_table->get_outcome(roll, crit_mod));

    return result;
}

AttackResult* CombatRoll::get_ranged_hit_result(const int){
    return new AttackResult(Outcome::CRITICAL);
}

AttackResult* CombatRoll::get_ranged_ability_result(const int){
    return new AttackResult(Outcome::CRITICAL);
}

AttackResult* CombatRoll::get_spell_ability_result(void){
    return new AttackResult(Outcome::CRITICAL);
}

void CombatRoll::set_target(Target* target) {
    this->target = target;
    // TODO: Update attack tables (in order to detect target level change)
}

void CombatRoll::set_character(Character* pchar) {
    this->pchar = pchar;

    if (mechanics == nullptr) {
        mechanics = new Mechanics(target->get_lvl(), pchar->get_hit_chance());
    }
}

WhiteHitTable* CombatRoll::get_white_hit_table(const int wpn_skill) {
    assert(this->pchar != nullptr);
    assert(this->mechanics != nullptr);

    if (auto_attack_tables.contains(wpn_skill))
        return auto_attack_tables[wpn_skill];

    WhiteHitTable* table = new WhiteHitTable(get_white_miss_chance(wpn_skill),
                                             mechanics->get_dodge_chance(wpn_skill),
                                             mechanics->get_parry_chance(wpn_skill),
                                             get_glancing_blow_chance(),
                                             mechanics->get_block_chance(),
                                             pchar->get_crit_chance());
    auto_attack_tables[wpn_skill] = table;

    return table;
}

MeleeSpecialTable* CombatRoll::get_melee_special_table(const int wpn_skill) {
    assert(this->pchar != nullptr);
    assert(this->mechanics != nullptr);

    if (melee_special_tables.contains(wpn_skill))
        return melee_special_tables[wpn_skill];

    MeleeSpecialTable* table = new MeleeSpecialTable(this->random,
                                                     get_white_miss_chance(wpn_skill),
                                                     mechanics->get_dodge_chance(wpn_skill),
                                                     mechanics->get_parry_chance(wpn_skill),
                                                     mechanics->get_block_chance(),
                                                     pchar->get_crit_chance());
    melee_special_tables[wpn_skill] = table;

    return table;
}

float CombatRoll::get_white_miss_chance(const int wpn_skill) {
    if (pchar->is_dual_wielding())
        return mechanics->get_dw_white_miss_chance(wpn_skill);
    return mechanics->get_2h_white_miss_chance(wpn_skill);
}

float CombatRoll::get_glancing_blow_chance() {
    return mechanics->get_glancing_blow_chance(pchar->get_clvl());
}

float CombatRoll::get_glancing_blow_dmg_penalty(const int wpn_skill) {
    return mechanics->get_glancing_blow_dmg_penalty(wpn_skill);
}

void CombatRoll::update_crit_chance(const float critical) {
    for (auto it : auto_attack_tables.keys()) {
        auto_attack_tables.value(it)->update_crit_chance(critical);
    }

    for (auto it : melee_special_tables.keys()) {
        melee_special_tables.value(it)->update_crit_chance(critical);
    }
}
