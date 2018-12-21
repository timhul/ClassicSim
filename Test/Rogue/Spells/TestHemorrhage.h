#ifndef TESTHEMORRHAGE_H
#define TESTHEMORRHAGE_H

#include "TestSpellRogue.h"

class TestHemorrhage: public TestSpellRogue {
public:
    TestHemorrhage(EquipmentDb *equipment_db);

    void test_all();

private:
    Hemorrhage* hemo();

    void test_name_correct() override;
    void test_spell_cooldown() override;
    void test_incurs_global_cooldown() override;
    void test_obeys_global_cooldown() override;
    void test_resource_cost() override;
    void test_is_ready_conditions() override;
    void test_combo_points() override;
    void test_stealth() override;

    void test_hit_dmg();
    void test_crit_dmg();
    void test_hit_dmg_5_of_5_lethality();
    void test_crit_dmg_1_of_5_lethality();
    void test_crit_dmg_2_of_5_lethality();
    void test_crit_dmg_3_of_5_lethality();
    void test_crit_dmg_4_of_5_lethality();
    void test_crit_dmg_5_of_5_lethality();

    void when_hemorrhage_is_performed();

    void given_hemorrhage_is_enabled();
};

#endif // TESTHEMORRHAGE_H
