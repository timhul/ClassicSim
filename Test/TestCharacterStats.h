#ifndef TESTCHARACTERSTATS_H
#define TESTCHARACTERSTATS_H

#include "TestCharacter.h"

class Character;
class CharacterStats;
class Race;


class TestCharacterStats : TestCharacter {
public:
    TestCharacterStats();

    void set_up();
    void tear_down();
    void test_all() override;

private:
    Character* pchar;
    CharacterStats* cstats;
    Race* race;

    void test_basic_properties() override;

    void test_attack_speed_multipliers_stacks_multiplicatively();
    void test_physical_damage_multipliers_stacks_multiplicatively();
    void test_physical_damage_taken_multipliers_stacks_multiplicatively();
    void test_spell_damage_taken_multipliers_stacks_multiplicatively();
    void test_damage_bonuses_vs_creature_type();
    void test_ap_bonuses_vs_creature_type();
    void test_ap_multipliers();
};

#endif // TESTCHARACTERSTATS_H
