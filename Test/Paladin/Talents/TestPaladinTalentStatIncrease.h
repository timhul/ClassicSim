#pragma once

#include "TestSpellPaladin.h"

class TestPaladinTalentStatIncrease: public TestSpellPaladin {
public:
public:
    TestPaladinTalentStatIncrease(EquipmentDb *equipment_db);

    void test_all();

private:
    void test_name_correct() override;
    void test_spell_cooldown() override;
    void test_whether_spell_causes_global_cooldown() override;
    void test_how_spell_observes_global_cooldown() override;
    void test_resource_cost() override;
    void test_is_ready_conditions() override;

    void test_conviction();
    void test_two_handed_weapon_specialization();
    void test_precision();
    void test_one_handed_weapon_specialization();
    void test_divine_strength();
    void test_divine_intellect();
};
