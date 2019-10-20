#include "TestStarfire.h"

#include <cassert>
#include <cmath>

#include "Buff.h"
#include "CharacterStats.h"
#include "Druid.h"
#include "DruidSpells.h"
#include "Event.h"
#include "Starfire.h"

TestStarfire::TestStarfire(EquipmentDb* equipment_db) :
    TestSpellDruid(equipment_db, "Starfire")
{}

void TestStarfire::test_all() {
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
    test_cast_time_1_of_5_improved_starfire();
    tear_down();

    set_up();
    test_cast_time_2_of_5_improved_starfire();
    tear_down();

    set_up();
    test_cast_time_3_of_5_improved_starfire();
    tear_down();

    set_up();
    test_cast_time_4_of_5_improved_starfire();
    tear_down();

    set_up();
    test_cast_time_5_of_5_improved_starfire();
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

void TestStarfire::test_name_correct() {
    assert(starfire()->get_name() == "Starfire");
}

void TestStarfire::test_spell_cooldown() {
    assert(almost_equal(0.0, starfire()->get_base_cooldown()));
}

void TestStarfire::test_whether_spell_causes_global_cooldown() {
    assert(druid->action_ready());

    when_starfire_is_performed();

    assert(!druid->action_ready());
}

void TestStarfire::test_how_spell_observes_global_cooldown() {

}

void TestStarfire::test_is_ready_conditions() {
    assert(starfire()->get_spell_status() == SpellStatus::Available);
}

void TestStarfire::test_resource_cost() {
    given_druid_has_mana(341);

    when_starfire_is_performed();
    when_running_queued_events_until(3.501);

    then_druid_has_mana(1);
}

void TestStarfire::test_hit_dmg() {
    given_a_guaranteed_magic_hit(MagicSchool::Arcane);
    given_1000_spell_power();
    given_no_previous_damage_dealt();

    when_starfire_is_performed();
    when_running_queued_events_until(3.501);

    // [Damage] = base_dmg + spell_power * spell_coefficient
    // [1495 - 1584] = [495 - 584] + 1000 * (3.5 / 3.5)
    then_damage_dealt_is_in_range(1495, 1584);
}

void TestStarfire::test_crit_dmg() {
    given_a_guaranteed_magic_crit(MagicSchool::Arcane);
    given_1000_spell_power();
    given_no_previous_damage_dealt();

    when_starfire_is_performed();
    when_running_queued_events_until(3.501);

    // [Damage] = (base_dmg + spell_power * spell_coefficient) * spell_crit_dmg_modifier
    // [2243 - 2376] = ([495 - 584] + 1000 * (3.5 / 3.5)) * 1.5
    then_damage_dealt_is_in_range(2243, 2376);
}

void TestStarfire::test_crit_dmg_5_of_5_vengeance() {
    given_balance_talent_ranks({{"Improved Moonfire", 5}, {"Vengeance", 5}});
    given_a_guaranteed_magic_crit(MagicSchool::Arcane);
    given_1000_spell_power();
    given_no_previous_damage_dealt();

    when_starfire_is_performed();
    when_running_queued_events_until(3.501);

    // [Damage] = (base_dmg + spell_power * spell_coefficient) * spell_crit_dmg_modifier
    // [2990 - 3168] = ([495 - 584] + 1000 * (3.5 / 3.5)) * 2
    then_damage_dealt_is_in_range(2990, 3168);
}

void TestStarfire::test_hit_damage_1_of_5_moonfury() {
    given_balance_talent_ranks({{"Nature's Grace", 1}, {"Moonfury", 1}});
    given_a_guaranteed_magic_hit(MagicSchool::Arcane);
    given_1000_spell_power();
    given_no_previous_damage_dealt();

    when_starfire_is_performed();
    when_running_queued_events_until(3.501);

    // [Damage] = base_dmg * moonfury + spell_power * spell_coefficient
    // [1505 - 1596] = [495 * 1.02 - 584 * 1.02] + 1000 * (3.5 / 3.5)
    then_damage_dealt_is_in_range(1505, 1596);
}

void TestStarfire::test_hit_damage_5_of_5_moonfury() {
    given_balance_talent_ranks({{"Nature's Grace", 1}, {"Moonfury", 5}});
    given_a_guaranteed_magic_hit(MagicSchool::Arcane);
    given_1000_spell_power();
    given_no_previous_damage_dealt();

    when_starfire_is_performed();
    when_running_queued_events_until(3.501);

    // [Damage] = base_dmg * moonfury + spell_power * spell_coefficient
    // [1545 - 1642] = [495 * 1.10 - 584 * 1.10] + 1000 * (3.5 / 3.5)
    then_damage_dealt_is_in_range(1545, 1642);
}

void TestStarfire::test_cast_time_1_of_5_improved_starfire() {
    given_balance_talent_rank("Improved Starfire", 1);

    when_starfire_is_performed();

    then_next_event_is(EventType::PlayerAction, "1.500");
    then_next_event_is(EventType::CastComplete, "3.400");
}

void TestStarfire::test_cast_time_2_of_5_improved_starfire() {
    given_balance_talent_rank("Improved Starfire", 2);

    when_starfire_is_performed();

    then_next_event_is(EventType::PlayerAction, "1.500");
    then_next_event_is(EventType::CastComplete, "3.300");
}

void TestStarfire::test_cast_time_3_of_5_improved_starfire() {
    given_balance_talent_rank("Improved Starfire", 3);

    when_starfire_is_performed();

    then_next_event_is(EventType::PlayerAction, "1.500");
    then_next_event_is(EventType::CastComplete, "3.200");
}

void TestStarfire::test_cast_time_4_of_5_improved_starfire() {
    given_balance_talent_rank("Improved Starfire", 4);

    when_starfire_is_performed();

    then_next_event_is(EventType::PlayerAction, "1.500");
    then_next_event_is(EventType::CastComplete, "3.100");
}

void TestStarfire::test_cast_time_5_of_5_improved_starfire() {
    given_balance_talent_rank("Improved Starfire", 5);

    when_starfire_is_performed();

    then_next_event_is(EventType::PlayerAction, "1.500");
    then_next_event_is(EventType::CastComplete, "3.000");
}

void TestStarfire::test_casting_speed_increases_reduces_casting_time() {
    assert(almost_equal(3.5, starfire()->get_cast_time()));

    pchar->get_stats()->increase_casting_speed_mod(100);
    assert(almost_equal(1.75, starfire()->get_cast_time()));

    pchar->get_stats()->decrease_casting_speed_mod(100);
    assert(almost_equal(3.5, starfire()->get_cast_time()));
}

void TestStarfire::test_resource_cost_3_of_3_moonglow() {
    given_balance_talent_rank("Moonglow", 3);
    given_druid_has_mana(static_cast<unsigned>(std::round(340 * 0.91) + 1));

    when_starfire_is_performed();
    when_running_queued_events_until(3.501);

    then_druid_has_mana(1);
}

void TestStarfire::test_natures_grace_reduces_casting_time() {
    given_a_guaranteed_magic_hit(MagicSchool::Arcane);
    given_balance_talent_rank("Nature's Grace", 1);
    given_balance_talent_rank("Improved Starfire", 5);
    pchar->prepare_set_of_combat_iterations();
    dynamic_cast<DruidSpells*>(druid->get_spells())->get_natures_grace()->apply_buff();

    when_starfire_is_performed();

    then_next_event_is(EventType::PlayerAction, "1.500");
    then_next_event_is(EventType::CastComplete, "2.500", RUN_EVENT);
    assert(!dynamic_cast<DruidSpells*>(druid->get_spells())->get_natures_grace()->is_active());
}

void TestStarfire::test_natures_grace_activated_on_spell_crit_if_enabled() {
    given_a_guaranteed_magic_crit(MagicSchool::Arcane);
    given_balance_talent_rank("Nature's Grace", 1);
    pchar->prepare_set_of_combat_iterations();
    assert(!dynamic_cast<DruidSpells*>(druid->get_spells())->get_natures_grace()->is_active());

    when_starfire_is_performed();
    when_running_queued_events_until(3.51);

    assert(dynamic_cast<DruidSpells*>(druid->get_spells())->get_natures_grace()->is_active());
}

void TestStarfire::test_natures_grace_not_activated_on_spell_crit_if_not_enabled() {
    given_a_guaranteed_magic_crit(MagicSchool::Arcane);
    assert(!dynamic_cast<DruidSpells*>(druid->get_spells())->get_natures_grace()->is_active());

    when_starfire_is_performed();
    when_running_queued_events_until(3.51);

    assert(!dynamic_cast<DruidSpells*>(druid->get_spells())->get_natures_grace()->is_active());
}

void TestStarfire::when_starfire_is_performed() {
    starfire()->perform();
}
