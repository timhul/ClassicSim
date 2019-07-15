#pragma once

#include "TestSpellMage.h"

class TestMageTalentStatIncrease: public TestSpellMage {
public:
public:
    TestMageTalentStatIncrease(EquipmentDb *equipment_db);

    void test_all();

private:
    void test_name_correct() override;
    void test_spell_cooldown() override;
    void test_whether_spell_causes_global_cooldown() override;
    void test_how_spell_observes_global_cooldown() override;
    void test_resource_cost() override;
    void test_is_ready_conditions() override;

    void test_fire_power();
    void test_arcane_subtlety();
    void test_arcane_focus();
    void test_arcane_mind();
    void test_arcane_instability();
    void test_elemental_precision();
    void test_piercing_ice();
};
