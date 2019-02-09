#include "TestEviscerate.h"

#include "Assassination.h"
#include "Combat.h"
#include "Equipment.h"
#include "Eviscerate.h"
#include "Item.h"
#include "Queue.h"
#include "Talent.h"
#include "WarriorSpells.h"

TestEviscerate::TestEviscerate(EquipmentDb *equipment_db) :
    TestSpellRogue(equipment_db, "Eviscerate")
{}

void TestEviscerate::test_all() {
    run_mandatory_tests();

    set_up();
    test_combo_points();
    tear_down();

    set_up();
    test_stealth();
    tear_down();

    set_up();
    test_hit_dmg_1_combo_points();
    tear_down();

    set_up();
    test_hit_dmg_2_combo_points();
    tear_down();

    set_up();
    test_hit_dmg_3_combo_points();
    tear_down();

    set_up();
    test_hit_dmg_4_combo_points();
    tear_down();

    set_up();
    test_hit_dmg_5_combo_points();
    tear_down();

    set_up();
    test_crit_dmg_1_combo_points();
    tear_down();

    set_up();
    test_crit_dmg_2_combo_points();
    tear_down();

    set_up();
    test_crit_dmg_3_combo_points();
    tear_down();

    set_up();
    test_crit_dmg_4_combo_points();
    tear_down();

    set_up();
    test_crit_dmg_5_combo_points();
    tear_down();

    set_up();
    test_hit_dmg_5_combo_points_with_1_of_3_imp_evisc();
    tear_down();

    set_up();
    test_hit_dmg_5_combo_points_with_2_of_3_imp_evisc();
    tear_down();

    set_up();
    test_hit_dmg_5_combo_points_with_3_of_3_imp_evisc();
    tear_down();

    set_up();
    test_crit_dmg_5_combo_points_with_1_of_3_imp_evisc();
    tear_down();

    set_up();
    test_crit_dmg_5_combo_points_with_2_of_3_imp_evisc();
    tear_down();

    set_up();
    test_crit_dmg_5_combo_points_with_3_of_3_imp_evisc();
    tear_down();

    set_up();
    test_hit_dmg_5_combo_points_with_1_of_3_aggression();
    tear_down();

    set_up();
    test_hit_dmg_5_combo_points_with_2_of_3_aggression();
    tear_down();

    set_up();
    test_hit_dmg_5_combo_points_with_3_of_3_aggression();
    tear_down();

    set_up();
    test_crit_dmg_5_combo_points_with_1_of_3_aggression();
    tear_down();

    set_up();
    test_crit_dmg_5_combo_points_with_2_of_3_aggression();
    tear_down();

    set_up();
    test_crit_dmg_5_combo_points_with_3_of_3_aggression();
    tear_down();

    set_up();
    test_hit_dmg_5_combo_points_with_3_of_3_imp_evisc_and_3_of_3_aggression_and_5_pc_deathdealer();
    tear_down();

    set_up();
    test_crit_dmg_5_combo_points_with_3_of_3_imp_evisc_and_3_of_3_aggression_and_5_pc_deathdealer();
    tear_down();
}

Eviscerate* TestEviscerate::eviscerate() {
    return dynamic_cast<RogueSpells*>(rogue->get_spells())->get_eviscerate();
}

void TestEviscerate::test_name_correct() {
    assert(eviscerate()->get_name() == "Eviscerate");
}

void TestEviscerate::test_spell_cooldown() {
    assert(QString::number(eviscerate()->get_base_cooldown(), 'f', 3) == "0.000");
}

void TestEviscerate::test_incurs_global_cooldown() {
    when_eviscerate_is_performed();

    then_next_event_is("CooldownReady", QString::number(rogue->global_cooldown(), 'f', 3));
}

void TestEviscerate::test_obeys_global_cooldown() {
    given_rogue_has_energy(100);
    given_rogue_has_combo_points(1);
    assert(eviscerate()->is_available());

    given_rogue_is_on_gcd();

    given_rogue_has_energy(100);
    assert(!eviscerate()->is_available());
}

void TestEviscerate::test_is_ready_conditions() {
    given_rogue_has_combo_points(0);
    assert(!eviscerate()->is_available());

    given_rogue_has_combo_points(1);
    assert(eviscerate()->is_available());

    given_rogue_has_combo_points(2);
    assert(eviscerate()->is_available());

    given_rogue_has_combo_points(3);
    assert(eviscerate()->is_available());

    given_rogue_has_combo_points(4);
    assert(eviscerate()->is_available());

    given_rogue_has_combo_points(5);
    assert(eviscerate()->is_available());
}

void TestEviscerate::test_resource_cost() {
    given_dagger_equipped_in_mainhand(rogue);
    given_a_guaranteed_melee_ability_hit();

    given_rogue_has_energy(35);
    when_eviscerate_is_performed();
    then_rogue_has_energy(0);

    given_engine_priority_at(1.01);

    given_rogue_has_energy(40);
    when_eviscerate_is_performed();
    then_rogue_has_energy(5);
}

void TestEviscerate::test_combo_points() {
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_hit();

    given_rogue_has_combo_points(1);
    when_eviscerate_is_performed();
    then_rogue_has_combo_points(0);

    given_engine_priority_pushed_forward(1.01);
    given_rogue_has_energy(100);
    given_rogue_has_combo_points(2);
    when_eviscerate_is_performed();
    then_rogue_has_combo_points(0);

    given_engine_priority_pushed_forward(1.01);
    given_rogue_has_energy(100);
    given_rogue_has_combo_points(3);
    when_eviscerate_is_performed();
    then_rogue_has_combo_points(0);

    given_engine_priority_pushed_forward(1.01);
    given_rogue_has_energy(100);
    given_rogue_has_combo_points(4);
    when_eviscerate_is_performed();
    then_rogue_has_combo_points(0);

    given_engine_priority_pushed_forward(1.01);
    given_rogue_has_energy(100);
    given_rogue_has_combo_points(5);
    when_eviscerate_is_performed();
    then_rogue_has_combo_points(0);
}

void TestEviscerate::test_stealth() {
    given_rogue_has_combo_points(1);

    given_rogue_not_in_stealth();
    assert(eviscerate()->is_available());

    given_rogue_in_stealth();
    assert(eviscerate()->is_available());

    when_eviscerate_is_performed();

    assert(!rogue->is_stealthed());
}

void TestEviscerate::test_hit_dmg_1_combo_points() {
    given_target_has_0_armor();
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_hit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_rogue_has_combo_points(1);

    when_eviscerate_is_performed();

    // [Damage] = evisc_range + melee_ap * combo_points * 0.03
    // [254-362] = [224-332] + 1000 * 1 * 0.03
    then_damage_dealt_is_in_range(254, 362);
}

void TestEviscerate::test_hit_dmg_2_combo_points() {
    given_target_has_0_armor();
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_hit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_rogue_has_combo_points(2);

    when_eviscerate_is_performed();

    // [Damage] = evisc_range + melee_ap * combo_points * 0.03
    // [454-562] = [394-502] + 1000 * 2 * 0.03
    then_damage_dealt_is_in_range(454, 562);
}

void TestEviscerate::test_hit_dmg_3_combo_points() {
    given_target_has_0_armor();
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_hit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_rogue_has_combo_points(3);

    when_eviscerate_is_performed();

    // [Damage] = evisc_range + melee_ap * combo_points * 0.03
    // [654-762] = [564-672] + 1000 * 3 * 0.03
    then_damage_dealt_is_in_range(654, 762);
}

void TestEviscerate::test_hit_dmg_4_combo_points() {
    given_target_has_0_armor();
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_hit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_rogue_has_combo_points(4);

    when_eviscerate_is_performed();

    // [Damage] = evisc_range + melee_ap * combo_points * 0.03
    // [854-962] = [734-842] + 1000 * 4 * 0.03
    then_damage_dealt_is_in_range(854, 962);
}

void TestEviscerate::test_hit_dmg_5_combo_points() {
    given_target_has_0_armor();
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_hit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_rogue_has_combo_points(5);

    when_eviscerate_is_performed();

    // [Damage] = evisc_range + melee_ap * combo_points * 0.03
    // [1054-1162] = [904-1012] + 1000 * 5 * 0.03
    then_damage_dealt_is_in_range(1054, 1162);
}

void TestEviscerate::test_crit_dmg_1_combo_points() {
    given_target_has_0_armor();
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_rogue_has_combo_points(1);

    when_eviscerate_is_performed();

    // [Damage] = (evisc_range + melee_ap * combo_points * 0.03) * crit_dmg_modifier
    // [508-724] = ([224-332] + 1000 * 1 * 0.03) * 2.0
    then_damage_dealt_is_in_range(508, 724);
}

void TestEviscerate::test_crit_dmg_2_combo_points() {
    given_target_has_0_armor();
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_rogue_has_combo_points(2);

    when_eviscerate_is_performed();

    // [Damage] = (evisc_range + melee_ap * combo_points * 0.03) * crit_dmg_modifier
    // [908-1124] = ([394-502] + 1000 * 2 * 0.03) * 2.0
    then_damage_dealt_is_in_range(908, 1124);
}

void TestEviscerate::test_crit_dmg_3_combo_points() {
    given_target_has_0_armor();
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_rogue_has_combo_points(3);

    when_eviscerate_is_performed();

    // [Damage] = (evisc_range + melee_ap * combo_points * 0.03) * crit_dmg_modifier
    // [1308-1524] = ([564-672] + 1000 * 3 * 0.03) * 2.0
    then_damage_dealt_is_in_range(1308, 1524);
}

void TestEviscerate::test_crit_dmg_4_combo_points() {
    given_target_has_0_armor();
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_rogue_has_combo_points(4);

    when_eviscerate_is_performed();

    // [Damage] = (evisc_range + melee_ap * combo_points * 0.03) * crit_dmg_modifier
    // [1708-1924] = ([734-842] + 1000 * 4 * 0.03) * 2.0
    then_damage_dealt_is_in_range(1708, 1924);
}

void TestEviscerate::test_crit_dmg_5_combo_points() {
    given_target_has_0_armor();
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_rogue_has_combo_points(5);

    when_eviscerate_is_performed();

    // [Damage] = (evisc_range + melee_ap * combo_points * 0.03) * crit_dmg_modifier
    // [2108-2324] = ([904-1012] + 1000 * 5 * 0.03) * 2.0
    then_damage_dealt_is_in_range(2108, 2324);
}

void TestEviscerate::test_hit_dmg_5_combo_points_with_1_of_3_imp_evisc() {
    given_target_has_0_armor();
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_hit();
    given_1000_melee_ap();
    given_1_of_3_imp_eviscerate();
    given_no_previous_damage_dealt();
    given_rogue_has_combo_points(5);

    when_eviscerate_is_performed();

    // [Damage] = (evisc_range + melee_ap * combo_points * 0.03) * imp_evisc
    // [1107-1220] = ([904-1012] + 1000 * 5 * 0.03) * 1.05
    then_damage_dealt_is_in_range(1107, 1220);
}

void TestEviscerate::test_crit_dmg_5_combo_points_with_1_of_3_imp_evisc() {
    given_target_has_0_armor();
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_1_of_3_imp_eviscerate();
    given_no_previous_damage_dealt();
    given_rogue_has_combo_points(5);

    when_eviscerate_is_performed();

    // [Damage] = (evisc_range + melee_ap * combo_points * 0.03) * imp_evisc * crit_dmg_modifier
    // [2213-2440] = ([904-1012] + 1000 * 5 * 0.03) * 1.05 * 2.0
    then_damage_dealt_is_in_range(2213, 2440);
}

void TestEviscerate::test_hit_dmg_5_combo_points_with_2_of_3_imp_evisc() {
    given_target_has_0_armor();
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_hit();
    given_1000_melee_ap();
    given_2_of_3_imp_eviscerate();
    given_no_previous_damage_dealt();
    given_rogue_has_combo_points(5);

    when_eviscerate_is_performed();

    // [Damage] = (evisc_range + melee_ap * combo_points * 0.03) * imp_evisc
    // [1159-1278] = ([904-1012] + 1000 * 5 * 0.03) * 1.10
    then_damage_dealt_is_in_range(1159, 1278);
}

void TestEviscerate::test_crit_dmg_5_combo_points_with_2_of_3_imp_evisc() {
    given_target_has_0_armor();
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_2_of_3_imp_eviscerate();
    given_no_previous_damage_dealt();
    given_rogue_has_combo_points(5);

    when_eviscerate_is_performed();

    // [Damage] = (evisc_range + melee_ap * combo_points * 0.03) * imp_evisc * crit_dmg_modifier
    // [2319-2556] = ([904-1012] + 1000 * 5 * 0.03) * 1.10 * 2.0
    then_damage_dealt_is_in_range(2139, 2556);
}

void TestEviscerate::test_hit_dmg_5_combo_points_with_3_of_3_imp_evisc() {
    given_target_has_0_armor();
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_hit();
    given_1000_melee_ap();
    given_3_of_3_imp_eviscerate();
    given_no_previous_damage_dealt();
    given_rogue_has_combo_points(5);

    when_eviscerate_is_performed();

    // [Damage] = (evisc_range + melee_ap * combo_points * 0.03) * imp_evisc
    // [1212-1336] = ([904-1012] + 1000 * 5 * 0.03) * 1.15
    then_damage_dealt_is_in_range(1212, 1336);
}

void TestEviscerate::test_crit_dmg_5_combo_points_with_3_of_3_imp_evisc() {
    given_target_has_0_armor();
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_3_of_3_imp_eviscerate();
    given_no_previous_damage_dealt();
    given_rogue_has_combo_points(5);

    when_eviscerate_is_performed();

    // [Damage] = (evisc_range + melee_ap * combo_points * 0.03) * imp_evisc * crit_dmg_modifier
    // [2424-2673] = ([904-1012] + 1000 * 5 * 0.03) * 1.15 * 2.0
    then_damage_dealt_is_in_range(2424, 2673);
}

void TestEviscerate::test_hit_dmg_5_combo_points_with_1_of_3_aggression() {
    given_target_has_0_armor();
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_hit();
    given_1000_melee_ap();
    given_1_of_3_aggression();
    given_no_previous_damage_dealt();
    given_rogue_has_combo_points(5);

    when_eviscerate_is_performed();

    // [Damage] = (evisc_range + melee_ap * combo_points * 0.03) * aggression
    // [1075-1185] = ([904-1012] + 1000 * 5 * 0.03) * 1.02
    then_damage_dealt_is_in_range(1075, 1185);
}

void TestEviscerate::test_crit_dmg_5_combo_points_with_1_of_3_aggression() {
    given_target_has_0_armor();
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_1_of_3_aggression();
    given_no_previous_damage_dealt();
    given_rogue_has_combo_points(5);

    when_eviscerate_is_performed();

    // [Damage] = (evisc_range + melee_ap * combo_points * 0.03) * aggression * crit_dmg_modifier
    // [2150-2370] = ([904-1012] + 1000 * 5 * 0.03) * 1.02 * 2.0
    then_damage_dealt_is_in_range(2150, 2370);
}

void TestEviscerate::test_hit_dmg_5_combo_points_with_2_of_3_aggression() {
    given_target_has_0_armor();
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_hit();
    given_1000_melee_ap();
    given_2_of_3_aggression();
    given_no_previous_damage_dealt();
    given_rogue_has_combo_points(5);

    when_eviscerate_is_performed();

    // [Damage] = (evisc_range + melee_ap * combo_points * 0.03) * aggression
    // [1096-1208] = ([904-1012] + 1000 * 5 * 0.03) * 1.04
    then_damage_dealt_is_in_range(1096, 1208);
}

void TestEviscerate::test_crit_dmg_5_combo_points_with_2_of_3_aggression() {
    given_target_has_0_armor();
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_2_of_3_aggression();
    given_no_previous_damage_dealt();
    given_rogue_has_combo_points(5);

    when_eviscerate_is_performed();

    // [Damage] = (evisc_range + melee_ap * combo_points * 0.03) * aggression * crit_dmg_modifier
    // [2192-2417] = ([904-1012] + 1000 * 5 * 0.03) * 1.04 * 2.0
    then_damage_dealt_is_in_range(2192, 2417);
}

void TestEviscerate::test_hit_dmg_5_combo_points_with_3_of_3_aggression() {
    given_target_has_0_armor();
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_hit();
    given_1000_melee_ap();
    given_3_of_3_aggression();
    given_no_previous_damage_dealt();
    given_rogue_has_combo_points(5);

    when_eviscerate_is_performed();

    // [Damage] = (evisc_range + melee_ap * combo_points * 0.03) * aggression
    // [1117-1232] = ([904-1012] + 1000 * 5 * 0.03) * 1.06
    then_damage_dealt_is_in_range(1117, 1232);
}

void TestEviscerate::test_crit_dmg_5_combo_points_with_3_of_3_aggression() {
    given_target_has_0_armor();
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_3_of_3_aggression();
    given_no_previous_damage_dealt();
    given_rogue_has_combo_points(5);

    when_eviscerate_is_performed();

    // [Damage] = (evisc_range + melee_ap * combo_points * 0.03) * aggression * crit_dmg_modifier
    // [2234-2463] = ([904-1012] + 1000 * 5 * 0.03) * 1.06 * 2.0
    then_damage_dealt_is_in_range(2234, 2463);
}

void TestEviscerate::test_hit_dmg_5_combo_points_with_3_of_3_imp_evisc_and_3_of_3_aggression_and_5_pc_deathdealer() {
    given_target_has_0_armor();
    given_5_pc_deathdealer();
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_hit();
    given_1000_melee_ap();
    given_3_of_3_aggression();
    given_3_of_3_imp_eviscerate();
    given_no_previous_damage_dealt();
    given_rogue_has_combo_points(5);

    when_eviscerate_is_performed();

    // [Damage] = (evisc_range + melee_ap * combo_points * 0.03) * aggression * imp_evisc * deathdealer_5pc
    // [1478-1629] = ([904-1012] + 1000 * 5 * 0.03) * 1.06 * 1.15 * 1.15
    then_damage_dealt_is_in_range(1478, 1629);
}

void TestEviscerate::test_crit_dmg_5_combo_points_with_3_of_3_imp_evisc_and_3_of_3_aggression_and_5_pc_deathdealer() {
    given_target_has_0_armor();
    given_5_pc_deathdealer();
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_3_of_3_aggression();
    given_3_of_3_imp_eviscerate();
    given_no_previous_damage_dealt();
    given_rogue_has_combo_points(5);

    when_eviscerate_is_performed();

    // [Damage] = (evisc_range + melee_ap * combo_points * 0.03) * aggression * imp_evisc * deathdealer_5pc * crit_dmg_modifier
    // [2955-3257] = ([904-1012] + 1000 * 5 * 0.03) * 1.06 * 1.15 * 1.15 * 2.0
    then_damage_dealt_is_in_range(2955, 3257);
}

void TestEviscerate::given_1_of_3_imp_eviscerate() {
    Talent* talent = Assassination(rogue).get_improved_eviscerate();

    talent->increment_rank();

    delete talent;
}

void TestEviscerate::given_2_of_3_imp_eviscerate() {
    Talent* talent = Assassination(rogue).get_improved_eviscerate();

    talent->increment_rank();
    talent->increment_rank();

    delete talent;
}

void TestEviscerate::given_3_of_3_imp_eviscerate() {
    Talent* talent = Assassination(rogue).get_improved_eviscerate();

    talent->increment_rank();
    talent->increment_rank();
    talent->increment_rank();

    delete talent;
}

void TestEviscerate::given_1_of_3_aggression() {
    Talent* talent = Combat(rogue).get_aggression();

    assert(talent->increment_rank());

    delete talent;
}

void TestEviscerate::given_2_of_3_aggression() {
    Talent* talent = Combat(rogue).get_aggression();

    assert(talent->increment_rank());
    assert(talent->increment_rank());

    delete talent;
}

void TestEviscerate::given_3_of_3_aggression() {
    Talent* talent = Combat(rogue).get_aggression();

    assert(talent->increment_rank());
    assert(talent->increment_rank());
    assert(talent->increment_rank());

    delete talent;
}

void TestEviscerate::given_5_pc_deathdealer() {
    pchar->get_equipment()->set_chest(21364);
    assert(pchar->get_equipment()->get_chest() != nullptr);
    assert(pchar->get_equipment()->get_chest()->get_name() == "Deathdealer's Vest");

    pchar->get_equipment()->set_boots(21359);
    assert(pchar->get_equipment()->get_boots() != nullptr);
    assert(pchar->get_equipment()->get_boots()->get_name() == "Deathdealer's Boots");

    pchar->get_equipment()->set_head(21360);
    assert(pchar->get_equipment()->get_head() != nullptr);
    assert(pchar->get_equipment()->get_head()->get_name() == "Deathdealer's Helm");

    pchar->get_equipment()->set_shoulders(21361);
    assert(pchar->get_equipment()->get_shoulders() != nullptr);
    assert(pchar->get_equipment()->get_shoulders()->get_name() == "Deathdealer's Spaulders");

    pchar->get_equipment()->set_legs(21362);
    assert(pchar->get_equipment()->get_legs() != nullptr);
    assert(pchar->get_equipment()->get_legs()->get_name() == "Deathdealer's Leggings");
}

void TestEviscerate::when_eviscerate_is_performed() {
    if (pchar->get_equipment()->get_mainhand() == nullptr)
        given_a_mainhand_dagger_with_100_min_max_dmg();

    if (rogue->get_combo_points() == 0)
        rogue->gain_combo_points(1);

    eviscerate()->perform();
}
