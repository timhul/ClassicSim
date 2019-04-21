#include "TestMortalStrike.h"

#include "MortalStrike.h"
#include "Queue.h"

TestMortalStrike::TestMortalStrike(EquipmentDb *equipment_db) :
    TestSpellWarrior(equipment_db, "Mortal Strike")
{}

void TestMortalStrike::test_all() {
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

MortalStrike* TestMortalStrike::mortal_strike() {
    return dynamic_cast<WarriorSpells*>(warrior->get_spells())->get_mortal_strike();
}

void TestMortalStrike::test_name_correct() {
    assert(mortal_strike()->get_name() == "Mortal Strike");
}

void TestMortalStrike::test_spell_cooldown() {
    given_a_twohand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_hit();
    assert(QString::number(mortal_strike()->get_base_cooldown(), 'f', 3) == "6.000");

    when_mortal_strike_is_performed();

    then_next_event_is("PlayerAction", "1.500");
    then_next_event_is("PlayerAction", "6.000");
}

void TestMortalStrike::test_incurs_global_cooldown() {
    given_a_twohand_weapon_with_100_min_max_dmg();
    assert(warrior->action_ready());
    when_mortal_strike_is_performed();

    assert(!warrior->action_ready());
}

void TestMortalStrike::test_obeys_global_cooldown() {
    mortal_strike()->enable();
    given_warrior_has_rage(100);
    assert(mortal_strike()->get_spell_status() == SpellStatus::Available);

    given_warrior_is_on_gcd();

    assert(mortal_strike()->get_spell_status() == SpellStatus::OnGCD);
    assert(almost_equal(mortal_strike()->get_cooldown_remaining(), 0));
}

void TestMortalStrike::test_is_ready_conditions() {
    given_warrior_has_rage(100);
    assert(mortal_strike()->get_spell_status() == SpellStatus::NotEnabled);

    mortal_strike()->enable();
    assert(mortal_strike()->get_spell_status() == SpellStatus::Available);
}

void TestMortalStrike::test_resource_cost() {
    given_a_twohand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_hit();
    given_warrior_has_rage(30);

    when_mortal_strike_is_performed();

    then_warrior_has_rage(0);
}

void TestMortalStrike::test_stance_cooldown() {
    mortal_strike()->enable();
    given_warrior_has_rage(100);
    assert(mortal_strike()->get_spell_status() == SpellStatus::Available);

    when_switching_to_berserker_stance();
    given_warrior_has_rage(100);
    assert(warrior->on_stance_cooldown() == true);
    assert(mortal_strike()->get_spell_status() == SpellStatus::OnGCD);

    given_engine_priority_pushed_forward(0.99);
    assert(warrior->on_stance_cooldown() == true);
    assert(mortal_strike()->get_spell_status() == SpellStatus::SpellSpecific);

    given_engine_priority_pushed_forward(0.02);
    assert(warrior->on_stance_cooldown() == false);
    assert(mortal_strike()->get_spell_status() == SpellStatus::Available);
}

void TestMortalStrike::test_hit_dmg() {
    given_target_has_0_armor();
    given_a_twohand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_hit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_2_of_2_impale();

    when_mortal_strike_is_performed();

    // [Damage] = base_dmg + (normalized_wpn_speed * AP / 14) + flat_damage_bonus
    // [496] = 100 + (3.3 * 1000 / 14) + 160
    then_damage_dealt_is(496);
}

void TestMortalStrike::test_crit_dmg_0_of_2_impale() {
    given_target_has_0_armor();
    given_a_twohand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_0_of_2_impale();

    when_mortal_strike_is_performed();

    // [Damage] = base_dmg + (normalized_wpn_speed * AP / 14) + flat_damage_bonus
    // [991] = (100 + (3.3 * 1000 / 14) + 160) * 2.0
    then_damage_dealt_is(991);
}

void TestMortalStrike::test_crit_dmg_1_of_2_impale() {
    given_target_has_0_armor();
    given_a_twohand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_1_of_2_impale();

    when_mortal_strike_is_performed();

    // [Damage] = base_dmg + (normalized_wpn_speed * AP / 14) * crit_dmg_modifier
    // [1041] = (100 + (3.3 * 1000 / 14)) * 2.1
    then_damage_dealt_is(1041);
}

void TestMortalStrike::test_crit_dmg_2_of_2_impale() {
    given_target_has_0_armor();
    given_a_twohand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_2_of_2_impale();

    when_mortal_strike_is_performed();

    // [Damage] = base_dmg + (normalized_wpn_speed * AP / 14) * crit_dmg_modifier
    // [1091] = (100 + (3.3 * 1000 / 14)) * 2.2
    then_damage_dealt_is(1091);
}

void TestMortalStrike::test_dodge_applies_overpower_buff() {
    given_a_guaranteed_melee_ability_dodge();

    when_mortal_strike_is_performed();

    then_overpower_is_active();
}

void TestMortalStrike::when_mortal_strike_is_performed() {
    mortal_strike()->perform();
}
