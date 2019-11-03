#include "TestEvocation.h"

#include <cassert>

#include "CharacterStats.h"
#include "Equipment.h"
#include "Event.h"
#include "Evocation.h"
#include "Mage.h"
#include "Mana.h"

TestEvocation::TestEvocation(EquipmentDb* equipment_db) :
    TestSpellMage(equipment_db, "Evocation")
{}

void TestEvocation::test_all() {
    run_mandatory_tests();

    set_up();
    test_mana_regen_increase();
    tear_down();

    set_up();
    test_2p_t3_set_bonus_cooldown_decrease();
    tear_down();
}

void TestEvocation::test_name_correct() {
    assert(evocation()->get_name() == "Evocation");
}

void TestEvocation::test_spell_cooldown() {
    assert(almost_equal(480.0, evocation()->get_base_cooldown()));
}

void TestEvocation::test_whether_spell_causes_global_cooldown() {
    assert(mage->action_ready());

    when_evocation_is_performed();

    assert(!mage->action_ready());
}

void TestEvocation::test_how_spell_observes_global_cooldown() {

}

void TestEvocation::test_is_ready_conditions() {
    assert(evocation()->get_spell_status() == SpellStatus::Available);
}

void TestEvocation::test_mana_regen_increase() {
    assert(17 == static_cast<Mana*>(pchar->get_resource())->get_resource_per_tick());

    when_evocation_is_performed();
    assert(283 == static_cast<Mana*>(pchar->get_resource())->get_resource_per_tick());

    when_running_queued_events_until(8.01);
    // 18 due to rounded tick causing a remainder
    assert(18 == static_cast<Mana*>(pchar->get_resource())->get_resource_per_tick());
}

void TestEvocation::test_2p_t3_set_bonus_cooldown_decrease() {
    const double cooldown_before = evocation()->get_base_cooldown();

    given_bracers_equipped(22503, "Frostfire Bindings");
    assert(almost_equal(cooldown_before, evocation()->get_base_cooldown()));
    given_head_equipped(22498, "Frostfire Circlet");
    assert(almost_equal(cooldown_before - 60.0, evocation()->get_base_cooldown()));

    given_bracers_cleared();
    assert(almost_equal(cooldown_before, evocation()->get_base_cooldown()));
    given_head_cleared();
    assert(almost_equal(cooldown_before, evocation()->get_base_cooldown()));
}

void TestEvocation::test_resource_cost() {
    assert(almost_equal(0.0, evocation()->get_resource_cost()));
    given_mage_has_mana(0);

    when_evocation_is_performed();

    then_mage_has_mana(0);
}

void TestEvocation::when_evocation_is_performed() {
    evocation()->perform();
}
