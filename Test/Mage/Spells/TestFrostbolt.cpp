#include "TestFrostbolt.h"

#include "CharacterStats.h"
#include "Event.h"
#include "Frostbolt.h"
#include "Mage.h"

TestFrostbolt::TestFrostbolt(EquipmentDb* equipment_db) :
    TestSpellMage(equipment_db, "Frostbolt")
{}

void TestFrostbolt::test_all() {
    run_mandatory_tests();

    set_up();
    test_hit_dmg();
    tear_down();

    set_up();
    test_crit_dmg();
    tear_down();

    set_up();
    test_cast_time_1_of_5_improved_frostbolt();
    tear_down();

    set_up();
    test_cast_time_2_of_5_improved_frostbolt();
    tear_down();

    set_up();
    test_cast_time_3_of_5_improved_frostbolt();
    tear_down();

    set_up();
    test_cast_time_4_of_5_improved_frostbolt();
    tear_down();

    set_up();
    test_cast_time_5_of_5_improved_frostbolt();
    tear_down();

    set_up();
    test_mana_return_1_of_3_master_of_elements();
    tear_down();

    set_up();
    test_mana_return_2_of_3_master_of_elements();
    tear_down();

    set_up();
    test_mana_return_3_of_3_master_of_elements();
    tear_down();

    set_up();
    test_hit_dmg_1_of_3_piercing_ice();
    tear_down();

    set_up();
    test_hit_dmg_3_of_3_piercing_ice();
    tear_down();

    set_up(false);
    test_crit_dmg_1_of_5_ice_shards();
    tear_down();

    set_up(false);
    test_crit_dmg_5_of_5_ice_shards();
    tear_down();

    set_up();
    test_crits_do_not_apply_ignite();
    tear_down();

    set_up(false);
    test_hit_dmg_arcane_power();
    tear_down();

    set_up();
    test_casting_speed_increases_reduces_casting_time();
    tear_down();
}

void TestFrostbolt::test_name_correct() {
    assert(frostbolt()->get_name() == "Frostbolt");
}

void TestFrostbolt::test_spell_cooldown() {
    assert(almost_equal(0.0, frostbolt()->get_base_cooldown()));
}

void TestFrostbolt::test_whether_spell_causes_global_cooldown() {
    assert(mage->action_ready());

    when_frostbolt_is_performed();

    assert(!mage->action_ready());
}

void TestFrostbolt::test_how_spell_observes_global_cooldown() {

}

void TestFrostbolt::test_is_ready_conditions() {
    assert(frostbolt()->get_spell_status() == SpellStatus::Available);
}

void TestFrostbolt::test_resource_cost() {
    given_mage_has_mana(291);

    when_frostbolt_is_performed();
    when_running_queued_events_until(3.01);

    then_mage_has_mana(1);
}

void TestFrostbolt::test_hit_dmg() {
    given_a_guaranteed_magic_hit(MagicSchool::Frost);
    given_1000_spell_power();
    given_no_previous_damage_dealt();

    when_frostbolt_is_performed();
    when_running_queued_events_until(3.01);

    // [Damage] = base_dmg + spell_power * spell_coefficient * 2ndary_effect_penalty
    // [1329 - 1369] = [515 - 555] + 1000 * (3 / 3.5) * 0.95
    then_damage_dealt_is_in_range(1329, 1369);
}

void TestFrostbolt::test_crit_dmg() {
    given_a_guaranteed_magic_crit(MagicSchool::Frost);
    given_1000_spell_power();
    given_no_previous_damage_dealt();

    when_frostbolt_is_performed();
    when_running_queued_events_until(3.01);

    // [Damage] = (base_dmg + spell_power * spell_coefficient * 2ndary_effect_penalty) * spell_crit_dmg_modifier
    // [1994 - 2054] = ([515 - 555] + 1000 * (3 / 3.5) * 0.95) * 1.5
    then_damage_dealt_is_in_range(1994, 2054);
}

void TestFrostbolt::test_cast_time_1_of_5_improved_frostbolt() {
    given_frost_talent_rank("Improved Frostbolt", 1);

    when_frostbolt_is_performed();

    then_next_event_is(EventType::PlayerAction, "1.500");
    then_next_event_is(EventType::CastComplete, "2.900");
}

void TestFrostbolt::test_cast_time_2_of_5_improved_frostbolt() {
    given_frost_talent_rank("Improved Frostbolt", 2);

    when_frostbolt_is_performed();

    then_next_event_is(EventType::PlayerAction, "1.500");
    then_next_event_is(EventType::CastComplete, "2.800");
}

void TestFrostbolt::test_cast_time_3_of_5_improved_frostbolt() {
    given_frost_talent_rank("Improved Frostbolt", 3);

    when_frostbolt_is_performed();

    then_next_event_is(EventType::PlayerAction, "1.500");
    then_next_event_is(EventType::CastComplete, "2.700");
}

void TestFrostbolt::test_cast_time_4_of_5_improved_frostbolt() {
    given_frost_talent_rank("Improved Frostbolt", 4);

    when_frostbolt_is_performed();

    then_next_event_is(EventType::PlayerAction, "1.500");
    then_next_event_is(EventType::CastComplete, "2.600");
}

void TestFrostbolt::test_cast_time_5_of_5_improved_frostbolt() {
    given_frost_talent_rank("Improved Frostbolt", 5);

    when_frostbolt_is_performed();

    then_next_event_is(EventType::PlayerAction, "1.500");
    then_next_event_is(EventType::CastComplete, "2.500");
}

void TestFrostbolt::test_mana_return_1_of_3_master_of_elements() {
    given_a_guaranteed_magic_crit(MagicSchool::Frost);
    given_fire_talent_rank("Master of Elements", 1);
    given_mage_has_mana(1000);

    when_frostbolt_is_performed();
    when_running_queued_events_until(3.01);

    // [mana] = initial_mana - resource_cost + base_resource_cost * master_of_elements_return
    // [739] = 1000 - 290 + 290 * 0.1
    then_mage_has_mana(739);
}

void TestFrostbolt::test_mana_return_2_of_3_master_of_elements() {
    given_a_guaranteed_magic_crit(MagicSchool::Frost);
    given_fire_talent_rank("Master of Elements", 2);
    given_mage_has_mana(1000);

    when_frostbolt_is_performed();
    when_running_queued_events_until(3.01);

    // [mana] = initial_mana - resource_cost + base_resource_cost * master_of_elements_return
    // [768] = 1000 - 290 + 290 * 0.2
    then_mage_has_mana(768);
}

void TestFrostbolt::test_mana_return_3_of_3_master_of_elements() {
    given_a_guaranteed_magic_crit(MagicSchool::Frost);
    given_fire_talent_rank("Master of Elements", 3);
    given_mage_has_mana(1000);

    when_frostbolt_is_performed();
    when_running_queued_events_until(3.01);

    // [mana] = initial_mana - resource_cost + base_resource_cost * master_of_elements_return
    // [797] = 1000 - 290 + 290 * 0.3
    then_mage_has_mana(797);
}

void TestFrostbolt::test_hit_dmg_1_of_3_piercing_ice() {
    given_a_guaranteed_magic_hit(MagicSchool::Frost);
    given_1000_spell_power();
    given_frost_talent_rank("Piercing Ice", 1);
    given_no_previous_damage_dealt();

    when_frostbolt_is_performed();
    when_running_queued_events_until(3.01);

    // [Damage] = (base_dmg + spell_power * spell_coefficient * 2ndary_effect_penalty) * piercing_ice
    // [1356 - 1397] = ([515 - 555] + 1000 * (3 / 3.5) * 0.95) * 1.02
    then_damage_dealt_is_in_range(1356, 1397);
}

void TestFrostbolt::test_hit_dmg_3_of_3_piercing_ice() {
    given_a_guaranteed_magic_hit(MagicSchool::Frost);
    given_1000_spell_power();
    given_frost_talent_rank("Piercing Ice", 3);
    given_no_previous_damage_dealt();

    when_frostbolt_is_performed();
    when_running_queued_events_until(3.01);

    // [Damage] = (base_dmg + spell_power * spell_coefficient * 2ndary_effect_penalty) * piercing_ice
    // [1409 - 1451] = ([515 - 555] + 1000 * (3 / 3.5) * 0.95) * 1.06
    then_damage_dealt_is_in_range(1409, 1451);
}

void TestFrostbolt::test_crit_dmg_1_of_5_ice_shards() {
    given_a_guaranteed_magic_crit(MagicSchool::Frost);
    given_1000_spell_power();
    given_frost_talent_rank("Ice Shards", 1);
    pchar->prepare_set_of_combat_iterations();
    given_no_previous_damage_dealt();

    when_frostbolt_is_performed();
    when_running_queued_events_until(3.01);

    // [Damage] = (base_dmg + spell_power * spell_coefficient * 2ndary_effect_penalty) * spell_crit_dmg_modifier
    // [2127 - 2191] = ([515 - 555] + 1000 * (3 / 3.5) * 0.95) * 1.6
    then_damage_dealt_is_in_range(2127, 2191);
}

void TestFrostbolt::test_crit_dmg_5_of_5_ice_shards() {
    given_a_guaranteed_magic_crit(MagicSchool::Frost);
    given_1000_spell_power();
    given_frost_talent_rank("Ice Shards", 5);
    pchar->prepare_set_of_combat_iterations();
    given_no_previous_damage_dealt();

    when_frostbolt_is_performed();
    when_running_queued_events_until(3.01);

    // [Damage] = (base_dmg + spell_power * spell_coefficient * 2ndary_effect_penalty) * spell_crit_dmg_modifier
    // [2659 - 2739] = ([515 - 555] + 1000 * (3 / 3.5) * 0.95) * 2.0
    then_damage_dealt_is_in_range(2659, 2739);
}

void TestFrostbolt::test_crits_do_not_apply_ignite() {
    given_a_guaranteed_magic_crit(MagicSchool::Frost);
    given_1000_spell_power();
    given_fire_talent_rank("Ignite", 1);
    given_no_previous_damage_dealt();

    when_frostbolt_is_performed();
    when_running_queued_events_until(4.01);

    // [Frostbolt Damage] = (base_dmg + spell_power * spell_coefficient * 2ndary_effect_penalty) * spell_crit_dmg_modifier
    // [1994 - 2054] = ([515 - 555] + 1000 * (3 / 3.5) * 0.95) * 1.5

    // [Ignite Damage] = Frostbolt_damage * ignite_percentage / num_ticks
    // [40 - 41] = [1994 - 2054] * 0.08 / 4

    // [Total Damage] = Frostbolt_damage
    // [1994 - 2054] = [1994 - 2054]
    then_damage_dealt_is_in_range(1994, 2054);
}

void TestFrostbolt::test_casting_speed_increases_reduces_casting_time() {
    assert(almost_equal(3.0, frostbolt()->get_cast_time()));

    pchar->get_stats()->increase_casting_speed_mod(100);
    assert(almost_equal(1.5, frostbolt()->get_cast_time()));

    pchar->get_stats()->decrease_casting_speed_mod(100);
    assert(almost_equal(3.0, frostbolt()->get_cast_time()));
}

void TestFrostbolt::test_hit_dmg_arcane_power() {
    given_mage_has_mana(378);
    given_a_guaranteed_magic_hit(MagicSchool::Frost);
    given_1000_spell_power();
    given_no_previous_damage_dealt();
    given_arcane_power_is_active();
    given_engine_priority_pushed_forward(1.5);

    when_frostbolt_is_performed();
    when_running_queued_events_until(4.51);

    // [Damage] = (base_dmg + spell_power * spell_coefficient * 2ndary_effect_penalty) * arcane_power * arcane_instability
    // [1780 - 1833] = ([515 - 555] + 1000 * (3 / 3.5) * 0.95) * 1.3 * 1.03
    then_damage_dealt_is_in_range(1780, 1833);
    then_mage_has_mana(1);
}

void TestFrostbolt::when_frostbolt_is_performed() {
    frostbolt()->perform();
}
