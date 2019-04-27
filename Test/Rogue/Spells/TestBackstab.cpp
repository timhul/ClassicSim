#include "TestBackstab.h"

#include "Backstab.h"
#include "Equipment.h"
#include "Queue.h"
#include "WarriorSpells.h"

TestBackstab::TestBackstab(EquipmentDb *equipment_db) :
    TestSpellRogue(equipment_db, "Backstab")
{}

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

Backstab* TestBackstab::backstab() {
    return dynamic_cast<RogueSpells*>(rogue->get_spells())->get_backstab();
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

    then_next_event_is("PlayerAction", QString::number(rogue->global_cooldown(), 'f', 3));
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
    // [497] = (100 + 1.7 * 1000 / 14) * 1.5 + 165
    then_damage_dealt_is(497);
}

void TestBackstab::test_crit_dmg() {
    given_target_has_0_armor();
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();

    when_backstab_is_performed();

    // [Damage] = ((base_dmg + normalized_wpn_speed * AP / 14) * 150% + flat_damage_bonus) * crit_dmg_modifier
    // [994] = ((100 + 1.7 * 1000 / 14) * 1.5 + 165) * 2.0
    then_damage_dealt_is(994);
}

void TestBackstab::test_hit_dmg_5_of_5_lethality() {
    given_5_of_5_lethality();
    test_hit_dmg();
}

void TestBackstab::test_crit_dmg_1_of_5_lethality() {
    given_1_of_5_lethality();
    given_target_has_0_armor();
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();

    when_backstab_is_performed();

    // [Damage] = ((base_dmg + normalized_wpn_speed * AP / 14) * 150% + flat_damage_bonus) * crit_dmg_modifier * lethality
    // [1054] = ((100 + 1.7 * 1000 / 14) * 1.5 + 165) * 2.0 * 1.06
    then_damage_dealt_is(1054);
}

void TestBackstab::test_crit_dmg_2_of_5_lethality() {
    given_2_of_5_lethality();
    given_target_has_0_armor();
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();

    when_backstab_is_performed();

    // [Damage] = ((base_dmg + normalized_wpn_speed * AP / 14) * 150% + flat_damage_bonus) * crit_dmg_modifier * lethality
    // [1114] = ((100 + 1.7 * 1000 / 14) * 1.5 + 165) * 2.0 * 1.12
    then_damage_dealt_is(1114);
}

void TestBackstab::test_crit_dmg_3_of_5_lethality() {
    given_3_of_5_lethality();
    given_target_has_0_armor();
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();

    when_backstab_is_performed();

    // [Damage] = ((base_dmg + normalized_wpn_speed * AP / 14) * 150% + flat_damage_bonus) * crit_dmg_modifier * lethality
    // [1173] = ((100 + 1.7 * 1000 / 14) * 1.5 + 165) * 2.0 * 1.18
    then_damage_dealt_is(1173);
}

void TestBackstab::test_crit_dmg_4_of_5_lethality() {
    given_4_of_5_lethality();
    given_target_has_0_armor();
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();

    when_backstab_is_performed();

    // [Damage] = ((base_dmg + normalized_wpn_speed * AP / 14) * 150% + flat_damage_bonus) * crit_dmg_modifier * lethality
    // [1233] = ((100 + 1.7 * 1000 / 14) * 1.5 + 165) * 2.0 * 1.24
    then_damage_dealt_is(1233);
}

void TestBackstab::test_crit_dmg_5_of_5_lethality() {
    given_5_of_5_lethality();
    given_target_has_0_armor();
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();

    when_backstab_is_performed();

    // [Damage] = ((base_dmg + normalized_wpn_speed * AP / 14) * 150% + flat_damage_bonus) * crit_dmg_modifier * lethality
    // [1293] = ((100 + 1.7 * 1000 / 14) * 1.5 + 165) * 2.0 * 1.30
    then_damage_dealt_is(1293);
}

void TestBackstab::test_hit_dmg_1_of_5_opportunity() {
    given_1_of_5_opportunity();
    given_target_has_0_armor();
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_hit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();

    when_backstab_is_performed();

    // [Damage] = ((base_dmg + normalized_wpn_speed * AP / 14) * 150% + flat_damage_bonus) * opportunity
    // [517] = ((100 + 1.7 * 1000 / 14) * 1.5 + 165) * 1.04
    then_damage_dealt_is(517);
}

void TestBackstab::test_hit_dmg_5_of_5_opportunity() {
    given_5_of_5_opportunity();
    given_target_has_0_armor();
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_hit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();

    when_backstab_is_performed();

    // [Damage] = ((base_dmg + normalized_wpn_speed * AP / 14) * 150% + flat_damage_bonus) * opportunity
    // [597] = ((100 + 1.7 * 1000 / 14) * 1.5 + 165) * 1.20
    then_damage_dealt_is(597);
}

void TestBackstab::test_crit_dmg_1_of_5_opportunity() {
    given_1_of_5_opportunity();
    given_target_has_0_armor();
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();

    when_backstab_is_performed();

    // [Damage] = ((base_dmg + normalized_wpn_speed * AP / 14) * 150% + flat_damage_bonus) * crit_dmg_modifier * opportunity
    // [1034] = ((100 + 1.7 * 1000 / 14) * 1.5 + 165) * 2.0 * 1.04
    then_damage_dealt_is(1034);
}

void TestBackstab::test_crit_dmg_5_of_5_opportunity() {
    given_5_of_5_opportunity();
    given_target_has_0_armor();
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();

    when_backstab_is_performed();

    // [Damage] = ((base_dmg + normalized_wpn_speed * AP / 14) * 150% + flat_damage_bonus) * crit_dmg_modifier * opportunity
    // [1193] = ((100 + 1.7 * 1000 / 14) * 1.5 + 165) * 2.0 * 1.20
    then_damage_dealt_is(1193);
}

void TestBackstab::test_hit_dmg_both_5_of_5_lethality_and_opportunity() {
    given_5_of_5_lethality();
    test_hit_dmg_5_of_5_opportunity();
}

void TestBackstab::test_crit_dmg_both_5_of_5_lethality_and_opportunity() {
    given_5_of_5_lethality();
    given_5_of_5_opportunity();
    given_target_has_0_armor();
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();

    when_backstab_is_performed();

    // [Damage] = ((base_dmg + normalized_wpn_speed * AP / 14) * 150% + flat_damage_bonus) * crit_dmg_modifier * opportunity * lethality
    // [1551] = ((100 + 1.7 * 1000 / 14) * 1.5 + 165) * 2.0 * 1.20 * 1.30
    then_damage_dealt_is(1551);
}

void TestBackstab::when_backstab_is_performed() {
    if (pchar->get_equipment()->get_mainhand() == nullptr)
        given_a_mainhand_dagger_with_100_min_max_dmg();

    backstab()->perform();
}
