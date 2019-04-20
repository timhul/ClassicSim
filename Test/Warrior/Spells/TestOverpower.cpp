#include "TestOverpower.h"

#include "Equipment.h"
#include "Overpower.h"
#include "OverpowerBuff.h"
#include "Queue.h"

TestOverpower::TestOverpower(EquipmentDb *equipment_db) :
    TestSpellWarrior(equipment_db, "Overpower")
{}

void TestOverpower::test_all() {
    run_mandatory_tests();

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

    set_up();
    test_overpower_hit_removes_buff();
    tear_down();

    set_up();
    test_overpower_crit_removes_buff();
    tear_down();

    set_up();
    test_overpower_miss_removes_buff();
    tear_down();
}

Overpower* TestOverpower::overpower() {
    return dynamic_cast<WarriorSpells*>(warrior->get_spells())->get_overpower();
}

void TestOverpower::test_name_correct() {
    assert(overpower()->get_name() == "Overpower");
}

void TestOverpower::test_spell_cooldown() {
    given_a_guaranteed_melee_ability_hit();
    assert(QString::number(overpower()->get_base_cooldown(), 'f', 3) == "5.000");

    when_overpower_is_performed();

    then_next_event_is("PlayerAction", "1.500");
    then_next_event_is("PlayerAction", "5.000");
}

void TestOverpower::test_incurs_global_cooldown() {
    assert(warrior->action_ready());

    when_overpower_is_performed();

    assert(!warrior->action_ready());
}

void TestOverpower::test_obeys_global_cooldown() {
    given_warrior_has_rage(100);
    when_overpower_buff_is_applied();
    assert(overpower()->is_available());

    given_warrior_is_on_gcd();

    assert(!overpower()->is_available());
}


void TestOverpower::test_resource_cost() {
    given_a_guaranteed_melee_ability_hit();
    given_warrior_has_rage(5);

    when_overpower_is_performed();

    then_warrior_has_rage(0);
}

void TestOverpower::test_is_ready_conditions() {
    given_warrior_in_battle_stance();
    given_no_overpower_buff();
    given_warrior_has_rage(100);
    assert(!overpower()->is_available());

    given_warrior_in_berserker_stance();
    when_overpower_buff_is_applied();
    given_warrior_has_rage(100);
    assert(!overpower()->is_available());

    given_warrior_in_defensive_stance();
    when_overpower_buff_is_applied();
    given_warrior_has_rage(100);
    assert(!overpower()->is_available());

    given_warrior_in_battle_stance();
    when_overpower_buff_is_applied();
    given_warrior_has_rage(100);
    assert(overpower()->is_available());
}

void TestOverpower::test_stance_cooldown() {
    given_warrior_in_berserker_stance();
    when_overpower_buff_is_applied();
    given_warrior_has_rage(100);
    assert(overpower()->is_available());

    when_switching_to_battle_stance();
    given_warrior_has_rage(100);
    assert(warrior->on_stance_cooldown() == true);
    assert(!overpower()->is_available());

    given_engine_priority_pushed_forward(0.99);
    assert(warrior->on_stance_cooldown() == true);
    assert(!overpower()->is_available());

    given_engine_priority_pushed_forward(0.02);
    assert(warrior->on_stance_cooldown() == false);
    assert(overpower()->is_available());
}

void TestOverpower::test_hit_dmg() {
    given_target_has_0_armor();
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
    given_target_has_0_armor();
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
    given_target_has_0_armor();
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
    given_target_has_0_armor();
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

void TestOverpower::test_overpower_hit_removes_buff() {
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_hit();

    when_overpower_buff_is_applied();
    when_overpower_is_performed();

    then_overpower_is_inactive();
}

void TestOverpower::test_overpower_crit_removes_buff() {
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();

    when_overpower_buff_is_applied();
    when_overpower_is_performed();

    then_overpower_is_inactive();
}

void TestOverpower::test_overpower_miss_removes_buff() {
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_miss();

    when_overpower_buff_is_applied();
    when_overpower_is_performed();

    then_overpower_is_inactive();
}

void TestOverpower::given_no_overpower_buff() {
    warrior->get_overpower_buff()->cancel_buff();
    assert(!warrior->get_overpower_buff()->is_active());
}

void TestOverpower::when_overpower_is_performed() {
    if (pchar->get_equipment()->get_mainhand() == nullptr)
        given_a_mainhand_weapon_with_100_min_max_dmg();

    overpower()->perform();
}

void TestOverpower::when_overpower_buff_is_applied() {
    warrior->get_overpower_buff()->apply_buff();
    assert(warrior->get_overpower_buff()->is_active());
}

void TestOverpower::then_overpower_is_inactive() {
    assert(warrior->get_overpower_buff()->is_active() == false);
}
