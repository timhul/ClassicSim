
#include "CombatRoll.h"
#include <iostream>

AttackResult* CombatRoll::get_melee_hit_result(const int wpn_skill) {
    const int roll = random->get_roll();

    std::cout << "CombatRoll: rolled " << roll << "\n";

    WhiteHitTable* attack_table = this->get_white_hit_table(wpn_skill);
    AttackResult* result = new AttackResult(attack_table->get_outcome(roll));

    return result;
}

AttackResult* CombatRoll::get_melee_ability_result(const int) {
    return new AttackResult(Outcome::CRITICAL);
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
}

WhiteHitTable* CombatRoll::get_white_hit_table(const int wpn_skill) {
    std::map<int, AttackTable*>::iterator it;
    it = attack_tables.find(wpn_skill);
    if (it != attack_tables.end())
        return dynamic_cast<WhiteHitTable*>(it->second);

    WhiteHitTable* table = new WhiteHitTable(get_white_miss_chance(wpn_skill),
                                             get_dodge_chance(wpn_skill),
                                             get_parry_chance(wpn_skill),
                                             get_glancing_blow_chance(),
                                             get_block_chance(),
                                             pchar->get_crit_chance(),
                                             wpn_skill);
    attack_tables.insert(std::pair<int, AttackTable*>(
                             wpn_skill,
                             dynamic_cast<AttackTable*>(table)));

    it = attack_tables.find(wpn_skill);
    assert(it != attack_tables.end());
    return table;
}

float CombatRoll::get_white_miss_chance(const int wpn_skill) const {
    // Note that it assumes defense diff is positive.
    // Formula currently not correct when diff is negative (player wpn skill > target defense)
    int defense_diff = this->target->get_defense() - wpn_skill;

    if (defense_diff > 10)
        return get_white_miss_chance_defense_diff_high(defense_diff);
    return get_white_miss_chance_defense_diff_low(defense_diff);
}

float CombatRoll::get_white_miss_chance_defense_diff_low(const int defense_diff) const {
    assert(defense_diff <= 10);

    if (pchar->is_dual_wielding())
        return 0.24 + defense_diff * 0.001 - pchar->get_hit_chance();
    return 0.05 + defense_diff * 0.001 - pchar->get_hit_chance();
}

float CombatRoll::get_white_miss_chance_defense_diff_high(const int defense_diff) const {
    assert(defense_diff > 10);

    if (pchar->is_dual_wielding())
        return 0.26 + (defense_diff - 10) * 0.004;
    return 0.07 + (defense_diff - 10) * 0.004;
}

float CombatRoll::get_glancing_blow_chance(void) const {
    // TODO: Non-melee classes do not follow this formula.
    int level_diff = target->get_lvl() - pchar->get_clvl();
    if (level_diff < 0)
        return 0.0;

    return 0.1 + level_diff * 5 * 0.02;
}

float CombatRoll::get_dodge_chance(const int wpn_skill) const {
    int defense_diff = wpn_skill - this->target->get_defense();

    if (defense_diff > 0)
        return 0.05 - defense_diff * 0.0004;
    return 0.05;
}

float CombatRoll::get_parry_chance(const int) const {
    // TODO: Add possibility to activate parry chance and have it affected by wpn skill.
    return 0.0;
}

float CombatRoll::get_block_chance(void) const {
    // TODO: Add possibility to activate block chance and have it affected by wpn skill.
    return 0.0;
}
