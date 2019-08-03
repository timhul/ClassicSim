#include "TestShred.h"

#include "Buff.h"
#include "CatForm.h"
#include "Druid.h"
#include "DruidSpells.h"
#include "Shred.h"

TestShred::TestShred(EquipmentDb* equipment_db) :
    TestSpellDruid(equipment_db, "Shred")
{}

void TestShred::test_all() {
    run_mandatory_tests();

    set_up();
    test_resource_cost_1_of_2_improved_shred();
    tear_down();

    set_up();
    test_resource_cost_2_of_2_improved_shred();
    tear_down();

    set_up();
    test_hit_dmg();
    tear_down();

    set_up();
    test_crit_dmg();
    tear_down();

    set_up();
    test_shred_awards_combo_points();
    tear_down();
}

void TestShred::test_name_correct() {
    assert(shred()->get_name() == "Shred");
}

void TestShred::test_spell_cooldown() {
    assert(almost_equal(0.0, shred()->get_base_cooldown()));
}

void TestShred::test_whether_spell_causes_global_cooldown() {
    given_druid_in_cat_form();
    given_engine_priority_at(0.51);
    assert(druid->action_ready());

    when_shred_is_performed();

    assert(!druid->action_ready());
}

void TestShred::test_how_spell_observes_global_cooldown() {

}

void TestShred::test_resource_cost() {
    given_druid_in_cat_form();
    given_a_guaranteed_melee_ability_hit();
    assert(druid->get_resource_level(ResourceType::Energy) == 100);
    given_engine_priority_at(0.51);

    when_shred_is_performed();

    then_druid_has_energy(40);
}

void TestShred::test_is_ready_conditions() {
    assert(shred()->get_spell_status() == SpellStatus::InCasterForm);

    given_druid_in_cat_form();
    given_engine_priority_at(0.51);

    assert(shred()->get_spell_status() == SpellStatus::Available);
}

void TestShred::test_resource_cost_1_of_2_improved_shred() {
    given_feral_talent_rank("Improved Shred", 1);
    given_druid_in_cat_form();
    given_a_guaranteed_melee_ability_hit();
    assert(druid->get_resource_level(ResourceType::Energy) == 100);
    given_engine_priority_at(0.51);

    when_shred_is_performed();

    then_druid_has_energy(46);
}

void TestShred::test_resource_cost_2_of_2_improved_shred() {
    given_feral_talent_rank("Improved Shred", 2);
    given_druid_in_cat_form();
    given_a_guaranteed_melee_ability_hit();
    assert(druid->get_resource_level(ResourceType::Energy) == 100);
    given_engine_priority_at(0.51);

    when_shred_is_performed();

    then_druid_has_energy(52);
}

void TestShred::test_hit_dmg() {
    given_target_has_0_armor();
    given_in_melee_attack_mode();
    given_druid_in_cat_form();
    given_1000_melee_ap();
    given_a_guaranteed_melee_ability_hit();
    given_engine_priority_at(0.51);

    when_shred_is_performed();

    // [Damage] = ([min - max] + AP / 14) + bonus_damage
    // [455 - 509] = ([60 * 0.85 - 60 * 1.25] + 1000 / 14) + 180
    then_damage_dealt_is_in_range(455, 509);
}

void TestShred::test_crit_dmg() {
    given_target_has_0_armor();
    given_in_melee_attack_mode();
    given_druid_in_cat_form();
    given_1000_melee_ap();
    given_a_guaranteed_melee_ability_crit();
    given_engine_priority_at(0.51);

    when_shred_is_performed();

    // [Damage] = (([min - max] + AP / 14) + bonus_damage) * crit_dmg_modifier
    // [911 - 1019] = (([60 * 0.85 - 60 * 1.25] + 1000 / 14) + 180) * 2.0
    then_damage_dealt_is_in_range(911, 1019);
}

void TestShred::test_shred_awards_combo_points() {
    given_druid_in_cat_form();
    given_a_guaranteed_melee_ability_hit();
    given_engine_priority_at(0.51);
    assert(druid->get_combo_points() == 0);

    when_shred_is_performed();

    assert(druid->get_combo_points() == 1);
}

void TestShred::when_shred_is_performed() {
    shred()->perform();
}

void TestShred::given_druid_in_cat_form() {
    cat_form()->perform();
}
