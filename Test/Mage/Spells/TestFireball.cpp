#include "TestFireball.h"

#include "CharacterStats.h"
#include "Event.h"
#include "Fireball.h"
#include "Mage.h"

TestFireball::TestFireball(EquipmentDb* equipment_db) :
    TestSpellMage(equipment_db, "Fireball")
{}

void TestFireball::test_all() {
    run_mandatory_tests();

    set_up();
    test_hit_dmg();
    tear_down();

    set_up();
    test_crit_dmg();
    tear_down();

    set_up();
    test_cast_time_1_of_5_improved_fireball();
    tear_down();

    set_up();
    test_cast_time_2_of_5_improved_fireball();
    tear_down();

    set_up();
    test_cast_time_3_of_5_improved_fireball();
    tear_down();

    set_up();
    test_cast_time_4_of_5_improved_fireball();
    tear_down();

    set_up();
    test_cast_time_5_of_5_improved_fireball();
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
    test_hit_dmg_1_of_5_fire_power();
    tear_down();

    set_up();
    test_hit_dmg_5_of_5_fire_power();
    tear_down();

    set_up();
    test_1_of_5_ignite();
    tear_down();

    set_up();
    test_5_of_5_ignite();
    tear_down();

    set_up(false);
    test_hit_dmg_arcane_power();
    tear_down();

    set_up();
    test_casting_speed_increases_reduces_casting_time();
    tear_down();
}

void TestFireball::test_name_correct() {
    assert(fireball()->get_name() == "Fireball");
}

void TestFireball::test_spell_cooldown() {
    assert(almost_equal(0.0, fireball()->get_base_cooldown()));
}

void TestFireball::test_whether_spell_causes_global_cooldown() {
    assert(mage->action_ready());

    when_fireball_is_performed();

    assert(!mage->action_ready());
}

void TestFireball::test_how_spell_observes_global_cooldown() {

}

void TestFireball::test_is_ready_conditions() {
    assert(fireball()->get_spell_status() == SpellStatus::Available);
}

void TestFireball::test_resource_cost() {
    given_mage_has_mana(411);

    when_fireball_is_performed();
    when_running_queued_events_until(3.501);

    then_mage_has_mana(1);
}

void TestFireball::test_hit_dmg() {
    given_a_guaranteed_magic_hit(MagicSchool::Fire);
    given_1000_spell_power();
    given_no_previous_damage_dealt();

    when_fireball_is_performed();
    when_running_queued_events_until(3.501);

    // [Damage] = base_dmg + spell_power * spell_coefficient
    // [1596 - 1761] = [596 - 761] + 1000 * 1.0
    then_damage_dealt_is_in_range(1596, 1761);
}

void TestFireball::test_crit_dmg() {
    given_a_guaranteed_magic_crit(MagicSchool::Fire);
    given_1000_spell_power();
    given_no_previous_damage_dealt();

    when_fireball_is_performed();
    when_running_queued_events_until(3.501);

    // [Damage] = (base_dmg + spell_power * spell_coefficient) * spell_crit_dmg_modifier
    // [2394 - 2642] = ([596 - 761] + 1000 * 1.0) * 1.5
    then_damage_dealt_is_in_range(2394, 2642);
}

void TestFireball::test_cast_time_1_of_5_improved_fireball() {
    given_fire_talent_rank("Improved Fireball", 1);

    when_fireball_is_performed();

    then_next_event_is(EventType::PlayerAction, "1.500");
    then_next_event_is(EventType::CastComplete, "3.400");
}

void TestFireball::test_cast_time_2_of_5_improved_fireball() {
    given_fire_talent_rank("Improved Fireball", 2);

    when_fireball_is_performed();

    then_next_event_is(EventType::PlayerAction, "1.500");
    then_next_event_is(EventType::CastComplete, "3.300");
}

void TestFireball::test_cast_time_3_of_5_improved_fireball() {
    given_fire_talent_rank("Improved Fireball", 3);

    when_fireball_is_performed();

    then_next_event_is(EventType::PlayerAction, "1.500");
    then_next_event_is(EventType::CastComplete, "3.200");
}

void TestFireball::test_cast_time_4_of_5_improved_fireball() {
    given_fire_talent_rank("Improved Fireball", 4);

    when_fireball_is_performed();

    then_next_event_is(EventType::PlayerAction, "1.500");
    then_next_event_is(EventType::CastComplete, "3.100");
}

void TestFireball::test_cast_time_5_of_5_improved_fireball() {
    given_fire_talent_rank("Improved Fireball", 5);

    when_fireball_is_performed();

    then_next_event_is(EventType::PlayerAction, "1.500");
    then_next_event_is(EventType::CastComplete, "3.000");
}

void TestFireball::test_mana_return_1_of_3_master_of_elements() {
    given_a_guaranteed_magic_crit(MagicSchool::Fire);
    given_fire_talent_rank("Master of Elements", 1);
    given_mage_has_mana(1000);

    when_fireball_is_performed();
    when_running_queued_events_until(3.501);

    // [mana] = initial_mana - resource_cost + base_resource_cost * master_of_elements_return
    // [631] = 1000 - 410 + 410 * 0.1
    then_mage_has_mana(631);
}

void TestFireball::test_mana_return_2_of_3_master_of_elements() {
    given_a_guaranteed_magic_crit(MagicSchool::Fire);
    given_fire_talent_rank("Master of Elements", 2);
    given_mage_has_mana(1000);

    when_fireball_is_performed();
    when_running_queued_events_until(3.501);

    // [mana] = initial_mana - resource_cost + base_resource_cost * master_of_elements_return
    // [672] = 1000 - 410 + 410 * 0.2
    then_mage_has_mana(672);
}

void TestFireball::test_mana_return_3_of_3_master_of_elements() {
    given_a_guaranteed_magic_crit(MagicSchool::Fire);
    given_fire_talent_rank("Master of Elements", 3);
    given_mage_has_mana(1000);

    when_fireball_is_performed();
    when_running_queued_events_until(3.501);

    // [mana] = initial_mana - resource_cost + base_resource_cost * master_of_elements_return
    // [713] = 1000 - 410 + 410 * 0.3
    then_mage_has_mana(713);
}

void TestFireball::test_hit_dmg_1_of_5_fire_power() {
    given_a_guaranteed_magic_hit(MagicSchool::Fire);
    given_1000_spell_power();
    given_fire_talent_rank("Fire Power", 1);
    given_no_previous_damage_dealt();

    when_fireball_is_performed();
    when_running_queued_events_until(3.501);

    // [Damage] = (base_dmg + spell_power * spell_coefficient) * fire_power
    // [1628 - 1796] = ([596 - 761] + 1000 * 1.0) * 1.02
    then_damage_dealt_is_in_range(1628, 1796);
}

void TestFireball::test_hit_dmg_5_of_5_fire_power() {
    given_a_guaranteed_magic_hit(MagicSchool::Fire);
    given_1000_spell_power();
    given_fire_talent_rank("Fire Power", 5);
    given_no_previous_damage_dealt();

    when_fireball_is_performed();
    when_running_queued_events_until(3.501);

    // [Damage] = (base_dmg + spell_power * spell_coefficient) * fire_power
    // [1756 - 1937] = ([596 - 761] + 1000 * 1.0) * 1.10
    then_damage_dealt_is_in_range(1756, 1937);
}

void TestFireball::test_1_of_5_ignite() {
    given_a_guaranteed_magic_crit(MagicSchool::Fire);
    given_1000_spell_power();
    given_fire_talent_rank("Ignite", 1);
    given_no_previous_damage_dealt();

    when_fireball_is_performed();
    when_running_queued_events_until(4.501);

    // [Fireball Damage] = (base_dmg + spell_power * spell_coefficient) * spell_crit_dmg_modifier
    // [2394 - 2642] = ([596 - 761] + 1000 * 1.0) * 1.5

    // [Ignite Damage] = fireball_damage * ignite_percentage / num_ticks
    // [48 - 53] = [2394 - 2642] * 0.08 / 4

    // [Total Damage] = fireball_damage + ignite_damage
    // [2442 - 2695] = [2394 - 2642] + [48 - 53]
    then_damage_dealt_is_in_range(2442, 2695);
}

void TestFireball::test_5_of_5_ignite() {
    given_a_guaranteed_magic_crit(MagicSchool::Fire);
    given_1000_spell_power();
    given_fire_talent_rank("Ignite", 5);
    given_no_previous_damage_dealt();

    when_fireball_is_performed();
    when_running_queued_events_until(4.501);

    // [Fireball Damage] = (base_dmg + spell_power * spell_coefficient) * spell_crit_dmg_modifier
    // [2394 - 2642] = ([596 - 761] + 1000 * 1.0) * 1.5

    // [Ignite Damage] = fireball_damage * ignite_percentage / num_ticks
    // [239 - 264] = [2394 - 2642] * 0.4 / 4

    // [Total Damage] = fireball_damage + ignite_damage
    // [2633 - 2906] = [2394 - 2642] + [239 - 264]
    then_damage_dealt_is_in_range(2633, 2906);
}

void TestFireball::test_hit_dmg_arcane_power() {
    given_mage_has_mana(534);
    given_a_guaranteed_magic_hit(MagicSchool::Fire);
    given_1000_spell_power();
    given_no_previous_damage_dealt();
    given_arcane_power_is_active();
    given_engine_priority_pushed_forward(1.5);

    when_fireball_is_performed();
    when_running_queued_events_until(5.01);

    // [Damage] = (base_dmg + spell_power * spell_coefficient) * arcane_power * arcane_instability
    // [2137 - 2358] = ([596 - 761] + 1000 * 1.0) * 1.3 * 1.03
    then_damage_dealt_is_in_range(2137, 2358);
    then_mage_has_mana(1);
}

void TestFireball::test_casting_speed_increases_reduces_casting_time() {
    assert(almost_equal(3.5, fireball()->get_cast_time()));

    pchar->get_stats()->increase_casting_speed(100);
    assert(almost_equal(1.75, fireball()->get_cast_time()));

    pchar->get_stats()->decrease_casting_speed(100);
    assert(almost_equal(3.5, fireball()->get_cast_time()));
}

void TestFireball::when_fireball_is_performed() {
    fireball()->perform();
}
