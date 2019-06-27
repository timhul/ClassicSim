#pragma once

#include "TestSpellWarrior.h"

class TestBloodFury: public TestSpellWarrior {
public:
    TestBloodFury(EquipmentDb* equipment_db);

    void test_all();

private:
    BloodFury* blood_fury() const;

    void test_name_correct() override;
    void test_spell_cooldown() override;
    void test_stance_cooldown() override;
    void test_how_spell_observes_global_cooldown() override;
    void test_whether_spell_causes_global_cooldown() override;
    void test_resource_cost() override;
    void test_is_ready_conditions() override;

    void test_melee_ap_bonus();
    void test_does_not_yield_ranged_ap();
};
