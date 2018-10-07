#ifndef TESTCHARACTERSTATS_H
#define TESTCHARACTERSTATS_H

#include "TestCharacter.h"

class CharacterStats;

class TestCharacterStats : TestCharacter {
public:
    TestCharacterStats();

    void set_up();
    void tear_down();
    void test_all() override;

private:
    CharacterStats* cstats;

    void test_basic_properties() override;

    void test_attack_speed_multipliers_stacks_multiplicatively();
    void test_physical_damage_multipliers_stacks_multiplicatively();
    void test_physical_damage_taken_multipliers_stacks_multiplicatively();
    void test_spell_damage_taken_multipliers_stacks_multiplicatively();
};

#endif // TESTCHARACTERSTATS_H
