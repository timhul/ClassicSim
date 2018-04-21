
#include "TestExecute.h"
#include "Execute.h"

#include "Warrior.h"
#include "Target.h"
#include "Orc.h"

#include "Engine.h"
#include "Queue.h"
#include "Equipment.h"
#include "Target.h"
#include "CombatRoll.h"
#include "PlayerAction.h"

#include <QDebug>

void TestExecute::set_up() {
    // not thread safe
    engine = new Engine();
    equipment = new Equipment();
    target = new Target(63);
    combat = new CombatRoll(target);
    race = new Orc();
    warrior = new Warrior(race, engine, equipment, combat);
}

void TestExecute::tear_down() {
    // not thread safe
    delete engine;
    delete equipment;
    delete combat;
    delete target;
    delete race;
    delete warrior;
}

void TestExecute::test_all() {
    set_up();
    test_name_correct();
    tear_down();

    set_up();
    test_has_no_cooldown();
    tear_down();

    set_up();
    test_incurs_global_cooldown_on_use();
    tear_down();
}

void TestExecute::test_name_correct() {
    assert(warrior->get_execute()->get_name() == "Execute");
}

void TestExecute::test_has_no_cooldown() {
    assert(QString::number(warrior->get_execute()->get_cooldown(), 'f', 3) == "0.000");
}

void TestExecute::test_incurs_global_cooldown_on_use() {
    Queue* queue = engine->get_queue();
    assert(queue->empty());

    warrior->get_execute()->perform(100);

    assert(!queue->empty());
    assert(!warrior->action_ready());
    Event* event = queue->get_next();
    assert(event->get_name() == "CooldownReady");
    assert(QString::number(event->get_priority(), 'f', 3) == QString::number(warrior->global_cooldown(), 'f', 3));
}
