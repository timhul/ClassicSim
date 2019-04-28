#include "TestSealOfTheCrusader.h"

#include "CharacterStats.h"
#include "Equipment.h"
#include "MainhandAttackPaladin.h"
#include "PaladinSpells.h"
#include "Retribution.h"
#include "SealOfTheCrusader.h"
#include "SealOfTheCrusaderBuff.h"
#include "Talent.h"

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
}

MainhandAttackPaladin* TestSealOfTheCrusader::mh_attack() {
    auto* spells = dynamic_cast<PaladinSpells*>(paladin->get_spells());
    return dynamic_cast<MainhandAttackPaladin*>(spells->get_mh_attack());
}

SealOfTheCrusader* TestSealOfTheCrusader::seal_of_the_crusader() {
    auto* spells = dynamic_cast<PaladinSpells*>(paladin->get_spells());
    return dynamic_cast<SealOfTheCrusader*>(spells->get_seal_of_the_crusader());
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
    given_benediction_rank(1);

    given_paladin_has_mana(154);
    assert(seal_of_the_crusader()->get_spell_status() == SpellStatus::InsufficientResources);

    given_paladin_has_mana(155);
    assert(seal_of_the_crusader()->get_spell_status() == SpellStatus::Available);

    given_paladin_has_mana(156);
    when_seal_of_the_crusader_is_performed();
    then_paladin_has_mana(1);
}

void TestSealOfTheCrusader::test_resource_cost_2_of_5_benediction() {
    given_benediction_rank(2);

    given_paladin_has_mana(149);
    assert(seal_of_the_crusader()->get_spell_status() == SpellStatus::InsufficientResources);

    given_paladin_has_mana(150);
    assert(seal_of_the_crusader()->get_spell_status() == SpellStatus::Available);

    given_paladin_has_mana(151);
    when_seal_of_the_crusader_is_performed();
    then_paladin_has_mana(1);
}

void TestSealOfTheCrusader::test_resource_cost_3_of_5_benediction() {
    given_benediction_rank(3);

    given_paladin_has_mana(145);
    assert(seal_of_the_crusader()->get_spell_status() == SpellStatus::InsufficientResources);

    given_paladin_has_mana(146);
    assert(seal_of_the_crusader()->get_spell_status() == SpellStatus::Available);

    given_paladin_has_mana(147);
    when_seal_of_the_crusader_is_performed();
    then_paladin_has_mana(1);
}

void TestSealOfTheCrusader::test_resource_cost_4_of_5_benediction() {
    given_benediction_rank(4);

    given_paladin_has_mana(140);
    assert(seal_of_the_crusader()->get_spell_status() == SpellStatus::InsufficientResources);

    given_paladin_has_mana(141);
    assert(seal_of_the_crusader()->get_spell_status() == SpellStatus::Available);

    given_paladin_has_mana(142);
    when_seal_of_the_crusader_is_performed();
    then_paladin_has_mana(1);
}

void TestSealOfTheCrusader::test_resource_cost_5_of_5_benediction() {
    given_benediction_rank(5);

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
    given_improved_sotc_rank(1);
    given_1000_melee_ap();

    when_seal_of_the_crusader_is_performed();

    assert(pchar->get_stats()->get_melee_ap() == 1000 + 321);
}

void TestSealOfTheCrusader::test_melee_ap_bonus_2_of_3_improved_sotc() {
    given_improved_sotc_rank(2);
    given_1000_melee_ap();

    when_seal_of_the_crusader_is_performed();

    assert(pchar->get_stats()->get_melee_ap() == 1000 + 337);
}

void TestSealOfTheCrusader::test_melee_ap_bonus_3_of_3_improved_sotc() {
    given_improved_sotc_rank(3);
    given_1000_melee_ap();

    when_seal_of_the_crusader_is_performed();

    assert(pchar->get_stats()->get_melee_ap() == 1000 + 352);
}

void TestSealOfTheCrusader::when_mh_attack_is_performed() {
    if (pchar->get_equipment()->get_mainhand() == nullptr)
        given_a_mainhand_weapon_with_100_min_max_dmg();

    mh_attack()->perform();
}

void TestSealOfTheCrusader::when_seal_of_the_crusader_is_performed() {
    if (pchar->get_equipment()->get_mainhand() == nullptr)
        given_a_mainhand_weapon_with_100_min_max_dmg();

    seal_of_the_crusader()->perform();
}

void TestSealOfTheCrusader::given_benediction_rank(const unsigned num) {
    given_talent_rank(Retribution(paladin).get_benediction(), num);
}

void TestSealOfTheCrusader::given_improved_sotc_rank(const unsigned num) {
    given_talent_rank(Retribution(paladin).get_improved_seal_of_the_crusader(), num);
}

void TestSealOfTheCrusader::given_seal_of_the_crusader_is_active() {
    seal_of_the_crusader()->perform();
    assert(seal_of_the_crusader()->get_buff()->is_active());
}
