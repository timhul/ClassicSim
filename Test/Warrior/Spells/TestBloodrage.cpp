
#include "TestBloodrage.h"
#include "Bloodrage.h"
#include "Queue.h"

TestBloodrage::TestBloodrage() :
    TestSpellWarrior("Bloodrage")
{}

void TestBloodrage::test_all() {
    set_up();
    test_name_correct();
    tear_down();

    set_up();
    test_has_60_second_cooldown();
    tear_down();

    set_up();
    test_does_not_incur_global_cooldown_on_use();
    tear_down();

    set_up();
    test_costs_0_rage();
    tear_down();

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

void TestBloodrage::test_has_60_second_cooldown() {
    assert(QString::number(bloodrage()->get_cooldown(), 'f', 3) == "60.000");
}

void TestBloodrage::test_does_not_incur_global_cooldown_on_use() {
    when_bloodrage_is_performed();

    assert(warrior->action_ready());
}

void TestBloodrage::test_costs_0_rage() {
    warrior->lose_rage(warrior->get_curr_rage());
    assert(bloodrage()->is_available());
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

void TestBloodrage::then_periodic_bloodrage_rage_gain_is(const int expected_rage_gain) {
    int prev = warrior->get_curr_rage();
    while (!engine->get_queue()->empty()) {
        Event* event = engine->get_queue()->get_next();
        engine->set_current_priority(event);

        if (event->get_name() != "ResourceGain") {
            delete event;
            continue;
        }

        event->act();
        delete event;
    }

    assert(warrior->get_curr_rage() - prev == expected_rage_gain);
}
