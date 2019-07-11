#include "TestScorch.h"

#include "CharacterStats.h"
#include "Event.h"
#include "Scorch.h"
#include "Mage.h"

TestScorch::TestScorch(EquipmentDb* equipment_db) :
    TestSpellMage(equipment_db, "Scorch")
{}

void TestScorch::test_all() {
    run_mandatory_tests();

    set_up();
    test_hit_dmg();
    tear_down();

    set_up();
    test_crit_dmg();
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
}

void TestScorch::test_name_correct() {
    assert(scorch()->get_name() == "Scorch");
}

void TestScorch::test_spell_cooldown() {
    assert(almost_equal(0.0, scorch()->get_base_cooldown()));
}

void TestScorch::test_whether_spell_causes_global_cooldown() {
    assert(mage->action_ready());

    when_scorch_is_performed();

    assert(!mage->action_ready());
}

void TestScorch::test_how_spell_observes_global_cooldown() {

}

void TestScorch::test_is_ready_conditions() {
    assert(scorch()->get_spell_status() == SpellStatus::Available);
}

void TestScorch::test_resource_cost() {
    given_a_guaranteed_melee_ability_hit();
    given_mage_has_mana(151);

    when_scorch_is_performed();
    when_running_queued_events_until(1.501);

    then_mage_has_mana(1);
}

void TestScorch::test_hit_dmg() {
    given_a_guaranteed_magic_hit(MagicSchool::Fire);
    given_1000_spell_power();
    given_no_previous_damage_dealt();

    when_scorch_is_performed();
    when_running_queued_events_until(1.501);

    // [Damage] = base_dmg + spell_power * spell_coefficient
    // [662 - 704] = [233- 275] + 1000 * (1.5 / 3.5)
    then_damage_dealt_is_in_range(662, 704);
}

void TestScorch::test_crit_dmg() {
    given_a_guaranteed_magic_crit(MagicSchool::Fire);
    given_1000_spell_power();
    given_no_previous_damage_dealt();

    when_scorch_is_performed();
    when_running_queued_events_until(1.501);

    // [Damage] = (base_dmg + spell_power * spell_coefficient) * spell_crit_dmg_modifier
    // [992 - 1055] = ([233- 275] + 1000 * (1.5 / 3.5)) * 1.5
    then_damage_dealt_is_in_range(992, 1055);
}

void TestScorch::test_mana_return_1_of_3_master_of_elements() {
    given_a_guaranteed_magic_crit(MagicSchool::Fire);
    given_fire_talent_rank("Master of Elements", 1);
    given_mage_has_mana(1000);

    when_scorch_is_performed();
    when_running_queued_events_until(1.501);

    // [mana] = initial_mana - resource_cost + base_resource_cost * master_of_elements_return
    // [865] = 1000 - 150 + 150 * 0.1
    then_mage_has_mana(865);
}

void TestScorch::test_mana_return_2_of_3_master_of_elements() {
    given_a_guaranteed_magic_crit(MagicSchool::Fire);
    given_fire_talent_rank("Master of Elements", 2);
    given_mage_has_mana(1000);

    when_scorch_is_performed();
    when_running_queued_events_until(1.501);

    // [mana] = initial_mana - resource_cost + base_resource_cost * master_of_elements_return
    // [880] = 1000 - 150 + 150 * 0.2
    then_mage_has_mana(880);
}

void TestScorch::test_mana_return_3_of_3_master_of_elements() {
    given_a_guaranteed_magic_crit(MagicSchool::Fire);
    given_fire_talent_rank("Master of Elements", 3);
    given_mage_has_mana(1000);

    when_scorch_is_performed();
    when_running_queued_events_until(1.501);

    // [mana] = initial_mana - resource_cost + base_resource_cost * master_of_elements_return
    // [895] = 1000 - 150 + 150 * 0.3
    then_mage_has_mana(895);
}

void TestScorch::test_hit_dmg_1_of_5_fire_power() {
    given_a_guaranteed_magic_hit(MagicSchool::Fire);
    given_1000_spell_power();
    given_fire_talent_rank("Fire Power", 1);
    given_no_previous_damage_dealt();

    when_scorch_is_performed();
    when_running_queued_events_until(1.501);

    // [Damage] = (base_dmg + spell_power * spell_coefficient) * fire_power
    // [675 - 718] = ([233- 275] + 1000 * (1.5 / 3.5)) * 1.02
    then_damage_dealt_is_in_range(675, 718);
}

void TestScorch::test_hit_dmg_5_of_5_fire_power() {
    given_a_guaranteed_magic_hit(MagicSchool::Fire);
    given_1000_spell_power();
    given_fire_talent_rank("Fire Power", 5);
    given_no_previous_damage_dealt();

    when_scorch_is_performed();
    when_running_queued_events_until(1.501);

    // [Damage] = (base_dmg + spell_power * spell_coefficient) * fire_power
    // [728 - 774] = ([233- 275] + 1000 * (1.5 / 3.5)) * 1.10
    then_damage_dealt_is_in_range(728, 774);
}

void TestScorch::test_1_of_5_ignite() {
    given_a_guaranteed_magic_crit(MagicSchool::Fire);
    given_1000_spell_power();
    given_fire_talent_rank("Ignite", 1);
    given_no_previous_damage_dealt();

    when_scorch_is_performed();
    when_running_queued_events_until(2.501);

    // [Scorch Damage] = (base_dmg + spell_power * spell_coefficient) * spell_crit_dmg_modifier
    // [992 - 1055] = ([233- 275] + 1000 * (1.5 / 3.5)) * 1.5

    // [Ignite Damage] = scorch_damage * ignite_percentage / num_ticks
    // [20 - 21] = [992 - 1055] * 0.08 / 4

    // [Total Damage] = scorch_damage + ignite_damage
    // [1012 - 1076] = [992 - 1055] + [20 - 21]
    then_damage_dealt_is_in_range(1012, 1076);
}

void TestScorch::test_5_of_5_ignite() {
    given_a_guaranteed_magic_crit(MagicSchool::Fire);
    given_1000_spell_power();
    given_fire_talent_rank("Ignite", 5);
    given_no_previous_damage_dealt();

    when_scorch_is_performed();
    when_running_queued_events_until(2.501);

    // [Scorch Damage] = (base_dmg + spell_power * spell_coefficient) * spell_crit_dmg_modifier
    // [992 - 1055] = ([233- 275] + 1000 * (1.5 / 3.5)) * 1.5

    // [Ignite Damage] = scorch_damage * ignite_percentage / num_ticks
    // [99 - 106] = [992 - 1055] * 0.4 / 4

    // [Total Damage] = scorch_damage + ignite_damage
    // [1091 - 1161] = [992 - 1055] + [99 - 106]
    then_damage_dealt_is_in_range(1091, 1161);
}

void TestScorch::when_scorch_is_performed() {
    scorch()->perform();
}
