#ifndef TESTMULTISHOT_H
#define TESTMULTISHOT_H

#include "TestSpellHunter.h"

class MultiShot;

class TestMultiShot: public TestSpellHunter {
public:
    TestMultiShot(EquipmentDb *equipment_db);

    void test_all();

private:
    MultiShot* multi_shot();

    void test_name_correct() override;
    void test_spell_cooldown() override;
    void test_incurs_global_cooldown() override;
    void test_obeys_global_cooldown() override;
    void test_resource_cost() override;
    void test_is_ready_conditions() override;

    void test_hit_dmg();
    void test_crit_dmg();

    void when_multi_shot_is_performed();
};

#endif // TESTMULTISHOT_H
