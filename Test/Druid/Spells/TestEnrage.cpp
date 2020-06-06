#include "TestEnrage.h"

#include <cassert>

#include "BearForm.h"
#include "Druid.h"
#include "DruidSpells.h"
#include "Engine.h"
#include "Enrage.h"
#include "Event.h"
#include "Queue.h"

TestEnrage::TestEnrage(EquipmentDb* equipment_db) : TestSpellDruid(equipment_db, "Enrage") {}

void TestEnrage::test_all() {
    run_mandatory_tests();

    set_up();
    test_improved_enrage_1_of_2_gain_5_rage_immediately();
    tear_down();

    set_up();
    test_improved_enrage_2_of_2_gain_10_rage_immediately();
    tear_down();

    set_up();
    test_gain_20_rage_over_10_seconds();
    tear_down();
}

Enrage* TestEnrage::enrage() const {
    return static_cast<Enrage*>(get_max_rank_spell_by_name("Enrage"));
}

void TestEnrage::test_name_correct() {
    assert(enrage()->get_name() == "Enrage");
}

void TestEnrage::test_spell_cooldown() {
    assert(QString::number(enrage()->get_base_cooldown(), 'f', 3) == "60.000");
}

void TestEnrage::test_whether_spell_causes_global_cooldown() {
    when_enrage_is_performed();

    assert(druid->action_ready());
}

void TestEnrage::test_how_spell_observes_global_cooldown() {
    assert(enrage()->get_spell_status() == SpellStatus::Available);

    given_druid_is_on_gcd(enrage());

    assert(enrage()->get_spell_status() == SpellStatus::Available);
}

void TestEnrage::test_is_ready_conditions() {
    assert(enrage()->get_spell_status() == SpellStatus::InCasterForm);
}

void TestEnrage::test_resource_cost() {
    druid->lose_rage(druid->get_resource_level(ResourceType::Rage));
    assert(enrage()->get_spell_status() == SpellStatus::Available);
}

void TestEnrage::test_improved_enrage_1_of_2_gain_5_rage_immediately() {
    given_druid_has_rage(0);

    when_enrage_is_performed();

    given_druid_has_rage(5);
}

void TestEnrage::test_improved_enrage_2_of_2_gain_10_rage_immediately() {
    given_druid_has_rage(0);

    when_enrage_is_performed();

    given_druid_has_rage(10);
}

void TestEnrage::test_gain_20_rage_over_10_seconds() {
    given_druid_has_rage(0);

    when_enrage_is_performed();

    then_periodic_enrage_rage_gain_is(20);
}

void TestEnrage::when_enrage_is_performed() {
    enrage()->perform();
}

void TestEnrage::then_periodic_enrage_rage_gain_is(const unsigned expected_rage_gain) {
    const unsigned prev = druid->get_resource_level(ResourceType::Rage);

    when_running_queued_events_until(10.01);

    assert(druid->get_resource_level(ResourceType::Rage) - prev == expected_rage_gain);
}

void TestEnrage::given_druid_in_bear_form() {
    bear_form()->perform();
}
