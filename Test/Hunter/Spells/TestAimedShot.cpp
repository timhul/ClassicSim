#include "TestAimedShot.h"

#include "AimedShot.h"
#include "CharacterStats.h"
#include "Equipment.h"
#include "Marksmanship.h"
#include "MultiShot.h"
#include "Talent.h"

TestAimedShot::TestAimedShot(EquipmentDb *equipment_db) :
    TestSpellHunter(equipment_db, "Aimed Shot")
{}

void TestAimedShot::test_all() {
    run_mandatory_tests();

    set_up();
    test_hit_dmg_0_of_5_ranged_weapon_specialization();
    tear_down();

    set_up();
    test_hit_dmg_5_of_5_ranged_weapon_specialization();
    tear_down();

    set_up();
    test_crit_dmg_0_of_5_mortal_shots_0_of_5_slaying();
    tear_down();

    set_up();
    test_crit_dmg_1_of_5_mortal_shots_0_of_5_slaying();
    tear_down();

    set_up();
    test_crit_dmg_2_of_5_mortal_shots_0_of_5_slaying();
    tear_down();

    set_up();
    test_crit_dmg_3_of_5_mortal_shots_0_of_5_slaying();
    tear_down();

    set_up();
    test_crit_dmg_4_of_5_mortal_shots_0_of_5_slaying();
    tear_down();

    set_up();
    test_crit_dmg_5_of_5_mortal_shots_0_of_5_slaying();
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
    test_aimed_shot_adds_player_action_event_on_completion();
    tear_down();

    set_up();
    test_aimed_shot_cast_in_progress_blocks_other_spells();
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

    set_up();
    test_aimed_shot_cast_time_reduced_by_ranged_attack_speed_boosts();
    tear_down();
}

AimedShot* TestAimedShot::aimed_shot() {
    auto* spells = dynamic_cast<HunterSpells*>(hunter->get_spells());
    return spells->get_aimed_shot();
}

MultiShot* TestAimedShot::multi_shot() {
    auto* spells = dynamic_cast<HunterSpells*>(hunter->get_spells());
    return spells->get_multi_shot();
}

void TestAimedShot::test_name_correct() {
    assert(aimed_shot()->get_name() == "Aimed Shot");
}

void TestAimedShot::test_spell_cooldown() {
    assert(almost_equal(10.0, aimed_shot()->get_base_cooldown()));
}

void TestAimedShot::test_obeys_global_cooldown() {
    given_aimed_shot_is_enabled();
    assert(aimed_shot()->is_available());
    given_hunter_is_on_gcd();
    given_hunter_has_mana(310);

    assert(!aimed_shot()->is_available());
}

void TestAimedShot::test_resource_cost() {
    given_aimed_shot_is_enabled();
    given_hunter_has_mana(310);
    assert(aimed_shot()->is_available());

    given_hunter_has_mana(309);
    assert(!aimed_shot()->is_available());

    given_hunter_has_mana(310);

    when_aimed_shot_is_performed();
    when_running_queued_events_until(3.01);

    then_hunter_has_mana(0);
}

void TestAimedShot::test_is_ready_conditions() {
    given_aimed_shot_is_enabled();
    when_aimed_shot_is_performed();
    given_engine_priority_pushed_forward(2.0);
    given_hunter_has_mana(310);

    assert(!aimed_shot()->is_available());
}

void TestAimedShot::test_incurs_global_cooldown() {
    given_aimed_shot_is_enabled();
    assert(hunter->action_ready());

    when_aimed_shot_is_performed();

    assert(!hunter->action_ready());
}

void TestAimedShot::test_hit_dmg_0_of_5_ranged_weapon_specialization() {
    given_target_has_0_armor();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_hit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();
    given_aimed_shot_is_enabled();

    when_aimed_shot_is_performed();
    then_next_event_is("PlayerAction", "1.500");
    then_next_event_is("CastComplete", "3.000", RUN_EVENT);

    // [Damage] = base_dmg + (normalized_wpn_speed * AP / 14) + flat_dmg_bonus
    // [900] = 100 + (2.8 * 1000 / 14) + 600
    then_damage_dealt_is(900);
}

void TestAimedShot::test_hit_dmg_5_of_5_ranged_weapon_specialization() {
    given_target_has_0_armor();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_hit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();
    given_aimed_shot_is_enabled();
    given_5_of_5_ranged_weapon_specialization();

    when_aimed_shot_is_performed();
    then_next_event_is("PlayerAction", "1.500");
    then_next_event_is("CastComplete", "3.000", RUN_EVENT);

    // [Damage] = (base_dmg + (normalized_wpn_speed * AP / 14) + flat_dmg_bonus) * total_phys_modifier
    // [945] = (100 + (2.8 * 1000 / 14) + 600) * 1.05
    then_damage_dealt_is(945);
}

void TestAimedShot::test_crit_dmg_0_of_5_mortal_shots_0_of_5_slaying() {
    given_target_has_0_armor();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_crit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();
    given_aimed_shot_is_enabled();

    when_aimed_shot_is_performed();
    then_next_event_is("PlayerAction", "1.500");
    then_next_event_is("CastComplete", "3.000", RUN_EVENT);

    // [Damage] = (base_dmg + (normalized_wpn_speed * AP / 14)) + flat_dmg_bonus) * crit_dmg_modifier
    // [1800] = (100 + (2.8 * 1000 / 14) + 600) * 2.0
    then_damage_dealt_is(1800);
}

void TestAimedShot::test_crit_dmg_1_of_5_mortal_shots_0_of_5_slaying() {
    given_target_has_0_armor();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_crit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();
    given_aimed_shot_is_enabled();
    given_1_of_5_mortal_shots();

    when_aimed_shot_is_performed();
    then_next_event_is("PlayerAction", "1.500");
    then_next_event_is("CastComplete", "3.000", RUN_EVENT);

    // [Damage] = (base_dmg + (normalized_wpn_speed * AP / 14)) + flat_dmg_bonus) * crit_dmg_modifier
    // [1854] = (100 + (2.8 * 1000 / 14) + 600) * 2.06
    then_damage_dealt_is(1854);
}

void TestAimedShot::test_crit_dmg_2_of_5_mortal_shots_0_of_5_slaying() {
    given_target_has_0_armor();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_crit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();
    given_aimed_shot_is_enabled();
    given_2_of_5_mortal_shots();

    when_aimed_shot_is_performed();
    then_next_event_is("PlayerAction", "1.500");
    then_next_event_is("CastComplete", "3.000", RUN_EVENT);

    // [Damage] = (base_dmg + (normalized_wpn_speed * AP / 14)) + flat_dmg_bonus) * crit_dmg_modifier
    // [1908] = (100 + (2.8 * 1000 / 14) + 600) * 2.12
    then_damage_dealt_is(1908);
}

void TestAimedShot::test_crit_dmg_3_of_5_mortal_shots_0_of_5_slaying() {
    given_target_has_0_armor();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_crit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();
    given_aimed_shot_is_enabled();
    given_3_of_5_mortal_shots();

    when_aimed_shot_is_performed();
    then_next_event_is("PlayerAction", "1.500");
    then_next_event_is("CastComplete", "3.000", RUN_EVENT);

    // [Damage] = (base_dmg + (normalized_wpn_speed * AP / 14)) + flat_dmg_bonus) * crit_dmg_modifier
    // [1962] = (100 + (2.8 * 1000 / 14) + 600) * 2.18
    then_damage_dealt_is(1962);
}

void TestAimedShot::test_crit_dmg_4_of_5_mortal_shots_0_of_5_slaying() {
    given_target_has_0_armor();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_crit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();
    given_aimed_shot_is_enabled();
    given_4_of_5_mortal_shots();

    when_aimed_shot_is_performed();
    then_next_event_is("PlayerAction", "1.500");
    then_next_event_is("CastComplete", "3.000", RUN_EVENT);

    // [Damage] = (base_dmg + (normalized_wpn_speed * AP / 14)) + flat_dmg_bonus) * crit_dmg_modifier
    // [2016] = (100 + (2.8 * 1000 / 14) + 600) * 2.24
    then_damage_dealt_is(2016);
}

void TestAimedShot::test_crit_dmg_5_of_5_mortal_shots_0_of_5_slaying() {
    given_target_has_0_armor();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_crit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();
    given_aimed_shot_is_enabled();
    given_5_of_5_mortal_shots();

    when_aimed_shot_is_performed();
    then_next_event_is("PlayerAction", "1.500");
    then_next_event_is("CastComplete", "3.000", RUN_EVENT);

    // [Damage] = (base_dmg + (normalized_wpn_speed * AP / 14)) + flat_dmg_bonus) * crit_dmg_modifier
    // [2070] = (100 + (2.8 * 1000 / 14) + 600) * 2.30
    then_damage_dealt_is(2070);
}

void TestAimedShot::test_crit_dmg_5_of_5_mortal_shots_1_of_3_monster_slaying() {
    given_target_has_0_armor();
    given_target_is_beast();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_crit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();
    given_aimed_shot_is_enabled();
    given_5_of_5_mortal_shots();
    given_1_of_3_monster_slaying();

    when_aimed_shot_is_performed();
    then_next_event_is("PlayerAction", "1.500");
    then_next_event_is("CastComplete", "3.000", RUN_EVENT);

    // [Damage] = (base_dmg + (normalized_wpn_speed * AP / 14)) + flat_dmg_bonus) * crit_dmg_modifier * total_phys_modifier
    // [2100] = (100 + (2.8 * 1000 / 14) + 600) * 2.31 * 1.01
    then_damage_dealt_is(2100);
}

void TestAimedShot::test_crit_dmg_5_of_5_mortal_shots_2_of_3_monster_slaying() {
    given_target_has_0_armor();
    given_target_is_beast();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_crit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();
    given_aimed_shot_is_enabled();
    given_5_of_5_mortal_shots();
    given_2_of_3_monster_slaying();

    when_aimed_shot_is_performed();
    then_next_event_is("PlayerAction", "1.500");
    then_next_event_is("CastComplete", "3.000", RUN_EVENT);

    // [Damage] = (base_dmg + (normalized_wpn_speed * AP / 14)) + flat_dmg_bonus) * crit_dmg_modifier * total_phys_modifier
    // [2130] = (100 + (2.8 * 1000 / 14) + 600) * 2.32 * 1.02
    then_damage_dealt_is(2130);
}

void TestAimedShot::test_crit_dmg_5_of_5_mortal_shots_3_of_3_monster_slaying() {
    given_target_has_0_armor();
    given_target_is_beast();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_crit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();
    given_aimed_shot_is_enabled();
    given_5_of_5_mortal_shots();
    given_3_of_3_monster_slaying();

    when_aimed_shot_is_performed();
    then_next_event_is("PlayerAction", "1.500");
    then_next_event_is("CastComplete", "3.000", RUN_EVENT);

    // [Damage] = (base_dmg + (normalized_wpn_speed * AP / 14)) + flat_dmg_bonus) * crit_dmg_modifier * total_phys_modifier
    // [2160] = (100 + (2.8 * 1000 / 14) + 600) * 2.33 * 1.03
    then_damage_dealt_is(2160);
}

void TestAimedShot::test_crit_dmg_5_of_5_mortal_shots_1_of_3_humanoid_slaying() {
    given_target_has_0_armor();
    given_target_is_humanoid();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_crit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();
    given_aimed_shot_is_enabled();
    given_5_of_5_mortal_shots();
    given_1_of_3_humanoid_slaying();

    when_aimed_shot_is_performed();
    then_next_event_is("PlayerAction", "1.500");
    then_next_event_is("CastComplete", "3.000", RUN_EVENT);

    // [Damage] = (base_dmg + (normalized_wpn_speed * AP / 14)) + flat_dmg_bonus) * crit_dmg_modifier * total_phys_modifier
    // [2100] = (100 + (2.8 * 1000 / 14) + 600) * 2.31 * 1.01
    then_damage_dealt_is(2100);
}

void TestAimedShot::test_crit_dmg_5_of_5_mortal_shots_2_of_3_humanoid_slaying() {
    given_target_has_0_armor();
    given_target_is_humanoid();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_crit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();
    given_aimed_shot_is_enabled();
    given_5_of_5_mortal_shots();
    given_2_of_3_humanoid_slaying();

    when_aimed_shot_is_performed();
    then_next_event_is("PlayerAction", "1.500");
    then_next_event_is("CastComplete", "3.000", RUN_EVENT);

    // [Damage] = (base_dmg + (normalized_wpn_speed * AP / 14)) + flat_dmg_bonus) * crit_dmg_modifier * total_phys_modifier
    // [2130] = (100 + (2.8 * 1000 / 14) + 600) * 2.32 * 1.02
    then_damage_dealt_is(2130);
}

void TestAimedShot::test_crit_dmg_5_of_5_mortal_shots_3_of_3_humanoid_slaying() {
    given_target_has_0_armor();
    given_target_is_humanoid();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_crit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();
    given_aimed_shot_is_enabled();
    given_5_of_5_mortal_shots();
    given_3_of_3_humanoid_slaying();

    when_aimed_shot_is_performed();
    then_next_event_is("PlayerAction", "1.500");
    then_next_event_is("CastComplete", "3.000", RUN_EVENT);

    // [Damage] = (base_dmg + (normalized_wpn_speed * AP / 14)) + flat_dmg_bonus) * crit_dmg_modifier * total_phys_modifier
    // [2160] = (100 + (2.8 * 1000 / 14) + 600) * 2.33 * 1.03
    then_damage_dealt_is(2160);
}

void TestAimedShot::test_aimed_shot_adds_player_action_event_on_completion() {
    given_aimed_shot_is_enabled();
    when_aimed_shot_is_performed();

    then_next_event_is("PlayerAction", "1.500");
    then_next_event_is("CastComplete", "3.000", RUN_EVENT);
    then_next_event_is("RangedHit", "3.000");
    then_next_event_is("PlayerAction", "3.100");
}

void TestAimedShot::test_aimed_shot_cast_in_progress_blocks_other_spells() {
    assert(multi_shot()->is_available());
    given_aimed_shot_is_enabled();
    when_aimed_shot_is_performed();
    given_engine_priority_pushed_forward(2.0);
    given_hunter_has_mana(310);

    assert(!multi_shot()->is_available());
}

void TestAimedShot::test_mana_cost_1_of_5_efficiency() {
    given_aimed_shot_is_enabled();
    given_1_of_5_efficiency();
    given_hunter_has_mana(304);
    assert(aimed_shot()->is_available());

    given_hunter_has_mana(303);
    assert(!aimed_shot()->is_available());

    given_hunter_has_mana(304);

    when_aimed_shot_is_performed();
    when_running_queued_events_until(3.01);

    then_hunter_has_mana(0);
}

void TestAimedShot::test_mana_cost_2_of_5_efficiency() {
    given_aimed_shot_is_enabled();
    given_2_of_5_efficiency();
    given_hunter_has_mana(298);
    assert(aimed_shot()->is_available());

    given_hunter_has_mana(297);
    assert(!aimed_shot()->is_available());

    given_hunter_has_mana(298);

    when_aimed_shot_is_performed();
    when_running_queued_events_until(3.01);

    then_hunter_has_mana(0);
}

void TestAimedShot::test_mana_cost_3_of_5_efficiency() {
    given_aimed_shot_is_enabled();
    given_3_of_5_efficiency();
    given_hunter_has_mana(291);
    assert(aimed_shot()->is_available());

    given_hunter_has_mana(290);
    assert(!aimed_shot()->is_available());

    given_hunter_has_mana(291);

    when_aimed_shot_is_performed();
    when_running_queued_events_until(3.01);

    then_hunter_has_mana(0);
}

void TestAimedShot::test_mana_cost_4_of_5_efficiency() {
    given_aimed_shot_is_enabled();
    given_4_of_5_efficiency();
    given_hunter_has_mana(285);
    assert(aimed_shot()->is_available());

    given_hunter_has_mana(284);
    assert(!aimed_shot()->is_available());

    given_hunter_has_mana(285);

    when_aimed_shot_is_performed();
    when_running_queued_events_until(3.01);

    then_hunter_has_mana(0);
}

void TestAimedShot::test_mana_cost_5_of_5_efficiency() {
    given_aimed_shot_is_enabled();
    given_5_of_5_efficiency();
    given_hunter_has_mana(279);
    assert(aimed_shot()->is_available());

    given_hunter_has_mana(278);
    assert(!aimed_shot()->is_available());

    given_hunter_has_mana(279);

    when_aimed_shot_is_performed();
    when_running_queued_events_until(3.01);

    then_hunter_has_mana(0);
}

void TestAimedShot::test_aimed_shot_cast_time_reduced_by_ranged_attack_speed_boosts() {
    given_aimed_shot_is_enabled();
    hunter->get_stats()->increase_ranged_attack_speed(200);
    hunter->get_stats()->increase_melee_attack_speed(200);

    when_aimed_shot_is_performed();

    // [cast_time] = base_cast_time / ranged_attack_speed_mod
    // 1.000 = 3.000 / 3.0
    then_next_event_is("CastComplete", "1.000");
}

void TestAimedShot::given_aimed_shot_is_enabled() {
    Talent* talent = Marksmanship(hunter).get_aimed_shot();

    assert(talent->increment_rank());

    delete talent;

    assert(aimed_shot()->is_enabled());
}

void TestAimedShot::when_aimed_shot_is_performed() {
    if (pchar->get_equipment()->get_ranged() == nullptr)
        given_a_ranged_weapon_with_100_min_max_dmg();

    aimed_shot()->perform();
}
