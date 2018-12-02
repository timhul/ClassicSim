#ifndef TESTSINISTERSTRIKE_H
#define TESTSINISTERSTRIKE_H

#include "TestSpellRogue.h"

class TestSinisterStrike: public TestSpellRogue {
public:
    TestSinisterStrike(EquipmentDb *equipment_db);

    void test_all();

    SinisterStrike* sinister_strike();

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
    void test_resource_cost_1_of_2_imp_ss();
    void test_resource_cost_2_of_2_imp_ss();

    void when_sinister_strike_is_performed();

private:
};

#endif // TESTSINISTERSTRIKE_H
