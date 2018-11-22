#ifndef TESTBACKSTAB_H
#define TESTBACKSTAB_H

#include "TestSpellRogue.h"

class TestBackstab: public TestSpellRogue {
public:
    TestBackstab(EquipmentDb *equipment_db);

    void test_all();

    Backstab* backstab();

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

    void when_backstab_is_performed();

private:
};

#endif // TESTBACKSTAB_H
