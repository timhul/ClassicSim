#pragma once

#include "TestSpellWarrior.h"

class TestWhirlwind : public TestSpellWarrior {
public:
    TestWhirlwind(EquipmentDb* equipment_db);

    void test_all();

private:
    Whirlwind* whirlwind() const;

    void test_name_correct() override;
    void test_spell_cooldown() override;
    void test_stance_cooldown() override;
    void test_whether_spell_causes_global_cooldown() override;
    void test_how_spell_observes_global_cooldown() override;
    void test_resource_cost() override;
    void test_is_ready_conditions() override;

    void test_hit_dmg();
    void test_crit_dmg_0_of_2_impale();
    void test_crit_dmg_1_of_2_impale();
    void test_crit_dmg_2_of_2_impale();
    void test_dodge_applies_overpower_buff();

    void when_whirlwind_is_performed();
};
