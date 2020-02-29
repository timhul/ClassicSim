#include "TestLifeTap.h"

#include <cassert>

#include "CharacterStats.h"
#include "Event.h"
#include "Frostbolt.h"
#include "LifeTap.h"
#include "Warlock.h"

TestLifeTap::TestLifeTap(EquipmentDb* equipment_db_) : TestSpellWarlock(equipment_db_, "Life Tap") {}

void TestLifeTap::test_all() {
    run_mandatory_tests();

    set_up();
    test_life_tap_scaling_with_spell_power();
    tear_down();

    set_up();
    test_1_of_2_improved_life_tap();
    tear_down();

    set_up();
    test_2_of_2_improved_life_tap();
    tear_down();
}

void TestLifeTap::test_name_correct() {
    assert(life_tap()->get_name() == "Life Tap");
}

void TestLifeTap::test_spell_cooldown() {
    assert(almost_equal(0.0, life_tap()->get_base_cooldown()));
}

void TestLifeTap::test_whether_spell_causes_global_cooldown() {
    assert(warlock->action_ready());

    when_life_tap_is_performed();

    assert(!warlock->action_ready());
}

void TestLifeTap::test_how_spell_observes_global_cooldown() {}

void TestLifeTap::test_is_ready_conditions() {
    assert(life_tap()->get_spell_status() == SpellStatus::Available);
}

void TestLifeTap::test_resource_cost() {
    given_warlock_has_mana(0);

    when_life_tap_is_performed();

    then_warlock_has_mana(424);
}

void TestLifeTap::test_life_tap_scaling_with_spell_power() {
    given_1000_spell_power();
    given_warlock_has_mana(0);

    when_life_tap_is_performed();

    // [mana] = (base_yield + spell_power * spell_coefficient) * imp_life_tap
    // 1224 = (424 + 1000 * 0.8) * 1.1
    then_warlock_has_mana(1224);
}

void TestLifeTap::test_1_of_2_improved_life_tap() {
    given_affliction_talent_rank("Improved Life Tap", 1);
    given_1000_spell_power();
    given_warlock_has_mana(0);

    when_life_tap_is_performed();

    // [mana] = (base_yield + spell_power * spell_coefficient) * imp_life_tap
    // 1346 = (424 + 1000 * 0.8) * 1.1
    then_warlock_has_mana(1346);
}

void TestLifeTap::test_2_of_2_improved_life_tap() {
    given_affliction_talent_rank("Improved Life Tap", 2);
    given_1000_spell_power();
    given_warlock_has_mana(0);

    when_life_tap_is_performed();

    // [mana] = (base_yield + spell_power * spell_coefficient) * imp_life_tap
    // 1469 = (424 + 1000 * 0.8) * 1.2
    then_warlock_has_mana(1469);
}

void TestLifeTap::when_life_tap_is_performed() {
    life_tap()->perform();
}
