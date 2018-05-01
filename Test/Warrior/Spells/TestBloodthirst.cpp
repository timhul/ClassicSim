
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
    test_costs_30_rage();
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

Bloodthirst* TestBloodthirst::bloodthirst() {
    return dynamic_cast<WarriorSpells*>(warrior->get_spells())->get_bloodthirst();
}

void TestBloodthirst::test_name_correct() {
    assert(bloodthirst()->get_name() == "Bloodthirst");
}

void TestBloodthirst::test_has_6_second_cooldown() {
    given_a_guaranteed_melee_ability_hit();
    assert(QString::number(bloodthirst()->get_cooldown(), 'f', 3) == "6.000");

    when_bloodthirst_is_performed();

    then_next_event_is("CooldownReady", "1.500");
    then_next_event_is("CooldownReady", "6.000");
}

void TestBloodthirst::test_incurs_global_cooldown_on_use() {
    when_bloodthirst_is_performed();

    then_next_event_is("CooldownReady", QString::number(warrior->global_cooldown(), 'f', 3));
}

void TestBloodthirst::test_costs_30_rage() {
    given_warrior_has_rage(30);

    when_bloodthirst_is_performed();

    then_warrior_has_rage(0);
}

void TestBloodthirst::test_hit_dmg() {
    given_a_guaranteed_melee_ability_hit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_2_of_2_impale();

    when_bloodthirst_is_performed();

    // [Damage] = melee_ap * 0.45
    // [450] = 1000 * 0.45
    then_damage_dealt_is(450);
}

void TestBloodthirst::test_crit_dmg_0_of_2_impale() {
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_0_of_2_impale();

    when_bloodthirst_is_performed();

    // [Damage] = melee_ap * 0.45 * crit_dmg_modifier
    // [900] = 1000 * 0.45 * 2.0
    then_damage_dealt_is(900);
}

void TestBloodthirst::test_crit_dmg_1_of_2_impale() {
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_1_of_2_impale();

    when_bloodthirst_is_performed();

    // [Damage] = melee_ap * 0.45 * crit_dmg_modifier
    // [945] = 1000 * 0.45 * 2.1
    then_damage_dealt_is(945);
}

void TestBloodthirst::test_crit_dmg_2_of_2_impale() {
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_2_of_2_impale();

    when_bloodthirst_is_performed();

    // [Damage] = melee_ap * 0.45 * crit_dmg_modifier
    // [990] = 1000 * 0.45 * 2.2
    then_damage_dealt_is(990);
}

void TestBloodthirst::when_bloodthirst_is_performed() {
    warrior->lose_rage(bloodthirst()->perform(warrior->get_curr_rage()));
}
