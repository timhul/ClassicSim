
#include "TestSpellDamage.h"

TestSpellDamage::TestSpellDamage(EquipmentDb* equipment_db, QString spell_under_test):
    TestSpell(equipment_db, spell_under_test),
    has_run_mandatory_tests(false)
{}

TestSpellDamage::~TestSpellDamage() {
    assert(has_run_mandatory_tests);
}

void TestSpellDamage::run_mandatory_tests() {
    set_up();
    test_name_correct();
    tear_down();

    set_up();
    test_obeys_global_cooldown();
    tear_down();

    set_up();
    test_incurs_global_cooldown();
    tear_down();

    set_up();
    test_spell_cooldown();
    tear_down();

    set_up();
    test_resource_cost();
    tear_down();

    set_up();
    test_is_ready_conditions();
    tear_down();

    has_run_mandatory_tests = true;
}
