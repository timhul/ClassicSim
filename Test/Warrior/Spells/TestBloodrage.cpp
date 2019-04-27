#include "TestBloodrage.h"

#include "Bloodrage.h"
#include "Engine.h"
#include "Queue.h"

TestBloodrage::TestBloodrage(EquipmentDb *equipment_db) :
    TestSpellWarrior(equipment_db, "Bloodrage")
{}

void TestBloodrage::test_all() {
    run_mandatory_tests();

    set_up();
    test_gain_10_rage_immediately();
    tear_down();

    set_up();
    test_gain_10_rage_over_10_seconds();
    tear_down();
}

Bloodrage* TestBloodrage::bloodrage() {
    return dynamic_cast<WarriorSpells*>(warrior->get_spells())->get_bloodrage();
}

void TestBloodrage::test_name_correct() {
    assert(bloodrage()->get_name() == "Bloodrage");
}

void TestBloodrage::test_spell_cooldown() {
    assert(QString::number(bloodrage()->get_base_cooldown(), 'f', 3) == "60.000");
}

void TestBloodrage::test_whether_spell_causes_global_cooldown() {
    when_bloodrage_is_performed();

    assert(warrior->action_ready());
}

void TestBloodrage::test_how_spell_observes_global_cooldown() {
    assert(bloodrage()->get_spell_status() == SpellStatus::Available);

    given_warrior_is_on_gcd();

    assert(bloodrage()->get_spell_status() == SpellStatus::Available);
}

void TestBloodrage::test_is_ready_conditions() {
    assert(bloodrage()->get_spell_status() == SpellStatus::Available);

    given_warrior_in_defensive_stance();
    assert(bloodrage()->get_spell_status() == SpellStatus::InDefensiveStance);

    given_warrior_in_battle_stance();
    assert(bloodrage()->get_spell_status() == SpellStatus::Available);

    given_warrior_in_berserker_stance();
    assert(bloodrage()->get_spell_status() == SpellStatus::Available);
}

void TestBloodrage::test_stance_cooldown() {
    assert(bloodrage()->get_spell_status() == SpellStatus::Available);

    when_switching_to_berserker_stance();
    assert(warrior->on_stance_cooldown() == true);
    assert(bloodrage()->get_spell_status() == SpellStatus::Available);

    given_engine_priority_pushed_forward(0.99);
    assert(warrior->on_stance_cooldown() == true);
    assert(bloodrage()->get_spell_status() == SpellStatus::Available);

    given_engine_priority_pushed_forward(0.02);
    assert(warrior->on_stance_cooldown() == false);
    assert(bloodrage()->get_spell_status() == SpellStatus::Available);
}

void TestBloodrage::test_resource_cost() {
    warrior->lose_rage(warrior->get_resource_level(ResourceType::Rage));
    assert(bloodrage()->get_spell_status() == SpellStatus::Available);
}

void TestBloodrage::test_gain_10_rage_immediately() {
    given_warrior_has_rage(0);

    when_bloodrage_is_performed();

    then_warrior_has_rage(10);
}

void TestBloodrage::test_gain_10_rage_over_10_seconds() {
    given_warrior_has_rage(0);

    when_bloodrage_is_performed();

    then_periodic_bloodrage_rage_gain_is(10);
}

void TestBloodrage::when_bloodrage_is_performed() {
    bloodrage()->perform();
}

void TestBloodrage::then_periodic_bloodrage_rage_gain_is(const unsigned expected_rage_gain) {
    unsigned prev = warrior->get_resource_level(ResourceType::Rage);
    while (!pchar->get_engine()->get_queue()->empty()) {
        Event* event = pchar->get_engine()->get_queue()->get_next();
        pchar->get_engine()->set_current_priority(event);

        if (event->get_name() != "ResourceGain") {
            delete event;
            continue;
        }

        event->act();
        delete event;
    }

    assert(warrior->get_resource_level(ResourceType::Rage) - prev == expected_rage_gain);
}
