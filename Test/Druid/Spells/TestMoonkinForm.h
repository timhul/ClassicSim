#pragma once

#include "TestSpellDruid.h"

class TestMoonkinForm: public TestSpellDruid {
public:
    TestMoonkinForm(EquipmentDb *equipment_db);

    void test_all();

private:
    void test_name_correct() override;
    void test_spell_cooldown() override;
    void test_whether_spell_causes_global_cooldown() override;
    void test_how_spell_observes_global_cooldown() override;
    void test_resource_cost() override;
    void test_is_ready_conditions() override;
    void test_gives_spell_crit_to_party_members();
    void test_resource_cost_with_3_of_3_natural_shapeshifter();

    void when_moonkin_form_is_performed();
};
