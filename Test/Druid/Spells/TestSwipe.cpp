#include "TestSwipe.h"

#include <cassert>

#include "BearForm.h"
#include "Buff.h"
#include "Druid.h"
#include "DruidSpells.h"
#include "Swipe.h"

TestSwipe::TestSwipe(EquipmentDb* equipment_db) : TestSpellDruid(equipment_db, "Swipe") {}

void TestSwipe::test_all() {
    run_mandatory_tests();

    set_up();
    test_resource_cost_1_of_5_ferocity();
    tear_down();

    set_up();
    test_resource_cost_2_of_5_ferocity();
    tear_down();

    set_up();
    test_resource_cost_3_of_5_ferocity();
    tear_down();

    set_up();
    test_resource_cost_4_of_5_ferocity();
    tear_down();

    set_up();
    test_resource_cost_5_of_5_ferocity();
    tear_down();

    set_up();
    test_hit_dmg();
    tear_down();

    set_up();
    test_crit_dmg();
    tear_down();

    set_up();
    test_swipe_hit_with_0_of_2_primal_fury_awards_0_rage();
    tear_down();

    set_up();
    test_swipe_crit_with_0_of_2_primal_fury_awards_0_rage();
    tear_down();

    set_up();
    test_swipe_hit_with_2_of_2_primal_fury_awards_0_rage();
    tear_down();

    set_up();
    test_swipe_crit_with_2_of_2_primal_fury_awards_5_rage();
    tear_down();
}

void TestSwipe::test_name_correct() {
    assert(swipe()->get_name() == "Swipe");
}

void TestSwipe::test_spell_cooldown() {
    assert(almost_equal(0.0, swipe()->get_base_cooldown()));
}

void TestSwipe::test_whether_spell_causes_global_cooldown() {
    given_druid_in_bear_form();
    given_engine_priority_at(0.51);
    given_druid_has_rage(100);
    assert(druid->action_ready());

    when_swipe_is_performed();

    assert(!druid->action_ready());
}

void TestSwipe::test_how_spell_observes_global_cooldown() {}

void TestSwipe::test_resource_cost() {
    given_druid_in_bear_form();
    given_a_guaranteed_melee_ability_hit();
    given_druid_has_rage(100);
    given_engine_priority_at(0.51);

    when_swipe_is_performed();

    then_druid_has_rage(80);
}

void TestSwipe::test_is_ready_conditions() {
    assert(swipe()->get_spell_status() == SpellStatus::InsufficientResources);

    given_druid_in_bear_form();
    given_engine_priority_at(0.51);

    assert(swipe()->get_spell_status() == SpellStatus::InsufficientResources);

    given_druid_has_rage(100);

    assert(swipe()->get_spell_status() == SpellStatus::Available);
}

void TestSwipe::test_resource_cost_1_of_5_ferocity() {
    given_feral_talent_rank("Ferocity", 1);
    given_druid_in_bear_form();
    given_a_guaranteed_melee_ability_hit();
    given_druid_has_rage(100);
    given_engine_priority_at(0.51);

    when_swipe_is_performed();

    then_druid_has_rage(81);
}

void TestSwipe::test_resource_cost_2_of_5_ferocity() {
    given_feral_talent_rank("Ferocity", 2);
    given_druid_in_bear_form();
    given_a_guaranteed_melee_ability_hit();
    given_druid_has_rage(100);
    given_engine_priority_at(0.51);

    when_swipe_is_performed();

    then_druid_has_rage(82);
}

void TestSwipe::test_resource_cost_3_of_5_ferocity() {
    given_feral_talent_rank("Ferocity", 3);
    given_druid_in_bear_form();
    given_a_guaranteed_melee_ability_hit();
    given_druid_has_rage(100);
    given_engine_priority_at(0.51);

    when_swipe_is_performed();

    then_druid_has_rage(83);
}

void TestSwipe::test_resource_cost_4_of_5_ferocity() {
    given_feral_talent_rank("Ferocity", 4);
    given_druid_in_bear_form();
    given_a_guaranteed_melee_ability_hit();
    given_druid_has_rage(100);
    given_engine_priority_at(0.51);

    when_swipe_is_performed();

    then_druid_has_rage(84);
}

void TestSwipe::test_resource_cost_5_of_5_ferocity() {
    given_feral_talent_rank("Ferocity", 5);
    given_druid_in_bear_form();
    given_a_guaranteed_melee_ability_hit();
    given_druid_has_rage(100);
    given_engine_priority_at(0.51);

    when_swipe_is_performed();

    then_druid_has_rage(85);
}

void TestSwipe::test_hit_dmg_1_of_2_savage_fury() {
    given_target_has_0_armor();
    given_in_melee_attack_mode();
    given_druid_in_bear_form();
    given_1000_melee_ap();
    given_a_guaranteed_melee_ability_hit();
    given_engine_priority_at(0.51);
    given_druid_has_rage(100);

    when_swipe_is_performed();

    // [Damage] = bonus_damage * 1.1 = 91.3
    then_damage_dealt_is_in_range(91, 92);
}

void TestSwipe::test_hit_dmg_2_of_2_savage_fury() {
    given_target_has_0_armor();
    given_in_melee_attack_mode();
    given_druid_in_bear_form();
    given_1000_melee_ap();
    given_a_guaranteed_melee_ability_hit();
    given_engine_priority_at(0.51);
    given_druid_has_rage(100);

    when_swipe_is_performed();

    // [Damage] = bonus_damage = 99.6
    then_damage_dealt_is_in_range(99, 100);
}

void TestSwipe::test_hit_dmg() {
    given_target_has_0_armor();
    given_in_melee_attack_mode();
    given_druid_in_bear_form();
    given_1000_melee_ap();
    given_a_guaranteed_melee_ability_hit();
    given_engine_priority_at(0.51);
    given_druid_has_rage(100);

    when_swipe_is_performed();

    // [Damage] = bonus_damage = 83
    then_damage_dealt_is_in_range(82, 84);
}

void TestSwipe::test_crit_dmg() {
    given_target_has_0_armor();
    given_in_melee_attack_mode();
    given_druid_in_bear_form();
    given_1000_melee_ap();
    given_a_guaranteed_melee_ability_crit();
    given_engine_priority_at(0.51);
    given_druid_has_rage(100);

    when_swipe_is_performed();

    // [Damage] = bonus_damage * crit_dmg_modifier = 83*2 = 166
    then_damage_dealt_is_in_range(165, 167);
}

void TestSwipe::test_swipe_hit_with_0_of_2_primal_fury_awards_0_rage() {
    given_druid_in_bear_form();
    given_a_guaranteed_melee_ability_crit();
    given_engine_priority_at(0.51);
    given_druid_has_rage(100);

    when_swipe_is_performed();

    then_druid_has_rage(80);
}

void TestSwipe::test_swipe_crit_with_0_of_2_primal_fury_awards_0_rage() {
    given_druid_in_bear_form();
    given_a_guaranteed_melee_ability_crit();
    given_engine_priority_at(0.51);
    given_druid_has_rage(100);

    when_swipe_is_performed();

    then_druid_has_rage(80);
}

void TestSwipe::test_swipe_hit_with_2_of_2_primal_fury_awards_0_rage() {
    given_feral_talent_ranks({{"Sharpened Claws", 3}, {"Primal Fury", 2}});
    pchar->prepare_set_of_combat_iterations();
    given_druid_in_bear_form();
    given_a_guaranteed_melee_ability_hit();
    given_engine_priority_at(0.51);
    given_druid_has_rage(100);

    when_swipe_is_performed();

    then_druid_has_rage(80);
}

void TestSwipe::test_swipe_crit_with_2_of_2_primal_fury_awards_5_rage() {
    given_feral_talent_ranks({{"Sharpened Claws", 3}, {"Primal Fury", 2}});
    pchar->prepare_set_of_combat_iterations();
    given_druid_in_bear_form();
    given_a_guaranteed_melee_ability_crit();
    given_engine_priority_at(0.51);
    given_druid_has_rage(100);

    when_swipe_is_performed();

    then_druid_has_rage(85);
}

void TestSwipe::when_swipe_is_performed() {
    swipe()->perform();
}

void TestSwipe::given_druid_in_bear_form() {
    bear_form()->perform();
}
