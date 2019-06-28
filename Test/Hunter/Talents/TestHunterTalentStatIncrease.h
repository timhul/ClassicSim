#pragma once

#include "TestSpellHunter.h"

class TestHunterTalentStatIncrease: public TestSpellHunter {
public:
public:
    TestHunterTalentStatIncrease(EquipmentDb *equipment_db);

    void test_all();

private:
    void test_name_correct() override;
    void test_spell_cooldown() override;
    void test_whether_spell_causes_global_cooldown() override;
    void test_how_spell_observes_global_cooldown() override;
    void test_resource_cost() override;
    void test_is_ready_conditions() override;

    void test_surefooted();
    void test_lightning_reflexes();
    void test_killer_instinct();
    void test_trueshot_aura();
    void test_unleashed_fury();
    void test_ferocity();
};
