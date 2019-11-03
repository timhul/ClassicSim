#include "TestWrath.h"

#include <cassert>
#include <cmath>

#include "Buff.h"
#include "CharacterStats.h"
#include "Druid.h"
#include "DruidSpells.h"
#include "Event.h"
#include "Wrath.h"

TestWrath::TestWrath(EquipmentDb* equipment_db) :
    TestSpellDruid(equipment_db, "Wrath")
{}

void TestWrath::test_all() {
    run_mandatory_tests();

    set_up();
    test_hit_dmg();
    tear_down();

    set_up();
    test_crit_dmg();
    tear_down();

    set_up();
    test_crit_dmg_5_of_5_vengeance();
    tear_down();

    set_up();
    test_hit_damage_1_of_5_moonfury();
    tear_down();

    set_up();
    test_hit_damage_5_of_5_moonfury();
    tear_down();

    set_up();
    test_cast_time_1_of_5_improved_wrath();
    tear_down();

    set_up();
    test_cast_time_2_of_5_improved_wrath();
    tear_down();

    set_up();
    test_cast_time_3_of_5_improved_wrath();
    tear_down();

    set_up();
    test_cast_time_4_of_5_improved_wrath();
    tear_down();

    set_up();
    test_cast_time_5_of_5_improved_wrath();
    tear_down();

    set_up();
    test_casting_speed_increases_reduces_casting_time();
    tear_down();

    set_up();
    test_resource_cost_3_of_3_moonglow();
    tear_down();

    set_up(false);
    test_natures_grace_reduces_casting_time();
    tear_down();

    set_up(false);
    test_natures_grace_activated_on_spell_crit_if_enabled();
    tear_down();

    set_up();
    test_natures_grace_not_activated_on_spell_crit_if_not_enabled();
    tear_down();
}

void TestWrath::test_name_correct() {
    assert(wrath()->get_name() == "Wrath");
}

void TestWrath::test_spell_cooldown() {
    assert(almost_equal(0.0, wrath()->get_base_cooldown()));
}

void TestWrath::test_whether_spell_causes_global_cooldown() {
    assert(druid->action_ready());

    when_wrath_is_performed();

    assert(!druid->action_ready());
}

void TestWrath::test_how_spell_observes_global_cooldown() {

}

void TestWrath::test_is_ready_conditions() {
    assert(wrath()->get_spell_status() == SpellStatus::Available);
}

void TestWrath::test_resource_cost() {
    given_druid_has_mana(181);

    when_wrath_is_performed();
    when_running_queued_events_until(2.01);

    then_druid_has_mana(1);
}

void TestWrath::test_hit_dmg() {
    given_a_guaranteed_magic_hit(MagicSchool::Nature);
    given_1000_spell_power();
    given_no_previous_damage_dealt();

    when_wrath_is_performed();
    when_running_queued_events_until(2.01);

    // [Damage] = base_dmg + spell_power * spell_coefficient
    // [807 - 836] = [236 - 265] + 1000 * (2 / 3.5)
    then_damage_dealt_is_in_range(807, 836);
}

void TestWrath::test_crit_dmg() {
    given_a_guaranteed_magic_crit(MagicSchool::Nature);
    given_1000_spell_power();
    given_no_previous_damage_dealt();

    when_wrath_is_performed();
    when_running_queued_events_until(2.01);

    // [Damage] = (base_dmg + spell_power * spell_coefficient) * spell_crit_dmg_modifier
    // [1211 - 1255] = ([236 - 265] + 1000 * (2 / 3.5)) * 1.5
    then_damage_dealt_is_in_range(1211, 1255);
}

void TestWrath::test_crit_dmg_5_of_5_vengeance() {
    given_balance_talent_ranks({{"Improved Moonfire", 5}, {"Vengeance", 5}});
    given_a_guaranteed_magic_crit(MagicSchool::Nature);
    given_1000_spell_power();
    given_no_previous_damage_dealt();

    when_wrath_is_performed();
    when_running_queued_events_until(2.01);

    // [Damage] = (base_dmg + spell_power * spell_coefficient) * spell_crit_dmg_modifier
    // [1615 - 1673] = ([236 - 265] + 1000 * (2 / 3.5)) * 2.0
    then_damage_dealt_is_in_range(1615, 1673);
}

void TestWrath::test_hit_damage_1_of_5_moonfury() {
    given_balance_talent_ranks({{"Nature's Grace", 1}, {"Moonfury", 1}});
    given_a_guaranteed_magic_hit(MagicSchool::Nature);
    given_1000_spell_power();
    given_no_previous_damage_dealt();

    when_wrath_is_performed();
    when_running_queued_events_until(2.01);

    // [Damage] = base_dmg * moonfury + spell_power * spell_coefficient
    // [812 - 841] = [236 * 1.02 - 265 * 1.02] + 1000 * (2 / 3.5)
    then_damage_dealt_is_in_range(812, 841);
}

void TestWrath::test_hit_damage_5_of_5_moonfury() {
    given_balance_talent_ranks({{"Nature's Grace", 1}, {"Moonfury", 5}});
    given_a_guaranteed_magic_hit(MagicSchool::Nature);
    given_1000_spell_power();
    given_no_previous_damage_dealt();

    when_wrath_is_performed();
    when_running_queued_events_until(2.01);

    // [Damage] = base_dmg * moonfury + spell_power * spell_coefficient
    // [831 - 863] = [236 * 1.10 - 265 * 1.10] + 1000 * (2 / 3.5)
    then_damage_dealt_is_in_range(831, 863);
}

void TestWrath::test_cast_time_1_of_5_improved_wrath() {
    given_balance_talent_rank("Improved Wrath", 1);

    when_wrath_is_performed();

    then_next_event_is(EventType::PlayerAction, "1.500");
    then_next_event_is(EventType::CastComplete, "1.900");
}

void TestWrath::test_cast_time_2_of_5_improved_wrath() {
    given_balance_talent_rank("Improved Wrath", 2);

    when_wrath_is_performed();

    then_next_event_is(EventType::PlayerAction, "1.500");
    then_next_event_is(EventType::CastComplete, "1.800");
}

void TestWrath::test_cast_time_3_of_5_improved_wrath() {
    given_balance_talent_rank("Improved Wrath", 3);

    when_wrath_is_performed();

    then_next_event_is(EventType::PlayerAction, "1.500");
    then_next_event_is(EventType::CastComplete, "1.700");
}

void TestWrath::test_cast_time_4_of_5_improved_wrath() {
    given_balance_talent_rank("Improved Wrath", 4);

    when_wrath_is_performed();

    then_next_event_is(EventType::PlayerAction, "1.500");
    then_next_event_is(EventType::CastComplete, "1.600");
}

void TestWrath::test_cast_time_5_of_5_improved_wrath() {
    given_balance_talent_rank("Improved Wrath", 5);

    when_wrath_is_performed();

    then_next_event_is(EventType::PlayerAction, "1.500");
    then_next_event_is(EventType::CastComplete, "1.500");
}

void TestWrath::test_casting_speed_increases_reduces_casting_time() {
    assert(almost_equal(2.0, wrath()->get_cast_time()));

    pchar->get_stats()->increase_casting_speed_mod(100);
    assert(almost_equal(1.0, wrath()->get_cast_time()));

    pchar->get_stats()->decrease_casting_speed_mod(100);
    assert(almost_equal(2.0, wrath()->get_cast_time()));
}

void TestWrath::test_resource_cost_3_of_3_moonglow() {
    given_balance_talent_rank("Moonglow", 3);
    given_druid_has_mana(static_cast<unsigned>(std::round(180 * 0.91) + 1));

    when_wrath_is_performed();
    when_running_queued_events_until(2.01);

    then_druid_has_mana(1);
}

void TestWrath::test_natures_grace_reduces_casting_time() {
    given_a_guaranteed_magic_hit(MagicSchool::Nature);
    given_balance_talent_rank("Improved Wrath", 5);
    given_balance_talent_rank("Nature's Grace", 1);
    pchar->prepare_set_of_combat_iterations();
    static_cast<DruidSpells*>(druid->get_spells())->get_natures_grace()->apply_buff();

    when_wrath_is_performed();

    then_next_event_is(EventType::CastComplete, "1.000", RUN_EVENT);
    assert(!static_cast<DruidSpells*>(druid->get_spells())->get_natures_grace()->is_active());
}

void TestWrath::test_natures_grace_activated_on_spell_crit_if_enabled() {
    given_a_guaranteed_magic_crit(MagicSchool::Nature);
    given_balance_talent_rank("Nature's Grace", 1);
    pchar->prepare_set_of_combat_iterations();
    assert(!static_cast<DruidSpells*>(druid->get_spells())->get_natures_grace()->is_active());

    when_wrath_is_performed();
    when_running_queued_events_until(2.01);

    assert(static_cast<DruidSpells*>(druid->get_spells())->get_natures_grace()->is_active());
}

void TestWrath::test_natures_grace_not_activated_on_spell_crit_if_not_enabled() {
    given_a_guaranteed_magic_crit(MagicSchool::Nature);
    assert(!static_cast<DruidSpells*>(druid->get_spells())->get_natures_grace()->is_active());

    when_wrath_is_performed();
    when_running_queued_events_until(2.01);

    assert(!static_cast<DruidSpells*>(druid->get_spells())->get_natures_grace()->is_active());
}

void TestWrath::when_wrath_is_performed() {
    wrath()->perform();
}
