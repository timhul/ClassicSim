#include "TestMageTalentStatIncrease.h"

#include "Arcane.h"
#include "Character.h"
#include "CharacterStats.h"
#include "Fire.h"
#include "Frost.h"
#include "Talent.h"

TestMageTalentStatIncrease::TestMageTalentStatIncrease(EquipmentDb* equipment_db) :
    TestSpellMage(equipment_db, "MageTalentStatIncrease")
{}

void TestMageTalentStatIncrease::test_all() {
    run_mandatory_tests();

    set_up();
    test_fire_power();
    tear_down();

    set_up();
    test_elemental_precision();
    tear_down();

    set_up();
    test_arcane_subtlety();
    tear_down();

    set_up();
    test_arcane_focus();
    tear_down();

    set_up();
    test_piercing_ice();
    tear_down();
}

void TestMageTalentStatIncrease::test_fire_power() {
    auto tree = Fire(mage);
    Talent* talent = tree.get_talent_from_name("Fire Power");

    assert(almost_equal(1.0, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Fire)));

    assert(talent->increment_rank());
    assert(almost_equal(1.02, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Fire)));

    assert(talent->increment_rank());
    assert(almost_equal(1.04, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Fire)));

    assert(talent->increment_rank());
    assert(almost_equal(1.06, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Fire)));

    assert(talent->increment_rank());
    assert(almost_equal(1.08, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Fire)));

    assert(talent->increment_rank());
    assert(almost_equal(1.10, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Fire)));

    assert(talent->decrement_rank());
    assert(almost_equal(1.08, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Fire)));

    assert(talent->decrement_rank());
    assert(almost_equal(1.06, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Fire)));

    assert(talent->decrement_rank());
    assert(almost_equal(1.04, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Fire)));

    assert(talent->decrement_rank());
    assert(almost_equal(1.02, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Fire)));

    assert(talent->decrement_rank());
    assert(almost_equal(1.0, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Fire)));
}

void TestMageTalentStatIncrease::test_elemental_precision() {
    auto tree = Frost(mage);
    Talent* talent = tree.get_talent_from_name("Elemental Precision");

    unsigned initial_hit_arcane = pchar->get_stats()->get_spell_hit_chance(MagicSchool::Arcane);
    unsigned initial_hit_fire = pchar->get_stats()->get_spell_hit_chance(MagicSchool::Fire);
    unsigned initial_hit_frost = pchar->get_stats()->get_spell_hit_chance(MagicSchool::Frost);

    assert(talent->increment_rank());
    assert(initial_hit_arcane == pchar->get_stats()->get_spell_hit_chance(MagicSchool::Arcane));
    assert(initial_hit_fire + 200 == pchar->get_stats()->get_spell_hit_chance(MagicSchool::Fire));
    assert(initial_hit_frost + 200 == pchar->get_stats()->get_spell_hit_chance(MagicSchool::Frost));

    assert(talent->increment_rank());
    assert(initial_hit_arcane == pchar->get_stats()->get_spell_hit_chance(MagicSchool::Arcane));
    assert(initial_hit_fire + 400 == pchar->get_stats()->get_spell_hit_chance(MagicSchool::Fire));
    assert(initial_hit_frost + 400 == pchar->get_stats()->get_spell_hit_chance(MagicSchool::Frost));

    assert(talent->increment_rank());
    assert(initial_hit_arcane == pchar->get_stats()->get_spell_hit_chance(MagicSchool::Arcane));
    assert(initial_hit_fire + 600 == pchar->get_stats()->get_spell_hit_chance(MagicSchool::Fire));
    assert(initial_hit_frost + 600 == pchar->get_stats()->get_spell_hit_chance(MagicSchool::Frost));

    assert(talent->decrement_rank());
    assert(initial_hit_arcane == pchar->get_stats()->get_spell_hit_chance(MagicSchool::Arcane));
    assert(initial_hit_fire + 400 == pchar->get_stats()->get_spell_hit_chance(MagicSchool::Fire));
    assert(initial_hit_frost + 400 == pchar->get_stats()->get_spell_hit_chance(MagicSchool::Frost));

    assert(talent->decrement_rank());
    assert(initial_hit_arcane == pchar->get_stats()->get_spell_hit_chance(MagicSchool::Arcane));
    assert(initial_hit_fire + 200 == pchar->get_stats()->get_spell_hit_chance(MagicSchool::Fire));
    assert(initial_hit_frost + 200 == pchar->get_stats()->get_spell_hit_chance(MagicSchool::Frost));

    assert(talent->decrement_rank());
    assert(initial_hit_arcane == pchar->get_stats()->get_spell_hit_chance(MagicSchool::Arcane));
    assert(initial_hit_fire == pchar->get_stats()->get_spell_hit_chance(MagicSchool::Fire));
    assert(initial_hit_frost == pchar->get_stats()->get_spell_hit_chance(MagicSchool::Frost));
}

void TestMageTalentStatIncrease::test_arcane_subtlety() {
    auto tree = Arcane(mage);
    Talent* talent = tree.get_talent_from_name("Arcane Subtlety");

    unsigned initial_target_res_arcane = pchar->get_stats()->get_target_resistance(MagicSchool::Arcane);
    unsigned initial_target_res_fire = pchar->get_stats()->get_target_resistance(MagicSchool::Fire);
    unsigned initial_target_res_frost = pchar->get_stats()->get_target_resistance(MagicSchool::Frost);

    assert(talent->increment_rank());
    assert(initial_target_res_arcane - 5 == pchar->get_stats()->get_target_resistance(MagicSchool::Arcane));
    assert(initial_target_res_fire - 5 == pchar->get_stats()->get_target_resistance(MagicSchool::Fire));
    assert(initial_target_res_frost - 5 == pchar->get_stats()->get_target_resistance(MagicSchool::Frost));

    assert(talent->increment_rank());
    assert(initial_target_res_arcane - 10 == pchar->get_stats()->get_target_resistance(MagicSchool::Arcane));
    assert(initial_target_res_fire - 10 == pchar->get_stats()->get_target_resistance(MagicSchool::Fire));
    assert(initial_target_res_frost - 10 == pchar->get_stats()->get_target_resistance(MagicSchool::Frost));

    assert(talent->decrement_rank());
    assert(initial_target_res_arcane - 5 == pchar->get_stats()->get_target_resistance(MagicSchool::Arcane));
    assert(initial_target_res_fire - 5 == pchar->get_stats()->get_target_resistance(MagicSchool::Fire));
    assert(initial_target_res_frost - 5 == pchar->get_stats()->get_target_resistance(MagicSchool::Frost));

    assert(talent->decrement_rank());
    assert(initial_target_res_arcane == pchar->get_stats()->get_target_resistance(MagicSchool::Arcane));
    assert(initial_target_res_fire == pchar->get_stats()->get_target_resistance(MagicSchool::Fire));
    assert(initial_target_res_frost == pchar->get_stats()->get_target_resistance(MagicSchool::Frost));
}

void TestMageTalentStatIncrease::test_arcane_focus() {
    auto tree = Arcane(mage);
    Talent* talent = tree.get_talent_from_name("Arcane Focus");

    unsigned initial_hit_arcane = pchar->get_stats()->get_spell_hit_chance(MagicSchool::Arcane);
    unsigned initial_hit_fire = pchar->get_stats()->get_spell_hit_chance(MagicSchool::Fire);
    unsigned initial_hit_frost = pchar->get_stats()->get_spell_hit_chance(MagicSchool::Frost);

    assert(talent->increment_rank());
    assert(initial_hit_arcane + 200 == pchar->get_stats()->get_spell_hit_chance(MagicSchool::Arcane));
    assert(initial_hit_fire == pchar->get_stats()->get_spell_hit_chance(MagicSchool::Fire));
    assert(initial_hit_frost == pchar->get_stats()->get_spell_hit_chance(MagicSchool::Frost));

    assert(talent->increment_rank());
    assert(initial_hit_arcane + 400 == pchar->get_stats()->get_spell_hit_chance(MagicSchool::Arcane));
    assert(initial_hit_fire == pchar->get_stats()->get_spell_hit_chance(MagicSchool::Fire));
    assert(initial_hit_frost == pchar->get_stats()->get_spell_hit_chance(MagicSchool::Frost));

    assert(talent->increment_rank());
    assert(initial_hit_arcane + 600 == pchar->get_stats()->get_spell_hit_chance(MagicSchool::Arcane));
    assert(initial_hit_fire == pchar->get_stats()->get_spell_hit_chance(MagicSchool::Fire));
    assert(initial_hit_frost == pchar->get_stats()->get_spell_hit_chance(MagicSchool::Frost));

    assert(talent->increment_rank());
    assert(initial_hit_arcane + 800 == pchar->get_stats()->get_spell_hit_chance(MagicSchool::Arcane));
    assert(initial_hit_fire == pchar->get_stats()->get_spell_hit_chance(MagicSchool::Fire));
    assert(initial_hit_frost == pchar->get_stats()->get_spell_hit_chance(MagicSchool::Frost));

    assert(talent->increment_rank());
    assert(initial_hit_arcane + 1000 == pchar->get_stats()->get_spell_hit_chance(MagicSchool::Arcane));
    assert(initial_hit_fire == pchar->get_stats()->get_spell_hit_chance(MagicSchool::Fire));
    assert(initial_hit_frost == pchar->get_stats()->get_spell_hit_chance(MagicSchool::Frost));

    assert(talent->decrement_rank());
    assert(initial_hit_arcane + 800 == pchar->get_stats()->get_spell_hit_chance(MagicSchool::Arcane));
    assert(initial_hit_fire == pchar->get_stats()->get_spell_hit_chance(MagicSchool::Fire));
    assert(initial_hit_frost == pchar->get_stats()->get_spell_hit_chance(MagicSchool::Frost));

    assert(talent->decrement_rank());
    assert(initial_hit_arcane + 600 == pchar->get_stats()->get_spell_hit_chance(MagicSchool::Arcane));
    assert(initial_hit_fire == pchar->get_stats()->get_spell_hit_chance(MagicSchool::Fire));
    assert(initial_hit_frost == pchar->get_stats()->get_spell_hit_chance(MagicSchool::Frost));

    assert(talent->decrement_rank());
    assert(initial_hit_arcane + 400 == pchar->get_stats()->get_spell_hit_chance(MagicSchool::Arcane));
    assert(initial_hit_fire == pchar->get_stats()->get_spell_hit_chance(MagicSchool::Fire));
    assert(initial_hit_frost == pchar->get_stats()->get_spell_hit_chance(MagicSchool::Frost));

    assert(talent->decrement_rank());
    assert(initial_hit_arcane + 200 == pchar->get_stats()->get_spell_hit_chance(MagicSchool::Arcane));
    assert(initial_hit_fire == pchar->get_stats()->get_spell_hit_chance(MagicSchool::Fire));
    assert(initial_hit_frost == pchar->get_stats()->get_spell_hit_chance(MagicSchool::Frost));

    assert(talent->decrement_rank());
    assert(initial_hit_arcane == pchar->get_stats()->get_spell_hit_chance(MagicSchool::Arcane));
    assert(initial_hit_fire == pchar->get_stats()->get_spell_hit_chance(MagicSchool::Fire));
    assert(initial_hit_frost == pchar->get_stats()->get_spell_hit_chance(MagicSchool::Frost));
}

void TestMageTalentStatIncrease::test_piercing_ice() {
    auto tree = Frost(mage);
    Talent* talent = tree.get_talent_from_name("Piercing Ice");

    assert(almost_equal(1.0, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Frost)));

    assert(talent->increment_rank());
    assert(almost_equal(1.02, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Frost)));

    assert(talent->increment_rank());
    assert(almost_equal(1.04, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Frost)));

    assert(talent->increment_rank());
    assert(almost_equal(1.06, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Frost)));

    assert(talent->decrement_rank());
    assert(almost_equal(1.04, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Frost)));

    assert(talent->decrement_rank());
    assert(almost_equal(1.02, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Frost)));

    assert(talent->decrement_rank());
    assert(almost_equal(1.0, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Frost)));
}

void TestMageTalentStatIncrease::test_name_correct() {
}

void TestMageTalentStatIncrease::test_spell_cooldown() {
}

void TestMageTalentStatIncrease::test_how_spell_observes_global_cooldown() {
}

void TestMageTalentStatIncrease::test_resource_cost() {
}

void TestMageTalentStatIncrease::test_is_ready_conditions() {
}

void TestMageTalentStatIncrease::test_whether_spell_causes_global_cooldown() {
}
