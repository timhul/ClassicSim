#ifndef TESTAIMEDSHOT_H
#define TESTAIMEDSHOT_H

#include "TestSpellHunter.h"

class AimedShot;

class TestAimedShot: public TestSpellHunter {
public:
    TestAimedShot(EquipmentDb *equipment_db);

    void test_all();

private:
    AimedShot* aimed_shot();

    void test_name_correct() override;
    void test_spell_cooldown() override;
    void test_incurs_global_cooldown() override;
    void test_obeys_global_cooldown() override;
    void test_resource_cost() override;
    void test_is_ready_conditions() override;

    void test_hit_dmg();
    void test_crit_dmg();

    void when_aimed_shot_is_performed();
};

#endif // TESTAIMEDSHOT_H
