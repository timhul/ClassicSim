#include "TestBackstab.h"

#include <cassert>

#include "Backstab.h"
#include "Equipment.h"
#include "Event.h"
#include "SpellRankGroup.h"

TestBackstab::TestBackstab(EquipmentDb* equipment_db) : TestSpellRogue(equipment_db, "Backstab") {}

void TestBackstab::test_all() {
    run_mandatory_tests();

    set_up();
    test_combo_points();
    tear_down();

    set_up();
    test_stealth();
    tear_down();

    set_up();
    test_hit_dmg();
    tear_down();

    set_up();
    test_crit_dmg();
    tear_down();

    set_up();
    test_hit_dmg_5_of_5_lethality();
    tear_down();

    set_up();
    test_crit_dmg_1_of_5_lethality();
    tear_down();

    set_up();
    test_crit_dmg_2_of_5_lethality();
    tear_down();

    set_up();
    test_crit_dmg_3_of_5_lethality();
    tear_down();

    set_up();
    test_crit_dmg_4_of_5_lethality();
    tear_down();

    set_up();
    test_crit_dmg_5_of_5_lethality();
    tear_down();

    set_up();
    test_hit_dmg_1_of_5_opportunity();
    tear_down();

    set_up();
    test_hit_dmg_5_of_5_opportunity();
    tear_down();

    set_up();
    test_crit_dmg_1_of_5_opportunity();
    tear_down();

    set_up();
    test_crit_dmg_5_of_5_opportunity();
    tear_down();

    set_up();
    test_hit_dmg_both_5_of_5_lethality_and_opportunity();
    tear_down();

    set_up();
    test_crit_dmg_both_5_of_5_lethality_and_opportunity();
    tear_down();
}

Backstab* TestBackstab::backstab() const {
    return static_cast<Backstab*>(rogue->get_spells()->get_spell_rank_group_by_name("Backstab")->get_max_available_spell_rank());
}

void TestBackstab::test_name_correct() {
    assert(backstab()->get_name() == "Backstab");
}

void TestBackstab::test_spell_cooldown() {
    assert(QString::number(backstab()->get_base_cooldown(), 'f', 3) == "0.000");
}

void TestBackstab::test_whether_spell_causes_global_cooldown() {
    given_a_guaranteed_melee_ability_hit();
    when_backstab_is_performed();

    then_next_event_is(EventType::PlayerAction, QString::number(rogue->global_cooldown(), 'f', 3));
}

void TestBackstab::test_how_spell_observes_global_cooldown() {
    given_dagger_equipped_in_mainhand(rogue);

    given_rogue_has_energy(100);
    assert(backstab()->get_spell_status() == SpellStatus::Available);

    given_rogue_is_on_gcd();

    given_rogue_has_energy(100);
    assert(backstab()->get_spell_status() == SpellStatus::OnGCD);
}

void TestBackstab::test_is_ready_conditions() {
    given_no_offhand(rogue);
    given_1h_mace_equipped_in_mainhand(rogue);
    assert(backstab()->get_spell_status() == SpellStatus::IncorrectWeaponType);

    given_1h_mace_equipped_in_offhand(rogue);
    assert(backstab()->get_spell_status() == SpellStatus::IncorrectWeaponType);

    given_1h_sword_equipped_in_mainhand(rogue);
    assert(backstab()->get_spell_status() == SpellStatus::IncorrectWeaponType);

    given_1h_sword_equipped_in_offhand(rogue);
    assert(backstab()->get_spell_status() == SpellStatus::IncorrectWeaponType);

    given_fist_weapon_equipped_in_mainhand(rogue);
    assert(backstab()->get_spell_status() == SpellStatus::IncorrectWeaponType);

    given_fist_weapon_equipped_in_offhand(rogue);
    assert(backstab()->get_spell_status() == SpellStatus::IncorrectWeaponType);

    given_dagger_equipped_in_mainhand(rogue);
    assert(backstab()->get_spell_status() == SpellStatus::Available);

    given_dagger_equipped_in_mainhand(rogue);
    given_no_offhand();
    assert(backstab()->get_spell_status() == SpellStatus::Available);

    given_1h_mace_equipped_in_offhand(rogue);
    assert(backstab()->get_spell_status() == SpellStatus::Available);

    given_1h_sword_equipped_in_offhand(rogue);
    assert(backstab()->get_spell_status() == SpellStatus::Available);

    given_fist_weapon_equipped_in_offhand(rogue);
    assert(backstab()->get_spell_status() == SpellStatus::Available);

    given_dagger_equipped_in_offhand(rogue);
    assert(backstab()->get_spell_status() == SpellStatus::Available);
}

void TestBackstab::test_resource_cost() {
    given_dagger_equipped_in_mainhand(rogue);
    given_a_guaranteed_melee_ability_hit();

    given_rogue_has_energy(60);
    when_backstab_is_performed();
    then_rogue_has_energy(0);

    given_engine_priority_at(1.01);

    given_rogue_has_energy(70);
    when_backstab_is_performed();
    then_rogue_has_energy(10);
}

void TestBackstab::test_combo_points() {
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_hit();
    then_rogue_has_combo_points(0);

    when_backstab_is_performed();

    then_rogue_has_combo_points(1);
}

void TestBackstab::test_stealth() {
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_rogue_not_in_stealth();
    assert(backstab()->get_spell_status() == SpellStatus::Available);
    given_rogue_in_stealth();
    assert(backstab()->get_spell_status() == SpellStatus::Available);

    when_backstab_is_performed();

    assert(!rogue->is_stealthed());
}

void TestBackstab::test_hit_dmg() {
    given_target_has_0_armor();
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_hit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();

    when_backstab_is_performed();

    // [Damage] = (base_dmg + normalized_wpn_speed * AP / 14) * 150% + flat_damage_bonus
    // [557] = (100 + 1.7 * 1000 / 14) * 1.5 + 225
    then_damage_dealt_is(557);
}

void TestBackstab::test_crit_dmg() {
    given_target_has_0_armor();
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();

    when_backstab_is_performed();

    // [Damage] = ((base_dmg + normalized_wpn_speed * AP / 14) * 150% + flat_damage_bonus) * crit_dmg_modifier
    // [1114] = ((100 + 1.7 * 1000 / 14) * 1.5 + 225) * 2.0
    then_damage_dealt_is(1114);
}

void TestBackstab::test_hit_dmg_5_of_5_lethality() {
    given_lethality_talent_rank(5);
    test_hit_dmg();
}

void TestBackstab::test_crit_dmg_1_of_5_lethality() {
    given_lethality_talent_rank(1);
    given_target_has_0_armor();
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();

    when_backstab_is_performed();

    // [Damage] = ((base_dmg + normalized_wpn_speed * AP / 14) * 150% + flat_damage_bonus) * (base_crit_dmg_modifier + lethality)
    // [1148] = ((100 + 1.7 * 1000 / 14) * 1.5 + 225) * (2.0 + 0.06)
    then_damage_dealt_is(1148);
}

void TestBackstab::test_crit_dmg_2_of_5_lethality() {
    given_lethality_talent_rank(2);
    given_target_has_0_armor();
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();

    when_backstab_is_performed();

    // [Damage] = ((base_dmg + normalized_wpn_speed * AP / 14) * 150% + flat_damage_bonus) * (base_crit_dmg_modifier + lethality)
    // [1181] = ((100 + 1.7 * 1000 / 14) * 1.5 + 225) * (2.0 + 0.12)
    then_damage_dealt_is(1181);
}

void TestBackstab::test_crit_dmg_3_of_5_lethality() {
    given_lethality_talent_rank(3);
    given_target_has_0_armor();
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();

    when_backstab_is_performed();

    // [Damage] = ((base_dmg + normalized_wpn_speed * AP / 14) * 150% + flat_damage_bonus) * (base_crit_dmg_modifier + lethality)
    // [1215] = ((100 + 1.7 * 1000 / 14) * 1.5 + 225) * (2.0 + 0.18)
    then_damage_dealt_is(1215);
}

void TestBackstab::test_crit_dmg_4_of_5_lethality() {
    given_lethality_talent_rank(4);
    given_target_has_0_armor();
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();

    when_backstab_is_performed();

    // [Damage] = ((base_dmg + normalized_wpn_speed * AP / 14) * 150% + flat_damage_bonus) * (base_crit_dmg_modifier + lethality)
    // [1248] = ((100 + 1.7 * 1000 / 14) * 1.5 + 225) * (2.0 + 0.24)
    then_damage_dealt_is(1248);
}

void TestBackstab::test_crit_dmg_5_of_5_lethality() {
    given_lethality_talent_rank(5);
    given_target_has_0_armor();
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();

    when_backstab_is_performed();

    // [Damage] = ((base_dmg + normalized_wpn_speed * AP / 14) * 150% + flat_damage_bonus) * (base_crit_dmg_modifier + lethality)
    // [1281] = ((100 + 1.7 * 1000 / 14) * 1.5 + 225) * (2.0 + 0.30)
    then_damage_dealt_is(1281);
}

void TestBackstab::test_hit_dmg_1_of_5_opportunity() {
    given_subtlety_talent_rank("Opportunity", 1);
    given_target_has_0_armor();
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_hit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();

    when_backstab_is_performed();

    // [Damage] = ((base_dmg + normalized_wpn_speed * AP / 14) * 150% + flat_damage_bonus) * opportunity
    // [579] = ((100 + 1.7 * 1000 / 14) * 1.5 + 225) * 1.04
    then_damage_dealt_is(579);
}

void TestBackstab::test_hit_dmg_5_of_5_opportunity() {
    given_subtlety_talent_rank("Opportunity", 5);
    given_target_has_0_armor();
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_hit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();

    when_backstab_is_performed();

    // [Damage] = ((base_dmg + normalized_wpn_speed * AP / 14) * 150% + flat_damage_bonus) * opportunity
    // [669] = ((100 + 1.7 * 1000 / 14) * 1.5 + 225) * 1.20
    then_damage_dealt_is(669);
}

void TestBackstab::test_crit_dmg_1_of_5_opportunity() {
    given_subtlety_talent_rank("Opportunity", 1);
    given_target_has_0_armor();
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();

    when_backstab_is_performed();

    // [Damage] = ((base_dmg + normalized_wpn_speed * AP / 14) * 150% + flat_damage_bonus) * crit_dmg_modifier * opportunity
    // [1159] = ((100 + 1.7 * 1000 / 14) * 1.5 + 225) * 2.0 * 1.04
    then_damage_dealt_is(1159);
}

void TestBackstab::test_crit_dmg_5_of_5_opportunity() {
    given_subtlety_talent_rank("Opportunity", 5);
    given_target_has_0_armor();
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();

    when_backstab_is_performed();

    // [Damage] = ((base_dmg + normalized_wpn_speed * AP / 14) * 150% + flat_damage_bonus) * crit_dmg_modifier * opportunity
    // [1337] = ((100 + 1.7 * 1000 / 14) * 1.5 + 225) * 2.0 * 1.20
    then_damage_dealt_is(1337);
}

void TestBackstab::test_hit_dmg_both_5_of_5_lethality_and_opportunity() {
    given_lethality_talent_rank(5);
    test_hit_dmg_5_of_5_opportunity();
}

void TestBackstab::test_crit_dmg_both_5_of_5_lethality_and_opportunity() {
    given_lethality_talent_rank(5);
    given_subtlety_talent_rank("Opportunity", 5);
    given_target_has_0_armor();
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();

    when_backstab_is_performed();

    // [Damage] = ((base_dmg + normalized_wpn_speed * AP / 14) * 150% + flat_damage_bonus) * (base_crit_dmg_modifier + lethality) * opportunity
    // [1538] = ((100 + 1.7 * 1000 / 14) * 1.5 + 225) * (2.0 + 0.30) * 1.20
    then_damage_dealt_is(1538);
}

void TestBackstab::when_backstab_is_performed() {
    if (pchar->get_equipment()->get_mainhand() == nullptr)
        given_a_mainhand_dagger_with_100_min_max_dmg();

    backstab()->perform();
}
