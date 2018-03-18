
#include "CombatRoll.h"
#include "Character.h"

AttackResult* CombatRoll::get_melee_hit_result(const int wpn_skill) {
    const int roll = random->get_roll();

    WhiteHitTable* attack_table = this->get_white_hit_table(wpn_skill);
    AttackResult* result = new AttackResult(attack_table->get_outcome(roll));

    return result;
}

AttackResult* CombatRoll::get_melee_ability_result(const int wpn_skill) {
    const int roll = random->get_roll();

    MeleeSpecialTable* attack_table = this->get_melee_special_table(wpn_skill);
    AttackResult* result = new AttackResult(attack_table->get_outcome(roll));

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

    std::map<int, WhiteHitTable*>::iterator it;
    it = auto_attack_tables.find(wpn_skill);
    if (it != auto_attack_tables.end())
        return it->second;

    WhiteHitTable* table = new WhiteHitTable(get_white_miss_chance(wpn_skill),
                                             mechanics->get_dodge_chance(wpn_skill),
                                             mechanics->get_parry_chance(wpn_skill),
                                             get_glancing_blow_chance(),
                                             mechanics->get_block_chance(),
                                             pchar->get_crit_chance(),
                                             wpn_skill);
    auto_attack_tables.insert(std::pair<int, WhiteHitTable*>(wpn_skill, table));

    it = auto_attack_tables.find(wpn_skill);
    assert(it != auto_attack_tables.end());
    return table;
}

MeleeSpecialTable* CombatRoll::get_melee_special_table(const int wpn_skill) {
    assert(this->pchar != nullptr);
    assert(this->mechanics != nullptr);

    std::map<int, MeleeSpecialTable*>::iterator it;
    it = melee_special_tables.find(wpn_skill);
    if (it != melee_special_tables.end())
        return it->second;

    MeleeSpecialTable* table = new MeleeSpecialTable(this->random,
                                                     get_white_miss_chance(wpn_skill),
                                                     mechanics->get_dodge_chance(wpn_skill),
                                                     mechanics->get_parry_chance(wpn_skill),
                                                     mechanics->get_block_chance(),
                                                     pchar->get_crit_chance(),
                                                     wpn_skill);
    melee_special_tables.insert(std::pair<int, MeleeSpecialTable*>(wpn_skill, table));

    it = melee_special_tables.find(wpn_skill);
    assert(it != melee_special_tables.end());
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
