#ifndef TESTHUNTERTALENTSTATINCREASE_H
#define TESTHUNTERTALENTSTATINCREASE_H

#include "TestSpellHunter.h"

class TestHunterTalentStatIncrease: public TestSpellHunter {
public:
public:
    TestHunterTalentStatIncrease(EquipmentDb *equipment_db);

    void test_all();

private:
    void test_name_correct() override;
    void test_spell_cooldown() override;
    void test_incurs_global_cooldown() override;
    void test_obeys_global_cooldown() override;
    void test_resource_cost() override;
    void test_is_ready_conditions() override;

    void test_surefooted();
    void test_lightning_reflexes();
    void test_killer_instinct();
};

#endif // TESTHUNTERTALENTSTATINCREASE_H
