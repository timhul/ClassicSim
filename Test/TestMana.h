#pragma once

#include "TestSpellHunter.h"

class Character;
class Mana;
class Race;

class TestMana : TestSpellHunter {
public:
    TestMana(EquipmentDb* equipment_db);

    void test_all();

private:
    void test_name_correct() override;
    void test_spell_cooldown() override;
    void test_whether_spell_causes_global_cooldown() override;
    void test_how_spell_observes_global_cooldown() override;
    void test_resource_cost() override;
    void test_is_ready_conditions() override;

    void test_mana_gain_when_tick_is_within_5sr();
    void test_mana_gain_when_tick_is_outside_5sr();

    void spend_mana();
};
