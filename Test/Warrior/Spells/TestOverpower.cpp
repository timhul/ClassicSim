
#include "TestOverpower.h"
#include "Overpower.h"
#include "Queue.h"
#include "Equipment.h"
#include <QDebug>

void TestOverpower::test_all() {
    set_up();
    test_name_correct();
    tear_down();

    set_up();
    test_has_5_second_cooldown();
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

void TestOverpower::test_name_correct() {
    assert(warrior->get_overpower()->get_name() == "Overpower");
}

void TestOverpower::test_has_5_second_cooldown() {
    given_a_guaranteed_melee_ability_hit();
    assert(QString::number(warrior->get_overpower()->get_cooldown(), 'f', 3) == "5.000");

    when_overpower_is_performed();

    Queue* queue = engine->get_queue();
    assert(!queue->empty());
    Event* event = queue->get_next();
    assert(!queue->empty());
    event = queue->get_next();
    assert(event->get_name() == "CooldownReady");
    assert(QString::number(event->get_priority(), 'f', 3) == "5.000");
}

void TestOverpower::test_incurs_global_cooldown_on_use() {
    Queue* queue = engine->get_queue();
    assert(queue->empty());

    when_overpower_is_performed();

    assert(!queue->empty());
    assert(!warrior->action_ready());
    Event* event = queue->get_next();
    assert(event->get_name() == "CooldownReady");
    assert(QString::number(event->get_priority(), 'f', 3) == QString::number(warrior->global_cooldown(), 'f', 3));
}

void TestOverpower::test_hit_dmg() {
    given_a_guaranteed_melee_ability_hit();
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_2_of_2_impale();

    when_overpower_is_performed();

    // [Damage] = base_dmg + (normalized_wpn_speed * AP / 14) + overpower_additional_dmg
    // [306] = 100 + (2.4 * 1000 / 14) + 35
    then_damage_dealt_is(306);
}

void TestOverpower::test_crit_dmg_0_of_2_impale() {
    given_a_guaranteed_melee_ability_crit();
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_0_of_2_impale();

    when_overpower_is_performed();

    // [Damage] = (base_dmg + (normalized_wpn_speed * AP / 14) + overpower_additional_dmg) * crit_dmg_modifier
    // [613] = (100 + (2.4 * 1000 / 14) + 35) * 2.0
    then_damage_dealt_is(613);
}

void TestOverpower::test_crit_dmg_1_of_2_impale() {
    given_a_guaranteed_melee_ability_crit();
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_1_of_2_impale();

    when_overpower_is_performed();

    // [Damage] = (base_dmg + (normalized_wpn_speed * AP / 14) + overpower_additional_dmg) * crit_dmg_modifier
    // [644] = (100 + (2.4 * 1000 / 14) + 35) * 2.0
    then_damage_dealt_is(644);
}

void TestOverpower::test_crit_dmg_2_of_2_impale() {
    given_a_guaranteed_melee_ability_crit();
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_2_of_2_impale();

    when_overpower_is_performed();

    // [Damage] = (base_dmg + (normalized_wpn_speed * AP / 14) + overpower_additional_dmg) * crit_dmg_modifier
    // [674] = (100 + (2.4 * 1000 / 14) + 35) * 2.0
    then_damage_dealt_is(674);
}

void TestOverpower::when_overpower_is_performed() {
    warrior->get_overpower()->perform(100);
}
