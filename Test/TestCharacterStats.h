#ifndef TESTCHARACTERSTATS_H
#define TESTCHARACTERSTATS_H

#include "TestObject.h"

class Character;
class CharacterStats;
class Race;


class TestCharacterStats : TestObject {
public:
    TestCharacterStats(EquipmentDb* equipment_db);

    void set_up();
    void tear_down();
    void test_all() override;

private:
    Character* pchar;
    CharacterStats* cstats;
    Race* race;

    void test_values_after_initialization() override;

    void test_attack_speed_multipliers_stacks_multiplicatively();
    void test_physical_damage_multipliers_stacks_multiplicatively();
    void test_physical_damage_taken_multipliers_stacks_multiplicatively();
    void test_spell_damage_taken_multipliers_stacks_multiplicatively();
    void test_damage_bonuses_vs_creature_type();
    void test_ap_bonuses_vs_creature_type();
    void test_ap_multipliers();
    void test_physical_damage_mod_depends_on_attack_mode();
    void test_crit_dmg_mod_affected_by_creature_type();
    void test_melee_and_ranged_attack_speed_modifiers_are_independent();
};

#endif // TESTCHARACTERSTATS_H
