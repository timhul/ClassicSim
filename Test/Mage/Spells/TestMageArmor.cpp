#include "TestMageArmor.h"

#include <cassert>
#include <cmath>

#include "CharacterStats.h"
#include "Equipment.h"
#include "Event.h"
#include "MageArmor.h"
#include "Mage.h"
#include "Mana.h"

TestMageArmor::TestMageArmor(EquipmentDb* equipment_db) : TestSpellMage(equipment_db, "Mage Armor") {}

void TestMageArmor::test_all() {
    run_mandatory_tests();

    set_up();
    test_mana_regen_increase();
    tear_down();
}

void TestMageArmor::test_name_correct() {
    assert(mage_armor()->get_name() == "Mage Armor");
}

void TestMageArmor::test_spell_cooldown() {
    assert(almost_equal(0.0, mage_armor()->get_base_cooldown())); // Mage armor does not have a cooldown
}

void TestMageArmor::test_whether_spell_causes_global_cooldown() {
    assert(mage->action_ready());
    when_mage_armor_is_performed();
    assert(!mage->action_ready());
}

void TestMageArmor::test_how_spell_observes_global_cooldown() {}

void TestMageArmor::test_is_ready_conditions() {
    assert(mage_armor()->get_spell_status() == SpellStatus::Available);
}

void TestMageArmor::test_mana_regen_increase() {
    assert(17 == static_cast<Mana*>(pchar->get_resource())->get_resource_per_tick());
    given_mage_has_mana(0);

    when_mage_armor_is_performed();

    when_running_queued_events_until(4.01);
    // Need to regenerate 11 mana in total over 4 seconds using 2 ticks.
    double mp4 = pchar->get_mp5_from_spirit() * 4.0 / 5.0; // MP4 if we were not casting
    unsigned int cast_mp4 = (unsigned int) std::lround(mp4 * 0.3); // Marge armor mana reg coefficient - since we just cast mage armor spell, we are within 5s rule
    then_mage_has_mana(cast_mp4);
}

void TestMageArmor::test_resource_cost() {
    assert(almost_equal(0.0, mage_armor()->get_resource_cost()));
    given_mage_has_mana(1000);
    when_mage_armor_is_performed();
    then_mage_has_mana(1000);
}

void TestMageArmor::when_mage_armor_is_performed() {
    mage_armor()->perform();
}

