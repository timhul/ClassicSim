#include "TestWhirlwind.h"

#include "Equipment.h"
#include "Execute.h"
#include "Queue.h"
#include "WarriorSpells.h"
#include "Whirlwind.h"

TestWhirlwind::TestWhirlwind(EquipmentDb *equipment_db) :
    TestSpellWarrior(equipment_db, "Whirlwind")
{}

void TestWhirlwind::test_all() {
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
    test_dodge_applies_overpower_buff();
    tear_down();
}

Whirlwind* TestWhirlwind::whirlwind() {
    return dynamic_cast<WarriorSpells*>(warrior->get_spells())->get_whirlwind();
}

void TestWhirlwind::test_name_correct() {
    assert(whirlwind()->get_name() == "Whirlwind");
}

void TestWhirlwind::test_spell_cooldown() {
    given_a_guaranteed_melee_ability_hit();
    assert(QString::number(whirlwind()->get_base_cooldown(), 'f', 3) == "10.000");

    when_whirlwind_is_performed();

    then_next_event_is("PlayerAction", "1.500");
    then_next_event_is("PlayerAction", "10.000");
}

void TestWhirlwind::test_incurs_global_cooldown() {
    assert(warrior->action_ready());

    when_whirlwind_is_performed();

    assert(!warrior->action_ready());
}

void TestWhirlwind::test_obeys_global_cooldown() {
    given_warrior_in_berserker_stance();
    given_warrior_has_rage(100);
    assert(whirlwind()->is_available());

    given_warrior_is_on_gcd(dynamic_cast<WarriorSpells*>(pchar->get_spells())->get_execute());

    assert(!whirlwind()->is_available());
}

void TestWhirlwind::test_is_ready_conditions() {

}

void TestWhirlwind::test_stance_cooldown() {
    given_warrior_has_rage(100);
    assert(whirlwind()->is_available());

    when_switching_to_berserker_stance();
    given_warrior_has_rage(100);
    assert(warrior->on_stance_cooldown() == true);
    assert(!whirlwind()->is_available());

    given_engine_priority_pushed_forward(0.99);
    assert(warrior->on_stance_cooldown() == true);
    assert(!whirlwind()->is_available());

    given_engine_priority_pushed_forward(0.02);
    assert(warrior->on_stance_cooldown() == false);
    assert(whirlwind()->is_available());
}

void TestWhirlwind::test_resource_cost() {
    given_a_guaranteed_melee_ability_hit();
    given_warrior_has_rage(25);

    when_whirlwind_is_performed();

    then_warrior_has_rage(0);
}

void TestWhirlwind::test_hit_dmg() {
    given_target_has_0_armor();
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_hit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_2_of_2_impale();

    when_whirlwind_is_performed();

    // [Damage] = base_dmg + (normalized_wpn_speed * AP / 14)
    // [271] = 100 + (2.4 * 1000 / 14)
    then_damage_dealt_is(271);
}

void TestWhirlwind::test_crit_dmg_0_of_2_impale() {
    given_target_has_0_armor();
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_0_of_2_impale();

    when_whirlwind_is_performed();

    // [Damage] = base_dmg + (normalized_wpn_speed * AP / 14) * crit_dmg_modifier
    // [543] = (100 + (2.4 * 1000 / 14)) * 2.0
    then_damage_dealt_is(543);
}

void TestWhirlwind::test_crit_dmg_1_of_2_impale() {
    given_target_has_0_armor();
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_1_of_2_impale();

    when_whirlwind_is_performed();

    // [Damage] = base_dmg + (normalized_wpn_speed * AP / 14) * crit_dmg_modifier
    // [570] = (100 + (2.4 * 1000 / 14)) * 2.1
    then_damage_dealt_is(570);
}

void TestWhirlwind::test_crit_dmg_2_of_2_impale() {
    given_target_has_0_armor();
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_2_of_2_impale();

    when_whirlwind_is_performed();

    // [Damage] = base_dmg + (normalized_wpn_speed * AP / 14) * crit_dmg_modifier
    // [597] = (100 + (2.4 * 1000 / 14)) * 2.2
    then_damage_dealt_is(597);
}

void TestWhirlwind::test_dodge_applies_overpower_buff() {
    given_a_guaranteed_melee_ability_dodge();

    when_whirlwind_is_performed();

    then_overpower_is_active();
}

void TestWhirlwind::when_whirlwind_is_performed() {
    if (pchar->get_equipment()->get_mainhand() == nullptr)
        given_a_mainhand_weapon_with_100_min_max_dmg();

    whirlwind()->perform();
}
