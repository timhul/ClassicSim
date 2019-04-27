#include "TestPaladinTalentStatIncrease.h"

#include "CharacterStats.h"
#include "HolyPaladin.h"
#include "ProtectionPaladin.h"
#include "Retribution.h"
#include "Talent.h"

TestPaladinTalentStatIncrease::TestPaladinTalentStatIncrease(EquipmentDb* equipment_db) :
    TestSpellPaladin(equipment_db, "PaladinTalentStatIncrease")
{}

void TestPaladinTalentStatIncrease::test_all() {
    run_mandatory_tests();

    set_up();
    test_conviction();
    tear_down();

    set_up();
    test_two_handed_weapon_specialization();
    tear_down();

    set_up();
    test_precision();
    tear_down();

    set_up();
    test_one_handed_weapon_specialization();
    tear_down();

    set_up();
    test_divine_strength();
    tear_down();

    set_up();
    test_divine_intellect();
    tear_down();
}

void TestPaladinTalentStatIncrease::test_conviction() {
    Talent* talent = Retribution(paladin).get_conviction();
    unsigned melee_crit_initial = pchar->get_stats()->get_mh_crit_chance();
    unsigned ranged_crit_initial = pchar->get_stats()->get_ranged_crit_chance();

    assert(talent->increment_rank());
    assert(melee_crit_initial + 100 == pchar->get_stats()->get_mh_crit_chance());
    assert(ranged_crit_initial + 100 == pchar->get_stats()->get_ranged_crit_chance());

    assert(talent->increment_rank());
    assert(melee_crit_initial + 200 == pchar->get_stats()->get_mh_crit_chance());
    assert(ranged_crit_initial + 200 == pchar->get_stats()->get_ranged_crit_chance());

    assert(talent->increment_rank());
    assert(melee_crit_initial + 300 == pchar->get_stats()->get_mh_crit_chance());
    assert(ranged_crit_initial + 300 == pchar->get_stats()->get_ranged_crit_chance());

    assert(talent->increment_rank());
    assert(melee_crit_initial + 400 == pchar->get_stats()->get_mh_crit_chance());
    assert(ranged_crit_initial + 400 == pchar->get_stats()->get_ranged_crit_chance());

    assert(talent->increment_rank());
    assert(melee_crit_initial + 500 == pchar->get_stats()->get_mh_crit_chance());
    assert(ranged_crit_initial + 500 == pchar->get_stats()->get_ranged_crit_chance());

    assert(talent->decrement_rank());
    assert(melee_crit_initial + 400 == pchar->get_stats()->get_mh_crit_chance());
    assert(ranged_crit_initial + 400 == pchar->get_stats()->get_ranged_crit_chance());

    assert(talent->decrement_rank());
    assert(melee_crit_initial + 300 == pchar->get_stats()->get_mh_crit_chance());
    assert(ranged_crit_initial + 300 == pchar->get_stats()->get_ranged_crit_chance());

    assert(talent->decrement_rank());
    assert(melee_crit_initial + 200 == pchar->get_stats()->get_mh_crit_chance());
    assert(ranged_crit_initial + 200 == pchar->get_stats()->get_ranged_crit_chance());

    assert(talent->decrement_rank());
    assert(melee_crit_initial + 100 == pchar->get_stats()->get_mh_crit_chance());
    assert(ranged_crit_initial + 100 == pchar->get_stats()->get_ranged_crit_chance());

    assert(talent->decrement_rank());
    assert(melee_crit_initial == pchar->get_stats()->get_mh_crit_chance());
    assert(ranged_crit_initial == pchar->get_stats()->get_ranged_crit_chance());

    delete talent;
}

void TestPaladinTalentStatIncrease::test_two_handed_weapon_specialization() {
    given_a_twohand_weapon_with_100_min_max_dmg();
    Talent* talent = Retribution(paladin).get_two_handed_weapon_specialization();
    assert(almost_equal(1.0, paladin->get_stats()->get_total_phys_dmg_mod()));

    assert(talent->increment_rank());
    assert(almost_equal(1.02, paladin->get_stats()->get_total_phys_dmg_mod()));

    assert(talent->increment_rank());
    assert(almost_equal(1.04, paladin->get_stats()->get_total_phys_dmg_mod()));

    assert(talent->increment_rank());
    assert(almost_equal(1.06, paladin->get_stats()->get_total_phys_dmg_mod()));

    given_1h_mace_equipped_in_mainhand(paladin);
    assert(almost_equal(1.0, paladin->get_stats()->get_total_phys_dmg_mod()));

    given_a_twohand_weapon_with_100_min_max_dmg();
    assert(almost_equal(1.06, paladin->get_stats()->get_total_phys_dmg_mod()));

    assert(talent->decrement_rank());
    assert(almost_equal(1.04, paladin->get_stats()->get_total_phys_dmg_mod()));

    assert(talent->decrement_rank());
    assert(almost_equal(1.02, paladin->get_stats()->get_total_phys_dmg_mod()));

    assert(talent->decrement_rank());
    assert(almost_equal(1.0, paladin->get_stats()->get_total_phys_dmg_mod()));

    delete talent;
}

void TestPaladinTalentStatIncrease::test_precision() {
    Talent* talent = ProtectionPaladin(paladin).get_precision();
    unsigned melee_hit_initial = pchar->get_stats()->get_melee_hit_chance();
    unsigned ranged_hit_initial = pchar->get_stats()->get_ranged_hit_chance();

    assert(talent->increment_rank());
    assert(melee_hit_initial + 100 == pchar->get_stats()->get_melee_hit_chance());
    assert(ranged_hit_initial + 100 == pchar->get_stats()->get_ranged_hit_chance());

    assert(talent->increment_rank());
    assert(melee_hit_initial + 200 == pchar->get_stats()->get_melee_hit_chance());
    assert(ranged_hit_initial + 200 == pchar->get_stats()->get_ranged_hit_chance());

    assert(talent->increment_rank());
    assert(melee_hit_initial + 300 == pchar->get_stats()->get_melee_hit_chance());
    assert(ranged_hit_initial + 300 == pchar->get_stats()->get_ranged_hit_chance());

    assert(talent->decrement_rank());
    assert(melee_hit_initial + 200 == pchar->get_stats()->get_melee_hit_chance());
    assert(ranged_hit_initial + 200 == pchar->get_stats()->get_ranged_hit_chance());

    assert(talent->decrement_rank());
    assert(melee_hit_initial + 100 == pchar->get_stats()->get_melee_hit_chance());
    assert(ranged_hit_initial + 100 == pchar->get_stats()->get_ranged_hit_chance());

    assert(talent->decrement_rank());
    assert(melee_hit_initial == pchar->get_stats()->get_melee_hit_chance());
    assert(ranged_hit_initial == pchar->get_stats()->get_ranged_hit_chance());

    delete talent;
}

void TestPaladinTalentStatIncrease::test_one_handed_weapon_specialization() {
    given_1h_mace_equipped_in_mainhand(paladin);
    Talent* talent = ProtectionPaladin(paladin).get_one_handed_weapon_specialization();
    assert(almost_equal(1.0, paladin->get_stats()->get_total_phys_dmg_mod()));

    assert(talent->increment_rank());
    assert(almost_equal(1.02, paladin->get_stats()->get_total_phys_dmg_mod()));

    assert(talent->increment_rank());
    assert(almost_equal(1.04, paladin->get_stats()->get_total_phys_dmg_mod()));

    assert(talent->increment_rank());
    assert(almost_equal(1.06, paladin->get_stats()->get_total_phys_dmg_mod()));

    assert(talent->increment_rank());
    assert(almost_equal(1.08, paladin->get_stats()->get_total_phys_dmg_mod()));

    assert(talent->increment_rank());
    assert(almost_equal(1.10, paladin->get_stats()->get_total_phys_dmg_mod()));

    given_a_twohand_weapon_with_100_min_max_dmg();
    assert(almost_equal(1.0, paladin->get_stats()->get_total_phys_dmg_mod()));

    given_1h_mace_equipped_in_mainhand(paladin);
    assert(almost_equal(1.10, paladin->get_stats()->get_total_phys_dmg_mod()));

    assert(talent->decrement_rank());
    assert(almost_equal(1.08, paladin->get_stats()->get_total_phys_dmg_mod()));

    assert(talent->decrement_rank());
    assert(almost_equal(1.06, paladin->get_stats()->get_total_phys_dmg_mod()));

    assert(talent->decrement_rank());
    assert(almost_equal(1.04, paladin->get_stats()->get_total_phys_dmg_mod()));

    assert(talent->decrement_rank());
    assert(almost_equal(1.02, paladin->get_stats()->get_total_phys_dmg_mod()));

    assert(talent->decrement_rank());
    assert(almost_equal(1.0, paladin->get_stats()->get_total_phys_dmg_mod()));

    delete talent;
}

void TestPaladinTalentStatIncrease::test_divine_strength() {
    Talent* talent = HolyPaladin(paladin).get_divine_strength();
    given_character_has_strength(100);

    assert(talent->increment_rank());
    assert(pchar->get_stats()->get_strength() == 102);

    assert(talent->increment_rank());
    assert(pchar->get_stats()->get_strength() == 104);

    assert(talent->increment_rank());
    assert(pchar->get_stats()->get_strength() == 106);

    assert(talent->increment_rank());
    assert(pchar->get_stats()->get_strength() == 108);

    assert(talent->increment_rank());
    assert(pchar->get_stats()->get_strength() == 110);

    assert(talent->decrement_rank());
    assert(pchar->get_stats()->get_strength() == 108);

    assert(talent->decrement_rank());
    assert(pchar->get_stats()->get_strength() == 106);

    assert(talent->decrement_rank());
    assert(pchar->get_stats()->get_strength() == 104);

    assert(talent->decrement_rank());
    assert(pchar->get_stats()->get_strength() == 102);

    assert(talent->decrement_rank());
    assert(pchar->get_stats()->get_strength() == 100);

    delete talent;
}

void TestPaladinTalentStatIncrease::test_divine_intellect() {
    Talent* talent = HolyPaladin(paladin).get_divine_intellect();
    given_character_has_intellect(100);

    assert(talent->increment_rank());
    assert(pchar->get_stats()->get_intellect() == 102);

    assert(talent->increment_rank());
    assert(pchar->get_stats()->get_intellect() == 104);

    assert(talent->increment_rank());
    assert(pchar->get_stats()->get_intellect() == 106);

    assert(talent->increment_rank());
    assert(pchar->get_stats()->get_intellect() == 108);

    assert(talent->increment_rank());
    assert(pchar->get_stats()->get_intellect() == 110);

    assert(talent->decrement_rank());
    assert(pchar->get_stats()->get_intellect() == 108);

    assert(talent->decrement_rank());
    assert(pchar->get_stats()->get_intellect() == 106);

    assert(talent->decrement_rank());
    assert(pchar->get_stats()->get_intellect() == 104);

    assert(talent->decrement_rank());
    assert(pchar->get_stats()->get_intellect() == 102);

    assert(talent->decrement_rank());
    assert(pchar->get_stats()->get_intellect() == 100);

    delete talent;
}

void TestPaladinTalentStatIncrease::test_name_correct() {
}

void TestPaladinTalentStatIncrease::test_spell_cooldown() {
}

void TestPaladinTalentStatIncrease::test_how_spell_observes_global_cooldown() {
}

void TestPaladinTalentStatIncrease::test_resource_cost() {
}

void TestPaladinTalentStatIncrease::test_is_ready_conditions() {
}

void TestPaladinTalentStatIncrease::test_whether_spell_causes_global_cooldown() {
}
