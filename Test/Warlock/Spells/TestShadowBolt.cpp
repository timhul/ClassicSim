#include "TestShadowBolt.h"

#include <cassert>

#include "CharacterStats.h"
#include "Event.h"
#include "Frostbolt.h"
#include "ShadowBolt.h"
#include "Warlock.h"

TestShadowBolt::TestShadowBolt(EquipmentDb* equipment_db_) : TestSpellWarlock(equipment_db_, "Shadow Bolt") {}

void TestShadowBolt::test_all() {
    run_mandatory_tests();

    set_up();
    test_hit_dmg();
    tear_down();

    set_up();
    test_crit_dmg();
    tear_down();

    set_up();
    test_cast_time_1_of_5_bane();
    tear_down();

    set_up();
    test_cast_time_2_of_5_bane();
    tear_down();

    set_up();
    test_cast_time_3_of_5_bane();
    tear_down();

    set_up();
    test_cast_time_4_of_5_bane();
    tear_down();

    set_up();
    test_cast_time_5_of_5_bane();
    tear_down();

    set_up();
    test_resource_cost_1_of_5_cataclysm();
    tear_down();

    set_up();
    test_resource_cost_2_of_5_cataclysm();
    tear_down();

    set_up();
    test_resource_cost_3_of_5_cataclysm();
    tear_down();

    set_up();
    test_resource_cost_4_of_5_cataclysm();
    tear_down();

    set_up();
    test_resource_cost_5_of_5_cataclysm();
    tear_down();

    set_up();
    test_crit_dmg_ruin();
    tear_down();

    set_up();
    test_hit_dmg_demonic_sacrifice();
    tear_down();

    set_up();
    test_crit_dmg_demonic_sacrifice();
    tear_down();

    set_up();
    test_crits_applies_improved_shadow_bolt_debuff_if_talented();
    tear_down();

    set_up();
    test_casting_speed_increases_reduces_casting_time();
    tear_down();
}

void TestShadowBolt::test_name_correct() {
    assert(shadow_bolt()->get_name() == "Shadow Bolt");
}

void TestShadowBolt::test_spell_cooldown() {
    assert(almost_equal(0.0, shadow_bolt()->get_base_cooldown()));
}

void TestShadowBolt::test_whether_spell_causes_global_cooldown() {
    assert(warlock->action_ready());

    when_shadow_bolt_is_performed();

    assert(!warlock->action_ready());
}

void TestShadowBolt::test_how_spell_observes_global_cooldown() {}

void TestShadowBolt::test_is_ready_conditions() {
    assert(shadow_bolt()->get_spell_status() == SpellStatus::Available);
}

void TestShadowBolt::test_resource_cost() {
    given_warlock_has_mana(381);

    when_shadow_bolt_is_performed();
    when_running_queued_events_until(3.01);

    then_warlock_has_mana(1);
}

void TestShadowBolt::test_hit_dmg() {
    given_a_guaranteed_magic_hit(MagicSchool::Shadow);
    given_1000_spell_power();
    given_no_previous_damage_dealt();

    when_shadow_bolt_is_performed();
    when_running_queued_events_until(3.01);

    // [Damage] = base_dmg + spell_power * spell_coefficient
    // [1339 - 1395] = [482 - 538] + 1000 * (3 / 3.5)
    then_damage_dealt_is_in_range(1339, 1395);
}

void TestShadowBolt::test_crit_dmg() {
    given_a_guaranteed_magic_crit(MagicSchool::Shadow);
    given_1000_spell_power();
    given_no_previous_damage_dealt();

    when_shadow_bolt_is_performed();
    when_running_queued_events_until(3.01);

    // [Damage] = (base_dmg + spell_power * spell_coefficient) * spell_crit_dmg_modifier
    // [2009 - 2093] = ([482 - 538] + 1000 * (3 / 3.5)) * 1.5
    then_damage_dealt_is_in_range(2009, 2093);
}

void TestShadowBolt::test_cast_time_1_of_5_bane() {
    given_destruction_talent_rank("Bane", 1);

    when_shadow_bolt_is_performed();

    then_next_event_is(EventType::PlayerAction, "1.500");
    then_next_event_is(EventType::CastComplete, "2.900");
}

void TestShadowBolt::test_cast_time_2_of_5_bane() {
    given_destruction_talent_rank("Bane", 2);

    when_shadow_bolt_is_performed();

    then_next_event_is(EventType::PlayerAction, "1.500");
    then_next_event_is(EventType::CastComplete, "2.800");
}

void TestShadowBolt::test_cast_time_3_of_5_bane() {
    given_destruction_talent_rank("Bane", 3);

    when_shadow_bolt_is_performed();

    then_next_event_is(EventType::PlayerAction, "1.500");
    then_next_event_is(EventType::CastComplete, "2.700");
}

void TestShadowBolt::test_cast_time_4_of_5_bane() {
    given_destruction_talent_rank("Bane", 4);

    when_shadow_bolt_is_performed();

    then_next_event_is(EventType::PlayerAction, "1.500");
    then_next_event_is(EventType::CastComplete, "2.600");
}

void TestShadowBolt::test_cast_time_5_of_5_bane() {
    given_destruction_talent_rank("Bane", 5);

    when_shadow_bolt_is_performed();

    then_next_event_is(EventType::PlayerAction, "1.500");
    then_next_event_is(EventType::CastComplete, "2.500");
}

void TestShadowBolt::test_resource_cost_1_of_5_cataclysm() {
    given_destruction_talent_rank("Cataclysm", 1);
    given_warlock_has_mana(377);

    when_shadow_bolt_is_performed();
    when_running_queued_events_until(3.01);

    then_warlock_has_mana(1);
}

void TestShadowBolt::test_resource_cost_2_of_5_cataclysm() {
    given_destruction_talent_rank("Cataclysm", 2);
    given_warlock_has_mana(373);

    when_shadow_bolt_is_performed();
    when_running_queued_events_until(3.01);

    then_warlock_has_mana(1);
}

void TestShadowBolt::test_resource_cost_3_of_5_cataclysm() {
    given_destruction_talent_rank("Cataclysm", 3);
    given_warlock_has_mana(370);

    when_shadow_bolt_is_performed();
    when_running_queued_events_until(3.01);

    then_warlock_has_mana(1);
}

void TestShadowBolt::test_resource_cost_4_of_5_cataclysm() {
    given_destruction_talent_rank("Cataclysm", 4);
    given_warlock_has_mana(366);

    when_shadow_bolt_is_performed();
    when_running_queued_events_until(3.01);

    then_warlock_has_mana(1);
}

void TestShadowBolt::test_resource_cost_5_of_5_cataclysm() {
    given_destruction_talent_rank("Cataclysm", 5);
    given_warlock_has_mana(362);

    when_shadow_bolt_is_performed();
    when_running_queued_events_until(3.01);

    then_warlock_has_mana(1);
}

void TestShadowBolt::test_crit_dmg_ruin() {
    given_a_guaranteed_magic_crit(MagicSchool::Shadow);
    given_1000_spell_power();
    given_ruin_enabled();
    given_no_previous_damage_dealt();

    when_shadow_bolt_is_performed();
    when_running_queued_events_until(3.01);

    // [Damage] = (base_dmg + spell_power * spell_coefficient) * spell_crit_dmg_modifier
    // [2678 - 2790] = ([482 - 538] + 1000 * (3 / 3.5)) * 2.0
    then_damage_dealt_is_in_range(2678, 2790);
}

void TestShadowBolt::test_hit_dmg_demonic_sacrifice() {
    given_a_guaranteed_magic_hit(MagicSchool::Shadow);
    given_1000_spell_power();
    given_demonology_talent_rank("Demonic Sacrifice", 1);
    given_no_previous_damage_dealt();

    when_shadow_bolt_is_performed();
    when_running_queued_events_until(3.01);

    // [Damage] = (base_dmg + spell_power * spell_coefficient) * demonic_sacrifice
    // [1540 - 1604] = ([482 - 538] + 1000 * (3 / 3.5)) * 1.15
    then_damage_dealt_is_in_range(1540, 1604);
}

void TestShadowBolt::test_crit_dmg_demonic_sacrifice() {
    given_a_guaranteed_magic_crit(MagicSchool::Shadow);
    given_1000_spell_power();
    given_demonology_talent_rank("Demonic Sacrifice", 1);
    given_no_previous_damage_dealt();

    when_shadow_bolt_is_performed();
    when_running_queued_events_until(3.01);

    // [Damage] = (base_dmg + spell_power * spell_coefficient) * demonic_sacrifice * spell_crit_dmg_modifier
    // [2310 - 2407] = ([482 - 538] + 1000 * (3 / 3.5)) * 1.15 * 1.5
    then_damage_dealt_is_in_range(2310, 2407);
}

void TestShadowBolt::test_crits_applies_improved_shadow_bolt_debuff_if_talented() {
    given_a_guaranteed_magic_crit(MagicSchool::Shadow);
    given_1000_spell_power();
    given_destruction_talent_rank("Improved Shadow Bolt", 5);
    given_no_previous_damage_dealt();

    when_shadow_bolt_is_performed();
    when_running_queued_events_until(3.01);

    assert(almost_equal(1.20, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Shadow, ConsumeCharge::No)));
}

void TestShadowBolt::test_casting_speed_increases_reduces_casting_time() {
    assert(almost_equal(3.0, shadow_bolt()->get_cast_time()));

    pchar->get_stats()->increase_casting_speed_mod(100);
    assert(almost_equal(1.5, shadow_bolt()->get_cast_time()));

    pchar->get_stats()->decrease_casting_speed_mod(100);
    assert(almost_equal(3.0, shadow_bolt()->get_cast_time()));
}

void TestShadowBolt::when_shadow_bolt_is_performed() {
    shadow_bolt()->perform();
}
