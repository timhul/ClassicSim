#include "TestMultiShot.h"

#include "Equipment.h"
#include "MultiShot.h"

TestMultiShot::TestMultiShot(EquipmentDb *equipment_db) :
    TestSpellHunter(equipment_db, "Multi-Shot")
{}

void TestMultiShot::test_all() {
    run_mandatory_tests();

    set_up();
    test_hit_dmg_0_of_5_ranged_weapon_specialization();
    tear_down();

    set_up();
    test_hit_dmg_5_of_5_ranged_weapon_specialization();
    tear_down();

    set_up();
    test_hit_dmg_1_of_3_barrage();
    tear_down();

    set_up();
    test_hit_dmg_2_of_3_barrage();
    tear_down();

    set_up();
    test_hit_dmg_3_of_3_barrage();
    tear_down();

    set_up();
    test_crit_dmg_0_of_5_mortal_shots();
    tear_down();

    set_up();
    test_crit_dmg_1_of_5_mortal_shots();
    tear_down();

    set_up();
    test_crit_dmg_2_of_5_mortal_shots();
    tear_down();

    set_up();
    test_crit_dmg_3_of_5_mortal_shots();
    tear_down();

    set_up();
    test_crit_dmg_4_of_5_mortal_shots();
    tear_down();

    set_up();
    test_crit_dmg_5_of_5_mortal_shots();
    tear_down();

    set_up();
    test_crit_dmg_5_of_5_mortal_shots_1_of_3_monster_slaying();
    tear_down();

    set_up();
    test_crit_dmg_5_of_5_mortal_shots_2_of_3_monster_slaying();
    tear_down();

    set_up();
    test_crit_dmg_5_of_5_mortal_shots_3_of_3_monster_slaying();
    tear_down();

    set_up();
    test_crit_dmg_5_of_5_mortal_shots_1_of_3_humanoid_slaying();
    tear_down();

    set_up();
    test_crit_dmg_5_of_5_mortal_shots_2_of_3_humanoid_slaying();
    tear_down();

    set_up();
    test_crit_dmg_5_of_5_mortal_shots_3_of_3_humanoid_slaying();
    tear_down();

    set_up();
    test_mana_cost_1_of_5_efficiency();
    tear_down();

    set_up();
    test_mana_cost_2_of_5_efficiency();
    tear_down();

    set_up();
    test_mana_cost_3_of_5_efficiency();
    tear_down();

    set_up();
    test_mana_cost_4_of_5_efficiency();
    tear_down();

    set_up();
    test_mana_cost_5_of_5_efficiency();
    tear_down();
}

MultiShot* TestMultiShot::multi_shot() {
    auto* spells = dynamic_cast<HunterSpells*>(hunter->get_spells());
    return spells->get_multi_shot();
}

void TestMultiShot::test_name_correct() {
    assert(multi_shot()->get_name() == "Multi-Shot");
}

void TestMultiShot::test_spell_cooldown() {
    assert(almost_equal(10.0, multi_shot()->get_base_cooldown()));
}

void TestMultiShot::test_obeys_global_cooldown() {
    given_hunter_is_on_gcd();

    assert(!multi_shot()->is_available());
}

void TestMultiShot::test_resource_cost() {
    given_hunter_has_mana(230);
    assert(multi_shot()->is_available());

    given_hunter_has_mana(229);
    assert(!multi_shot()->is_available());

    given_hunter_has_mana(230);

    when_multi_shot_is_performed();

    then_hunter_has_mana(0);
}

void TestMultiShot::test_is_ready_conditions() {
    // No conditions not tested in other mandatory tests.
}

void TestMultiShot::test_incurs_global_cooldown() {
    assert(hunter->action_ready());

    when_multi_shot_is_performed();

    assert(!hunter->action_ready());
}

void TestMultiShot::test_hit_dmg_0_of_5_ranged_weapon_specialization() {
    given_target_has_0_armor();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_hit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();

    when_multi_shot_is_performed();

    // [Damage] = base_dmg + (normalized_wpn_speed * AP / 14) + flat_dmg_bonus
    // [450] = 100 + (2.8 * 1000 / 14) + 150
    then_damage_dealt_is(450);
}

void TestMultiShot::test_hit_dmg_5_of_5_ranged_weapon_specialization() {
    given_target_has_0_armor();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_hit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();
    given_5_of_5_ranged_weapon_specialization();

    when_multi_shot_is_performed();

    // [Damage] = (base_dmg + (normalized_wpn_speed * AP / 14) + flat_dmg_bonus) * total_phys_modifier
    // [473] = (100 + (2.8 * 1000 / 14) + 150) * 1.05
    then_damage_dealt_is(473);
}

void TestMultiShot::test_hit_dmg_1_of_3_barrage() {
    given_target_has_0_armor();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_hit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();
    given_1_of_3_barrage();

    when_multi_shot_is_performed();

    // [Damage] = (base_dmg + (normalized_wpn_speed * AP / 14) + flat_dmg_bonus) * barrage_mod
    // [473] = (100 + (2.8 * 1000 / 14) + 150) * 1.05
    then_damage_dealt_is(473);
}

void TestMultiShot::test_hit_dmg_2_of_3_barrage() {
    given_target_has_0_armor();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_hit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();
    given_2_of_3_barrage();

    when_multi_shot_is_performed();

    // [Damage] = (base_dmg + (normalized_wpn_speed * AP / 14) + flat_dmg_bonus) * barrage_mod
    // [495] = (100 + (2.8 * 1000 / 14) + 150) * 1.10
    then_damage_dealt_is(495);
}

void TestMultiShot::test_hit_dmg_3_of_3_barrage() {
    given_target_has_0_armor();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_hit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();
    given_3_of_3_barrage();

    when_multi_shot_is_performed();

    // [Damage] = (base_dmg + (normalized_wpn_speed * AP / 14) + flat_dmg_bonus) * barrage_mod
    // [518] = (100 + (2.8 * 1000 / 14) + 150) * 1.15
    then_damage_dealt_is(518);
}

void TestMultiShot::test_crit_dmg_0_of_5_mortal_shots() {
    given_target_has_0_armor();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_crit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();

    when_multi_shot_is_performed();

    // [Damage] = (base_dmg + (normalized_wpn_speed * AP / 14)) + flat_dmg_bonus) * crit_dmg_modifier
    // [900] = (100 + (2.8 * 1000 / 14) + 150) * 2.0
    then_damage_dealt_is(900);
}

void TestMultiShot::test_crit_dmg_1_of_5_mortal_shots() {
    given_target_has_0_armor();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_crit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();
    given_1_of_5_mortal_shots();

    when_multi_shot_is_performed();

    // [Damage] = (base_dmg + (normalized_wpn_speed * AP / 14)) + flat_dmg_bonus) * crit_dmg_modifier
    // [927] = (100 + (2.8 * 1000 / 14) + 150) * 2.06
    then_damage_dealt_is(927);
}

void TestMultiShot::test_crit_dmg_2_of_5_mortal_shots() {
    given_target_has_0_armor();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_crit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();
    given_2_of_5_mortal_shots();

    when_multi_shot_is_performed();

    // [Damage] = (base_dmg + (normalized_wpn_speed * AP / 14)) + flat_dmg_bonus) * crit_dmg_modifier
    // [954] = (100 + (2.8 * 1000 / 14) + 150) * 2.12
    then_damage_dealt_is(954);
}

void TestMultiShot::test_crit_dmg_3_of_5_mortal_shots() {
    given_target_has_0_armor();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_crit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();
    given_3_of_5_mortal_shots();

    when_multi_shot_is_performed();

    // [Damage] = (base_dmg + (normalized_wpn_speed * AP / 14)) + flat_dmg_bonus) * crit_dmg_modifier
    // [981] = (100 + (2.8 * 1000 / 14) + 150) * 2.18
    then_damage_dealt_is(981);
}

void TestMultiShot::test_crit_dmg_4_of_5_mortal_shots() {
    given_target_has_0_armor();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_crit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();
    given_4_of_5_mortal_shots();

    when_multi_shot_is_performed();

    // [Damage] = (base_dmg + (normalized_wpn_speed * AP / 14)) + flat_dmg_bonus) * crit_dmg_modifier
    // [1008] = (100 + (2.8 * 1000 / 14) + 150) * 2.24
    then_damage_dealt_is(1008);
}

void TestMultiShot::test_crit_dmg_5_of_5_mortal_shots() {
    given_target_has_0_armor();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_crit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();
    given_5_of_5_mortal_shots();

    when_multi_shot_is_performed();

    // [Damage] = (base_dmg + (normalized_wpn_speed * AP / 14)) + flat_dmg_bonus) * crit_dmg_modifier
    // [1035] = (100 + (2.8 * 1000 / 14) + 150) * 2.30
    then_damage_dealt_is(1035);
}

void TestMultiShot::test_crit_dmg_5_of_5_mortal_shots_1_of_3_monster_slaying() {
    given_target_is_beast();
    given_target_has_0_armor();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_crit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();
    given_5_of_5_mortal_shots();
    given_1_of_3_monster_slaying();

    when_multi_shot_is_performed();

    // [Damage] = (base_dmg + (normalized_wpn_speed * AP / 14)) + flat_dmg_bonus) * crit_dmg_modifier * total_phys_modifier
    // [1050] = (100 + (2.8 * 1000 / 14) + 150) * 2.31 * 1.01
    then_damage_dealt_is(1050);
}

void TestMultiShot::test_crit_dmg_5_of_5_mortal_shots_2_of_3_monster_slaying() {
    given_target_is_beast();
    given_target_has_0_armor();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_crit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();
    given_5_of_5_mortal_shots();
    given_2_of_3_monster_slaying();

    when_multi_shot_is_performed();

    // [Damage] = (base_dmg + (normalized_wpn_speed * AP / 14)) + flat_dmg_bonus) * crit_dmg_modifier * total_phys_modifier
    // [1065] = (100 + (2.8 * 1000 / 14) + 150) * 2.32 * 1.02
    then_damage_dealt_is(1065);
}

void TestMultiShot::test_crit_dmg_5_of_5_mortal_shots_3_of_3_monster_slaying() {
    given_target_is_beast();
    given_target_has_0_armor();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_crit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();
    given_5_of_5_mortal_shots();
    given_3_of_3_monster_slaying();

    when_multi_shot_is_performed();

    // [Damage] = (base_dmg + (normalized_wpn_speed * AP / 14)) + flat_dmg_bonus) * crit_dmg_modifier * total_phys_modifier
    // [1080] = (100 + (2.8 * 1000 / 14) + 150) * 2.33 * 1.03
    then_damage_dealt_is(1080);
}

void TestMultiShot::test_crit_dmg_5_of_5_mortal_shots_1_of_3_humanoid_slaying() {
    given_target_is_humanoid();
    given_target_has_0_armor();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_crit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();
    given_5_of_5_mortal_shots();
    given_1_of_3_humanoid_slaying();

    when_multi_shot_is_performed();

    // [Damage] = (base_dmg + (normalized_wpn_speed * AP / 14)) + flat_dmg_bonus) * crit_dmg_modifier * total_phys_modifier
    // [1050] = (100 + (2.8 * 1000 / 14) + 150) * 2.31 * 1.01
    then_damage_dealt_is(1050);
}

void TestMultiShot::test_crit_dmg_5_of_5_mortal_shots_2_of_3_humanoid_slaying() {
    given_target_is_humanoid();
    given_target_has_0_armor();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_crit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();
    given_5_of_5_mortal_shots();
    given_2_of_3_humanoid_slaying();

    when_multi_shot_is_performed();

    // [Damage] = (base_dmg + (normalized_wpn_speed * AP / 14)) + flat_dmg_bonus) * crit_dmg_modifier * total_phys_modifier
    // [1065] = (100 + (2.8 * 1000 / 14) + 150) * 2.32 * 1.02
    then_damage_dealt_is(1065);
}

void TestMultiShot::test_crit_dmg_5_of_5_mortal_shots_3_of_3_humanoid_slaying() {
    given_target_is_humanoid();
    given_target_has_0_armor();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_crit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();
    given_5_of_5_mortal_shots();
    given_3_of_3_humanoid_slaying();

    when_multi_shot_is_performed();

    // [Damage] = (base_dmg + (normalized_wpn_speed * AP / 14)) + flat_dmg_bonus) * crit_dmg_modifier * total_phys_modifier
    // [1080] = (100 + (2.8 * 1000 / 14) + 150) * 2.33 * 1.03
    then_damage_dealt_is(1080);
}

void TestMultiShot::test_mana_cost_1_of_5_efficiency() {
    given_1_of_5_efficiency();
    given_hunter_has_mana(225);
    assert(multi_shot()->is_available());

    given_hunter_has_mana(224);
    assert(!multi_shot()->is_available());

    given_hunter_has_mana(225);

    when_multi_shot_is_performed();

    then_hunter_has_mana(0);
}

void TestMultiShot::test_mana_cost_2_of_5_efficiency() {
    given_2_of_5_efficiency();
    given_hunter_has_mana(221);
    assert(multi_shot()->is_available());

    given_hunter_has_mana(220);
    assert(!multi_shot()->is_available());

    given_hunter_has_mana(221);

    when_multi_shot_is_performed();

    then_hunter_has_mana(0);
}

void TestMultiShot::test_mana_cost_3_of_5_efficiency() {
    given_3_of_5_efficiency();
    given_hunter_has_mana(216);
    assert(multi_shot()->is_available());

    given_hunter_has_mana(215);
    assert(!multi_shot()->is_available());

    given_hunter_has_mana(216);

    when_multi_shot_is_performed();

    then_hunter_has_mana(0);
}

void TestMultiShot::test_mana_cost_4_of_5_efficiency() {
    given_4_of_5_efficiency();
    given_hunter_has_mana(212);
    assert(multi_shot()->is_available());

    given_hunter_has_mana(211);
    assert(!multi_shot()->is_available());

    given_hunter_has_mana(212);

    when_multi_shot_is_performed();

    then_hunter_has_mana(0);
}

void TestMultiShot::test_mana_cost_5_of_5_efficiency() {
    given_5_of_5_efficiency();
    given_hunter_has_mana(207);
    assert(multi_shot()->is_available());

    given_hunter_has_mana(206);
    assert(!multi_shot()->is_available());

    given_hunter_has_mana(207);

    when_multi_shot_is_performed();

    then_hunter_has_mana(0);
}

void TestMultiShot::when_multi_shot_is_performed() {
    if (pchar->get_equipment()->get_ranged() == nullptr)
        given_a_ranged_weapon_with_100_min_max_dmg();

    multi_shot()->perform();
}
