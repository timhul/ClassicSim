#pragma once

#include "TestSpellDruid.h"

class TestEnrage : public TestSpellDruid {
public:
    TestEnrage(EquipmentDb* equipment_db);

    void test_all();

private:
    Enrage* enrage() const;

    void test_name_correct() override;
    void test_spell_cooldown() override;
    void test_whether_spell_causes_global_cooldown() override;
    void test_how_spell_observes_global_cooldown() override;
    void test_resource_cost() override;
    void test_is_ready_conditions() override;

    void test_improved_enrage_1_of_2_gain_5_rage_immediately();
    void test_improved_enrage_2_of_2_gain_10_rage_immediately();
    void test_gain_20_rage_over_10_seconds();

    void when_enrage_is_performed();

    void then_periodic_enrage_rage_gain_is(const unsigned expected_rage_gain);

    void given_druid_in_bear_form();
};
