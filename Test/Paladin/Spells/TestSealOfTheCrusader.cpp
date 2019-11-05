#include "TestSealOfTheCrusader.h"

#include <cassert>

#include "Buff.h"
#include "CharacterStats.h"
#include "Paladin.h"
#include "SealOfCommand.h"
#include "SealOfTheCrusader.h"

TestSealOfTheCrusader::TestSealOfTheCrusader(EquipmentDb *equipment_db) :
    TestSpellPaladin(equipment_db, "Seal of the Crusader")
{}

void TestSealOfTheCrusader::test_all() {
    run_mandatory_tests();

    set_up();
    test_seal_of_the_crusader_lowers_damage();
    tear_down();

    set_up();
    test_seal_removal_restores_damage();
    tear_down();

    set_up();
    test_resource_cost_1_of_5_benediction();
    tear_down();

    set_up();
    test_resource_cost_2_of_5_benediction();
    tear_down();

    set_up();
    test_resource_cost_3_of_5_benediction();
    tear_down();

    set_up();
    test_resource_cost_4_of_5_benediction();
    tear_down();

    set_up();
    test_resource_cost_5_of_5_benediction();
    tear_down();

    set_up();
    test_melee_ap_bonus_0_of_3_improved_sotc();
    tear_down();

    set_up();
    test_melee_ap_bonus_1_of_3_improved_sotc();
    tear_down();

    set_up();
    test_melee_ap_bonus_2_of_3_improved_sotc();
    tear_down();

    set_up();
    test_melee_ap_bonus_3_of_3_improved_sotc();
    tear_down();

    set_up(false);
    test_seal_of_the_crusader_removes_active_seal_of_command();
    tear_down();

    set_up();
    test_libram_of_fervor_increases_melee_ap_bonus();
    tear_down();

    set_up();
    test_libram_of_hope_reduces_mana_cost();
    tear_down();

    set_up();
    test_auto_attack_hit_refreshes_duration_while_no_seal_is_active();
    tear_down();

    set_up();
    test_auto_attack_crit_refreshes_duration_while_no_seal_is_active();
    tear_down();

    set_up();
    test_auto_attack_glancing_refreshes_duration_while_no_seal_is_active();
    tear_down();

    set_up();
    test_auto_attack_dodge_does_not_refresh_duration_while_no_seal_is_active();
    tear_down();

    set_up();
    test_auto_attack_miss_does_not_refresh_duration_while_no_seal_is_active();
    tear_down();

    set_up(false);
    test_auto_attack_hit_refreshes_duration_while_seal_of_command_is_active();
    tear_down();

    set_up(false);
    test_auto_attack_crit_refreshes_duration_while_seal_of_command_is_active();
    tear_down();

    set_up(false);
    test_auto_attack_glancing_refreshes_duration_while_seal_of_command_is_active();
    tear_down();

    set_up(false);
    test_auto_attack_dodge_does_not_refresh_duration_while_seal_of_command_is_active();
    tear_down();

    set_up(false);
    test_auto_attack_miss_does_not_refresh_duration_while_seal_of_command_is_active();
    tear_down();
}

void TestSealOfTheCrusader::test_name_correct() {
    assert(seal_of_the_crusader()->get_name() == "Seal of the Crusader");
}

void TestSealOfTheCrusader::test_spell_cooldown() {
    assert(almost_equal(seal_of_the_crusader()->get_base_cooldown(), 0.0));
}

void TestSealOfTheCrusader::test_how_spell_observes_global_cooldown() {
    assert(seal_of_the_crusader()->get_spell_status() == SpellStatus::Available);

    given_paladin_is_on_gcd();

    assert(seal_of_the_crusader()->get_spell_status() == SpellStatus::OnGCD);
}

void TestSealOfTheCrusader::test_resource_cost() {
    given_paladin_has_mana(159);
    assert(seal_of_the_crusader()->get_spell_status() == SpellStatus::InsufficientResources);

    given_paladin_has_mana(160);
    assert(seal_of_the_crusader()->get_spell_status() == SpellStatus::Available);

    given_paladin_has_mana(161);
    when_seal_of_the_crusader_is_performed();
    then_paladin_has_mana(1);
}

void TestSealOfTheCrusader::test_is_ready_conditions() {
    // No conditions not tested in other mandatory tests.
}

void TestSealOfTheCrusader::test_whether_spell_causes_global_cooldown() {
    assert(paladin->action_ready());

    when_seal_of_the_crusader_is_performed();

    assert(!paladin->action_ready());
}

void TestSealOfTheCrusader::test_seal_of_the_crusader_lowers_damage() {
    given_target_has_0_armor();
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_white_hit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_seal_of_the_crusader_is_active();

    when_mh_attack_is_performed();

    // [Damage] = (base_dmg + (wpn_speed * AP / 14)) * sotc_penalty
    // [245] = (100 + (2.6 * (1000 + 306) / 14)) * (1 / 1.4)
    then_damage_dealt_is(245);
}

void TestSealOfTheCrusader::test_seal_removal_restores_damage() {
    given_target_has_0_armor();
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_white_hit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_seal_of_the_crusader_is_active();

    seal_of_the_crusader()->get_buff()->cancel_buff();
    when_mh_attack_is_performed();

    // [Damage] = base_dmg + (wpn_speed * AP / 14)
    // [286] = 100 + (2.6 * 1000 / 14)
    then_damage_dealt_is(286);
}

void TestSealOfTheCrusader::test_resource_cost_1_of_5_benediction() {
    given_retribution_talent_rank("Benediction", 1);

    given_paladin_has_mana(154);
    assert(seal_of_the_crusader()->get_spell_status() == SpellStatus::InsufficientResources);

    given_paladin_has_mana(155);
    assert(seal_of_the_crusader()->get_spell_status() == SpellStatus::Available);

    given_paladin_has_mana(156);
    when_seal_of_the_crusader_is_performed();
    then_paladin_has_mana(1);
}

void TestSealOfTheCrusader::test_resource_cost_2_of_5_benediction() {
    given_retribution_talent_rank("Benediction", 2);

    given_paladin_has_mana(149);
    assert(seal_of_the_crusader()->get_spell_status() == SpellStatus::InsufficientResources);

    given_paladin_has_mana(150);
    assert(seal_of_the_crusader()->get_spell_status() == SpellStatus::Available);

    given_paladin_has_mana(151);
    when_seal_of_the_crusader_is_performed();
    then_paladin_has_mana(1);
}

void TestSealOfTheCrusader::test_resource_cost_3_of_5_benediction() {
    given_retribution_talent_rank("Benediction", 3);

    given_paladin_has_mana(145);
    assert(seal_of_the_crusader()->get_spell_status() == SpellStatus::InsufficientResources);

    given_paladin_has_mana(146);
    assert(seal_of_the_crusader()->get_spell_status() == SpellStatus::Available);

    given_paladin_has_mana(147);
    when_seal_of_the_crusader_is_performed();
    then_paladin_has_mana(1);
}

void TestSealOfTheCrusader::test_resource_cost_4_of_5_benediction() {
    given_retribution_talent_rank("Benediction", 4);

    given_paladin_has_mana(140);
    assert(seal_of_the_crusader()->get_spell_status() == SpellStatus::InsufficientResources);

    given_paladin_has_mana(141);
    assert(seal_of_the_crusader()->get_spell_status() == SpellStatus::Available);

    given_paladin_has_mana(142);
    when_seal_of_the_crusader_is_performed();
    then_paladin_has_mana(1);
}

void TestSealOfTheCrusader::test_resource_cost_5_of_5_benediction() {
    given_retribution_talent_rank("Benediction", 5);

    given_paladin_has_mana(135);
    assert(seal_of_the_crusader()->get_spell_status() == SpellStatus::InsufficientResources);

    given_paladin_has_mana(136);
    assert(seal_of_the_crusader()->get_spell_status() == SpellStatus::Available);

    given_paladin_has_mana(137);
    when_seal_of_the_crusader_is_performed();
    then_paladin_has_mana(1);
}

void TestSealOfTheCrusader::test_melee_ap_bonus_0_of_3_improved_sotc() {
    given_1000_melee_ap();

    when_seal_of_the_crusader_is_performed();

    assert(pchar->get_stats()->get_melee_ap() == 1000 + 306);
}

void TestSealOfTheCrusader::test_melee_ap_bonus_1_of_3_improved_sotc() {
    given_retribution_talent_rank("Improved Seal of the Crusader", 1);
    given_1000_melee_ap();

    when_seal_of_the_crusader_is_performed();

    assert(pchar->get_stats()->get_melee_ap() == 1000 + 321);
}

void TestSealOfTheCrusader::test_melee_ap_bonus_2_of_3_improved_sotc() {
    given_retribution_talent_rank("Improved Seal of the Crusader", 2);
    given_1000_melee_ap();

    when_seal_of_the_crusader_is_performed();

    assert(pchar->get_stats()->get_melee_ap() == 1000 + 337);
}

void TestSealOfTheCrusader::test_melee_ap_bonus_3_of_3_improved_sotc() {
    given_retribution_talent_rank("Improved Seal of the Crusader", 3);
    given_1000_melee_ap();

    when_seal_of_the_crusader_is_performed();

    assert(pchar->get_stats()->get_melee_ap() == 1000 + 352);
}

void TestSealOfTheCrusader::test_seal_of_the_crusader_removes_active_seal_of_command() {
    given_seal_of_command_is_active();
    given_engine_priority_pushed_forward(1.5);
    assert(seal_of_command()->get_buff()->is_active());

    when_seal_of_the_crusader_is_performed();

    assert(!seal_of_command()->get_buff()->is_active());
}

void TestSealOfTheCrusader::test_libram_of_fervor_increases_melee_ap_bonus() {
    given_relic_equipped(23203);
    given_1000_melee_ap();
    given_retribution_talent_rank("Improved Seal of the Crusader", 3);

    when_seal_of_the_crusader_is_performed();

    // [ap_bonus] = (base + relic_bonus) * improved_sotc_mod
    // [407] = (306 + 48) * 1.15
    assert(pchar->get_stats()->get_melee_ap() == 1000 + 407);
}

void TestSealOfTheCrusader::test_libram_of_hope_reduces_mana_cost() {
    const double original_mana_cost = seal_of_the_crusader()->get_resource_cost();

    given_relic_equipped(22401);
    assert(almost_equal(20.0, original_mana_cost - seal_of_the_crusader()->get_resource_cost()));

    given_no_relic_equipped();
    assert(almost_equal(0.0, original_mana_cost - seal_of_the_crusader()->get_resource_cost()));
}

void TestSealOfTheCrusader::test_auto_attack_hit_refreshes_duration_while_no_seal_is_active() {
    given_2h_sword_equipped(paladin);
    given_a_guaranteed_white_hit();
    given_a_guaranteed_ranged_white_hit();
    given_seal_of_the_crusader_is_active();

    when_judgement_is_performed();
    assert(seal_of_the_crusader()->get_buff()->is_active() == false);
    given_engine_priority_pushed_forward(5.0);
    assert(almost_equal(5.0, seal_of_the_crusader()->get_judge_debuff()->time_left()));

    when_mh_attack_is_performed();
    assert(almost_equal(10.0, seal_of_the_crusader()->get_judge_debuff()->time_left()));
}

void TestSealOfTheCrusader::test_auto_attack_crit_refreshes_duration_while_no_seal_is_active() {
    given_2h_sword_equipped(paladin);
    given_a_guaranteed_white_crit();
    given_a_guaranteed_ranged_white_hit();
    given_seal_of_the_crusader_is_active();

    when_judgement_is_performed();
    assert(seal_of_the_crusader()->get_buff()->is_active() == false);
    given_engine_priority_pushed_forward(5.0);
    assert(almost_equal(5.0, seal_of_the_crusader()->get_judge_debuff()->time_left()));

    when_mh_attack_is_performed();
    assert(almost_equal(10.0, seal_of_the_crusader()->get_judge_debuff()->time_left()));
}

void TestSealOfTheCrusader::test_auto_attack_glancing_refreshes_duration_while_no_seal_is_active() {
    given_2h_sword_equipped(paladin);
    given_a_guaranteed_white_glancing_blow();
    given_a_guaranteed_ranged_white_hit();
    given_seal_of_the_crusader_is_active();

    when_judgement_is_performed();
    assert(seal_of_the_crusader()->get_buff()->is_active() == false);
    given_engine_priority_pushed_forward(5.0);
    assert(almost_equal(5.0, seal_of_the_crusader()->get_judge_debuff()->time_left()));

    when_mh_attack_is_performed();
    assert(almost_equal(10.0, seal_of_the_crusader()->get_judge_debuff()->time_left()));
}

void TestSealOfTheCrusader::test_auto_attack_dodge_does_not_refresh_duration_while_no_seal_is_active() {
    given_2h_sword_equipped(paladin);
    given_a_guaranteed_white_dodge();
    given_a_guaranteed_ranged_white_hit();
    given_seal_of_the_crusader_is_active();

    when_judgement_is_performed();
    assert(seal_of_the_crusader()->get_buff()->is_active() == false);
    given_engine_priority_pushed_forward(5.0);
    assert(almost_equal(5.0, seal_of_the_crusader()->get_judge_debuff()->time_left()));

    when_mh_attack_is_performed();
    assert(almost_equal(5.0, seal_of_the_crusader()->get_judge_debuff()->time_left()));
}

void TestSealOfTheCrusader::test_auto_attack_miss_does_not_refresh_duration_while_no_seal_is_active() {
    given_2h_sword_equipped(paladin);
    given_a_guaranteed_white_miss();
    given_a_guaranteed_ranged_white_hit();
    given_seal_of_the_crusader_is_active();

    when_judgement_is_performed();
    assert(seal_of_the_crusader()->get_buff()->is_active() == false);
    given_engine_priority_pushed_forward(5.0);
    assert(almost_equal(5.0, seal_of_the_crusader()->get_judge_debuff()->time_left()));

    when_mh_attack_is_performed();
    assert(almost_equal(5.0, seal_of_the_crusader()->get_judge_debuff()->time_left()));
}

void TestSealOfTheCrusader::test_auto_attack_hit_refreshes_duration_while_seal_of_command_is_active() {
    given_retribution_talent_rank("Seal of Command", 1);
    paladin->prepare_set_of_combat_iterations();
    given_2h_sword_equipped(paladin);
    given_a_guaranteed_white_hit();
    given_a_guaranteed_ranged_white_hit();
    given_seal_of_the_crusader_is_active();

    when_judgement_is_performed();
    assert(seal_of_the_crusader()->get_buff()->is_active() == false);
    given_engine_priority_pushed_forward(5.0);
    assert(almost_equal(5.0, seal_of_the_crusader()->get_judge_debuff()->time_left()));
    seal_of_command()->perform();

    when_mh_attack_is_performed();
    assert(almost_equal(10.0, seal_of_the_crusader()->get_judge_debuff()->time_left()));
}

void TestSealOfTheCrusader::test_auto_attack_crit_refreshes_duration_while_seal_of_command_is_active() {
    given_retribution_talent_rank("Seal of Command", 1);
    paladin->prepare_set_of_combat_iterations();
    given_2h_sword_equipped(paladin);
    given_a_guaranteed_white_crit();
    given_a_guaranteed_ranged_white_hit();
    given_seal_of_the_crusader_is_active();

    when_judgement_is_performed();
    assert(seal_of_the_crusader()->get_buff()->is_active() == false);
    given_engine_priority_pushed_forward(5.0);
    assert(almost_equal(5.0, seal_of_the_crusader()->get_judge_debuff()->time_left()));
    seal_of_command()->perform();

    when_mh_attack_is_performed();
    assert(almost_equal(10.0, seal_of_the_crusader()->get_judge_debuff()->time_left()));
}

void TestSealOfTheCrusader::test_auto_attack_glancing_refreshes_duration_while_seal_of_command_is_active() {
    given_retribution_talent_rank("Seal of Command", 1);
    paladin->prepare_set_of_combat_iterations();
    given_2h_sword_equipped(paladin);
    given_a_guaranteed_white_glancing_blow();
    given_a_guaranteed_ranged_white_hit();
    given_seal_of_the_crusader_is_active();

    when_judgement_is_performed();
    assert(seal_of_the_crusader()->get_buff()->is_active() == false);
    given_engine_priority_pushed_forward(5.0);
    assert(almost_equal(5.0, seal_of_the_crusader()->get_judge_debuff()->time_left()));
    seal_of_command()->perform();

    when_mh_attack_is_performed();
    assert(almost_equal(10.0, seal_of_the_crusader()->get_judge_debuff()->time_left()));
}

void TestSealOfTheCrusader::test_auto_attack_dodge_does_not_refresh_duration_while_seal_of_command_is_active() {
    given_retribution_talent_rank("Seal of Command", 1);
    paladin->prepare_set_of_combat_iterations();
    given_2h_sword_equipped(paladin);
    given_a_guaranteed_white_dodge();
    given_a_guaranteed_ranged_white_hit();
    given_seal_of_the_crusader_is_active();

    when_judgement_is_performed();
    assert(seal_of_the_crusader()->get_buff()->is_active() == false);
    given_engine_priority_pushed_forward(5.0);
    assert(almost_equal(5.0, seal_of_the_crusader()->get_judge_debuff()->time_left()));
    seal_of_command()->perform();

    when_mh_attack_is_performed();
    assert(almost_equal(5.0, seal_of_the_crusader()->get_judge_debuff()->time_left()));
}

void TestSealOfTheCrusader::test_auto_attack_miss_does_not_refresh_duration_while_seal_of_command_is_active() {
    given_retribution_talent_rank("Seal of Command", 1);
    paladin->prepare_set_of_combat_iterations();
    given_2h_sword_equipped(paladin);
    given_a_guaranteed_white_miss();
    given_a_guaranteed_ranged_white_hit();
    given_seal_of_the_crusader_is_active();

    when_judgement_is_performed();
    assert(seal_of_the_crusader()->get_buff()->is_active() == false);
    given_engine_priority_pushed_forward(5.0);
    assert(almost_equal(5.0, seal_of_the_crusader()->get_judge_debuff()->time_left()));
    seal_of_command()->perform();

    when_mh_attack_is_performed();
    assert(almost_equal(5.0, seal_of_the_crusader()->get_judge_debuff()->time_left()));
}
