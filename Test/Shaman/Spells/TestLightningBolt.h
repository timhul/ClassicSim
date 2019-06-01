#pragma once

#include "TestSpellShaman.h"

class TestLightningBolt: public TestSpellShaman {
public:
    TestLightningBolt(EquipmentDb *equipment_db);

    void test_all();

private:
    void test_name_correct() override;
    void test_spell_cooldown() override;
    void test_whether_spell_causes_global_cooldown() override;
    void test_how_spell_observes_global_cooldown() override;
    void test_resource_cost() override;
    void test_is_ready_conditions() override;

    void test_hit_dmg();
    void test_crit_dmg();
    void test_clearcasting_roll();

    void when_lightning_bolt_is_performed();
};
