#ifndef TESTSPELLDAMAGE_H
#define TESTSPELLDAMAGE_H

#include "TestSpell.h"

class Character;

class TestSpellDamage : public TestSpell {
public:
    TestSpellDamage(EquipmentDb* equipment_db, QString spell_under_test);

    virtual ~TestSpellDamage();

    void run_mandatory_tests(const bool prepare_combat_iterations = true);

    virtual void set_up(const bool prepare_combat_iterations = true) = 0;
    virtual void tear_down() = 0;

    virtual void test_name_correct() = 0;
    virtual void test_obeys_global_cooldown() = 0;
    virtual void test_incurs_global_cooldown() = 0;
    virtual void test_spell_cooldown() = 0;
    virtual void test_resource_cost() = 0;
    virtual void test_is_ready_conditions() = 0;

private:
    bool has_run_mandatory_tests;
};

#endif // TESTSPELLDAMAGE_H
