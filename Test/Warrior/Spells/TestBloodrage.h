#pragma once

#include "TestSpellWarrior.h"

class TestBloodrage: public TestSpellWarrior {
public:
    TestBloodrage(EquipmentDb *equipment_db);

    void test_all();

private:
    Bloodrage* bloodrage() const;

    void test_name_correct() override;
    void test_spell_cooldown() override;
    void test_stance_cooldown() override;
    void test_whether_spell_causes_global_cooldown() override;
    void test_how_spell_observes_global_cooldown() override;
    void test_resource_cost() override;
    void test_is_ready_conditions() override;

    void test_gain_10_rage_immediately();
    void test_gain_10_rage_over_10_seconds();

    void when_bloodrage_is_performed();

    void then_periodic_bloodrage_rage_gain_is(const unsigned expected_rage_gain);
};
