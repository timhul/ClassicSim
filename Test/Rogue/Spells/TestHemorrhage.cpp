#include "TestHemorrhage.h"

#include "Equipment.h"
#include "Hemorrhage.h"
#include "Queue.h"
#include "RogueSpells.h"
#include "Subtlety.h"
#include "Talent.h"

TestHemorrhage::TestHemorrhage(EquipmentDb *equipment_db) :
    TestSpellRogue(equipment_db, "Hemorrhage")
{}

void TestHemorrhage::test_all() {
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
}

Hemorrhage *TestHemorrhage::hemo() {
    return dynamic_cast<RogueSpells*>(rogue->get_spells())->get_hemorrhage();
}

void TestHemorrhage::test_name_correct() {
    assert(hemo()->get_name() == "Hemorrhage");
}

void TestHemorrhage::test_spell_cooldown() {
    assert(QString::number(hemo()->get_base_cooldown(), 'f', 3) == "0.000");
}

void TestHemorrhage::test_incurs_global_cooldown() {
    given_hemorrhage_is_enabled();
    when_hemorrhage_is_performed();

    then_next_event_is("PlayerAction", QString::number(rogue->global_cooldown(), 'f', 3));
}

void TestHemorrhage::test_obeys_global_cooldown() {
    given_hemorrhage_is_enabled();
    given_rogue_has_energy(100);
    assert(hemo()->is_available());

    given_rogue_is_on_gcd();

    given_rogue_has_energy(100);
    assert(!hemo()->is_available());
}

void TestHemorrhage::test_is_ready_conditions() {
    given_rogue_has_energy(100);
    assert(!hemo()->is_available());

    given_hemorrhage_is_enabled();

    assert(hemo()->is_available());
}

void TestHemorrhage::test_resource_cost() {
    given_hemorrhage_is_enabled();
    given_1h_sword_equipped_in_mainhand(pchar);
    given_a_guaranteed_melee_ability_hit();

    given_rogue_has_energy(35);
    when_hemorrhage_is_performed();
    then_rogue_has_energy(0);

    given_engine_priority_at(1.01);

    given_rogue_has_energy(45);
    when_hemorrhage_is_performed();
    then_rogue_has_energy(10);
}

void TestHemorrhage::test_combo_points() {
    given_hemorrhage_is_enabled();
    given_1h_sword_equipped_in_mainhand(pchar);
    given_a_guaranteed_melee_ability_hit();
    then_rogue_has_combo_points(0);

    when_hemorrhage_is_performed();

    then_rogue_has_combo_points(1);
}

void TestHemorrhage::test_stealth() {
    given_hemorrhage_is_enabled();
    given_1h_sword_equipped_in_mainhand(pchar);
    given_rogue_not_in_stealth();
    assert(hemo()->is_available());
    given_rogue_in_stealth();
    assert(hemo()->is_available());

    when_hemorrhage_is_performed();

    assert(!rogue->is_stealthed());
}

void TestHemorrhage::test_hit_dmg() {
    given_hemorrhage_is_enabled();
    given_target_has_0_armor();
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_hit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();

    when_hemorrhage_is_performed();

    // [Damage] = base_dmg + non_normalized_wpn_speed * AP / 14
    // [286] = 100 + 2.6 * 1000 / 14
    then_damage_dealt_is(286);
}

void TestHemorrhage::test_crit_dmg() {
    given_hemorrhage_is_enabled();
    given_target_has_0_armor();
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();

    when_hemorrhage_is_performed();

    // [Damage] = (base_dmg + non_normalized_wpn_speed * AP / 14) * crit_dmg_modifier
    // [571] = (100 + 2.6 * 1000 / 14) * 2.0
    then_damage_dealt_is(571);
}

void TestHemorrhage::test_hit_dmg_5_of_5_lethality() {
    given_5_of_5_lethality();
    test_hit_dmg();
}

void TestHemorrhage::test_crit_dmg_1_of_5_lethality() {
    given_hemorrhage_is_enabled();
    given_1_of_5_lethality();
    given_target_has_0_armor();
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();

    when_hemorrhage_is_performed();

    // [Damage] = (base_dmg + non_normalized_wpn_speed * AP / 14) * crit_dmg_modifier * lethality
    // [606] = (100 + 2.6 * 1000 / 14) * 2.0 * 1.06
    then_damage_dealt_is(606);
}

void TestHemorrhage::test_crit_dmg_2_of_5_lethality() {
    given_hemorrhage_is_enabled();
    given_2_of_5_lethality();
    given_target_has_0_armor();
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();

    when_hemorrhage_is_performed();

    // [Damage] = ((base_dmg + non_normalized_wpn_speed * AP / 14)) * crit_dmg_modifier * lethality
    // [640] = (100 + 2.6 * 1000 / 14) * 2.0 * 1.12
    then_damage_dealt_is(640);
}

void TestHemorrhage::test_crit_dmg_3_of_5_lethality() {
    given_hemorrhage_is_enabled();
    given_3_of_5_lethality();
    given_target_has_0_armor();
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();

    when_hemorrhage_is_performed();

    // [Damage] = ((base_dmg + non_normalized_wpn_speed * AP / 14)) * crit_dmg_modifier * lethality
    // [674] = (100 + 2.6 * 1000 / 14) * 2.0 * 1.18
    then_damage_dealt_is(674);
}

void TestHemorrhage::test_crit_dmg_4_of_5_lethality() {
    given_hemorrhage_is_enabled();
    given_4_of_5_lethality();
    given_target_has_0_armor();
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();

    when_hemorrhage_is_performed();

    // [Damage] = ((base_dmg + non_normalized_wpn_speed * AP / 14)) * crit_dmg_modifier * lethality
    // [709] = (100 + 2.6 * 1000 / 14) * 2.0 * 1.24
    then_damage_dealt_is(709);
}

void TestHemorrhage::test_crit_dmg_5_of_5_lethality() {
    given_hemorrhage_is_enabled();
    given_5_of_5_lethality();
    given_target_has_0_armor();
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();

    when_hemorrhage_is_performed();

    // [Damage] = ((base_dmg + non_normalized_wpn_speed * AP / 14)) * crit_dmg_modifier * lethality
    // [743] = (100 + 2.6 * 1000 / 14) * 2.0 * 1.30
    then_damage_dealt_is(743);
}

void TestHemorrhage::when_hemorrhage_is_performed() {
    if (pchar->get_equipment()->get_mainhand() == nullptr)
        given_1h_sword_equipped_in_mainhand(pchar);

    hemo()->perform();
}

void TestHemorrhage::given_hemorrhage_is_enabled() {
    Talent* talent = Subtlety(rogue).get_hemorrhage();

    assert(talent->increment_rank());

    delete talent;
}
