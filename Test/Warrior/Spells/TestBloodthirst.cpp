
#include "TestBloodthirst.h"
#include "Bloodthirst.h"
#include "Queue.h"
#include <QDebug>

void TestBloodthirst::test_all() {
    set_up();
    test_name_correct();
    tear_down();

    set_up();
    test_has_6_second_cooldown();
    tear_down();

    set_up();
    test_incurs_global_cooldown_on_use();
    tear_down();

    set_up();
    test_hit_dmg();
    tear_down();

    set_up();
    test_crit_dmg_0_of_2_impale();
    tear_down();

    set_up();
    test_crit_dmg_1_of_2_impale();
    tear_down();

    set_up();
    test_crit_dmg_2_of_2_impale();
    tear_down();
}

void TestBloodthirst::test_name_correct() {
    assert(warrior->get_bloodthirst()->get_name() == "Bloodthirst");
}

void TestBloodthirst::test_has_6_second_cooldown() {
    given_a_guaranteed_melee_ability_hit();
    assert(QString::number(warrior->get_bloodthirst()->get_cooldown(), 'f', 3) == "6.000");

    when_bloodthirst_is_performed();

    Queue* queue = engine->get_queue();
    assert(!queue->empty());
    Event* event = queue->get_next();
    assert(!queue->empty());
    event = queue->get_next();
    assert(event->get_name() == "CooldownReady");
    assert(QString::number(event->get_priority(), 'f', 3) == "6.000");
}

void TestBloodthirst::test_incurs_global_cooldown_on_use() {
    Queue* queue = engine->get_queue();
    assert(queue->empty());

    when_bloodthirst_is_performed();

    assert(!queue->empty());
    assert(!warrior->action_ready());
    Event* event = queue->get_next();
    assert(event->get_name() == "CooldownReady");
    assert(QString::number(event->get_priority(), 'f', 3) == QString::number(warrior->global_cooldown(), 'f', 3));
}

void TestBloodthirst::test_hit_dmg() {
    given_a_guaranteed_melee_ability_hit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_2_of_2_impale();

    when_bloodthirst_is_performed();

    then_damage_dealt_is(450);
}

void TestBloodthirst::test_crit_dmg_0_of_2_impale() {
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_0_of_2_impale();

    when_bloodthirst_is_performed();

    then_damage_dealt_is(900);
}

void TestBloodthirst::test_crit_dmg_1_of_2_impale() {
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_1_of_2_impale();

    when_bloodthirst_is_performed();

    then_damage_dealt_is(945);
}

void TestBloodthirst::test_crit_dmg_2_of_2_impale() {
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_2_of_2_impale();

    when_bloodthirst_is_performed();

    then_damage_dealt_is(990);
}

void TestBloodthirst::given_1000_melee_ap() {
    warrior->increase_melee_ap(1000 - warrior->get_melee_ap());
    assert(warrior->get_melee_ap() == 1000);
}

void TestBloodthirst::when_bloodthirst_is_performed() {
    warrior->get_bloodthirst()->perform(100);
}
