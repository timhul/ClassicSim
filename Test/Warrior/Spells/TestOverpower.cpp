
#include "TestOverpower.h"
#include "Overpower.h"
#include "Queue.h"
#include "Equipment.h"

TestOverpower::TestOverpower() :
    TestSpellWarrior("Overpower")
{}

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
    test_costs_5_rage();
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

Overpower* TestOverpower::overpower() {
    return dynamic_cast<WarriorSpells*>(warrior->get_spells())->get_overpower();
}

void TestOverpower::test_name_correct() {
    assert(overpower()->get_name() == "Overpower");
}

void TestOverpower::test_has_5_second_cooldown() {
    given_a_guaranteed_melee_ability_hit();
    assert(QString::number(overpower()->get_cooldown(), 'f', 3) == "5.000");

    when_overpower_is_performed();

    then_next_event_is("CooldownReady", "1.500");
    then_next_event_is("CooldownReady", "5.000");
}

void TestOverpower::test_incurs_global_cooldown_on_use() {
    when_overpower_is_performed();

    then_next_event_is("CooldownReady", QString::number(warrior->global_cooldown(), 'f', 3));
}

void TestOverpower::test_costs_5_rage() {
    given_a_guaranteed_melee_ability_hit();
    given_warrior_has_rage(5);

    when_overpower_is_performed();

    then_warrior_has_rage(0);
}

void TestOverpower::test_hit_dmg() {
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_hit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_2_of_2_impale();

    when_overpower_is_performed();

    // [Damage] = base_dmg + (normalized_wpn_speed * AP / 14) + overpower_additional_dmg
    // [306] = 100 + (2.4 * 1000 / 14) + 35
    then_damage_dealt_is(306);
}

void TestOverpower::test_crit_dmg_0_of_2_impale() {
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_0_of_2_impale();

    when_overpower_is_performed();

    // [Damage] = (base_dmg + (normalized_wpn_speed * AP / 14) + overpower_additional_dmg) * crit_dmg_modifier
    // [613] = (100 + (2.4 * 1000 / 14) + 35) * 2.0
    then_damage_dealt_is(613);
}

void TestOverpower::test_crit_dmg_1_of_2_impale() {
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_1_of_2_impale();

    when_overpower_is_performed();

    // [Damage] = (base_dmg + (normalized_wpn_speed * AP / 14) + overpower_additional_dmg) * crit_dmg_modifier
    // [644] = (100 + (2.4 * 1000 / 14) + 35) * 2.0
    then_damage_dealt_is(644);
}

void TestOverpower::test_crit_dmg_2_of_2_impale() {
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_2_of_2_impale();

    when_overpower_is_performed();

    // [Damage] = (base_dmg + (normalized_wpn_speed * AP / 14) + overpower_additional_dmg) * crit_dmg_modifier
    // [674] = (100 + (2.4 * 1000 / 14) + 35) * 2.0
    then_damage_dealt_is(674);
}

void TestOverpower::when_overpower_is_performed() {
    warrior->lose_rage(overpower()->perform(warrior->get_curr_rage()));
}
