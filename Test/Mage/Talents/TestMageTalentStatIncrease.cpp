#include "TestMageTalentStatIncrease.h"

#include <cassert>
#include <cmath>

#include "Arcane.h"
#include "Character.h"
#include "CharacterStats.h"
#include "Fire.h"
#include "Frost.h"
#include "Mana.h"
#include "Talent.h"

TestMageTalentStatIncrease::TestMageTalentStatIncrease(EquipmentDb* equipment_db) : TestSpellMage(equipment_db, "MageTalentStatIncrease") {}

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
    test_arcane_mind();
    tear_down();

    set_up();
    test_arcane_instability();
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

void TestMageTalentStatIncrease::test_arcane_mind() {
    auto tree = Arcane(mage);
    Talent* prereq = tree.get_talent_from_name("Arcane Resilience");
    assert(prereq->increment_rank());
    Talent* talent = tree.get_talent_from_name("Arcane Mind");
    const unsigned max_mana_before = static_cast<Mana*>(pchar->get_resource())->get_max_resource();

    assert(talent->increment_rank());
    assert(static_cast<unsigned>(round(max_mana_before * 1.02)) == static_cast<Mana*>(pchar->get_resource())->get_max_resource());

    assert(talent->increment_rank());
    assert(static_cast<unsigned>(round(max_mana_before * 1.04)) == static_cast<Mana*>(pchar->get_resource())->get_max_resource());

    assert(talent->increment_rank());
    assert(static_cast<unsigned>(round(max_mana_before * 1.06)) == static_cast<Mana*>(pchar->get_resource())->get_max_resource());

    assert(talent->increment_rank());
    assert(static_cast<unsigned>(round(max_mana_before * 1.08)) == static_cast<Mana*>(pchar->get_resource())->get_max_resource());

    assert(talent->increment_rank());
    assert(static_cast<unsigned>(round(max_mana_before * 1.10)) == static_cast<Mana*>(pchar->get_resource())->get_max_resource());

    assert(talent->decrement_rank());
    assert(static_cast<unsigned>(round(max_mana_before * 1.08)) == static_cast<Mana*>(pchar->get_resource())->get_max_resource());

    assert(talent->decrement_rank());
    assert(static_cast<unsigned>(round(max_mana_before * 1.06)) == static_cast<Mana*>(pchar->get_resource())->get_max_resource());

    assert(talent->decrement_rank());
    assert(static_cast<unsigned>(round(max_mana_before * 1.04)) == static_cast<Mana*>(pchar->get_resource())->get_max_resource());

    assert(talent->decrement_rank());
    assert(static_cast<unsigned>(round(max_mana_before * 1.02)) == static_cast<Mana*>(pchar->get_resource())->get_max_resource());

    assert(talent->decrement_rank());
    assert(max_mana_before == static_cast<Mana*>(pchar->get_resource())->get_max_resource());
}

void TestMageTalentStatIncrease::test_arcane_instability() {
    auto tree = Arcane(mage);
    assert(tree.get_talent_from_name("Presence of Mind")->increment_rank());
    Talent* talent = tree.get_talent_from_name("Arcane Instability");

    const unsigned spell_crit_before_arcane = pchar->get_stats()->get_spell_crit_chance(MagicSchool::Arcane);
    const unsigned spell_crit_before_fire = pchar->get_stats()->get_spell_crit_chance(MagicSchool::Fire);
    const unsigned spell_crit_before_frost = pchar->get_stats()->get_spell_crit_chance(MagicSchool::Frost);
    const unsigned spell_crit_before_holy = pchar->get_stats()->get_spell_crit_chance(MagicSchool::Holy);
    const unsigned spell_crit_before_nature = pchar->get_stats()->get_spell_crit_chance(MagicSchool::Nature);
    const unsigned spell_crit_before_shadow = pchar->get_stats()->get_spell_crit_chance(MagicSchool::Shadow);

    assert(almost_equal(1.0, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Arcane)));
    assert(almost_equal(1.0, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Fire)));
    assert(almost_equal(1.0, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Frost)));
    assert(almost_equal(1.0, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Holy)));
    assert(almost_equal(1.0, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Nature)));
    assert(almost_equal(1.0, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Shadow)));

    assert(talent->increment_rank());
    assert(almost_equal(1.01, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Arcane)));
    assert(almost_equal(spell_crit_before_arcane + 100, pchar->get_stats()->get_spell_crit_chance(MagicSchool::Arcane)));
    assert(almost_equal(1.01, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Fire)));
    assert(almost_equal(spell_crit_before_fire + 100, pchar->get_stats()->get_spell_crit_chance(MagicSchool::Fire)));
    assert(almost_equal(1.01, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Frost)));
    assert(almost_equal(spell_crit_before_frost + 100, pchar->get_stats()->get_spell_crit_chance(MagicSchool::Frost)));
    assert(almost_equal(1.01, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Holy)));
    assert(almost_equal(spell_crit_before_holy + 100, pchar->get_stats()->get_spell_crit_chance(MagicSchool::Holy)));
    assert(almost_equal(1.01, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Nature)));
    assert(almost_equal(spell_crit_before_nature + 100, pchar->get_stats()->get_spell_crit_chance(MagicSchool::Nature)));
    assert(almost_equal(1.01, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Shadow)));
    assert(almost_equal(spell_crit_before_shadow + 100, pchar->get_stats()->get_spell_crit_chance(MagicSchool::Shadow)));

    assert(talent->increment_rank());
    assert(almost_equal(1.02, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Arcane)));
    assert(almost_equal(spell_crit_before_arcane + 200, pchar->get_stats()->get_spell_crit_chance(MagicSchool::Arcane)));
    assert(almost_equal(1.02, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Fire)));
    assert(almost_equal(spell_crit_before_fire + 200, pchar->get_stats()->get_spell_crit_chance(MagicSchool::Fire)));
    assert(almost_equal(1.02, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Frost)));
    assert(almost_equal(spell_crit_before_frost + 200, pchar->get_stats()->get_spell_crit_chance(MagicSchool::Frost)));
    assert(almost_equal(1.02, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Holy)));
    assert(almost_equal(spell_crit_before_holy + 200, pchar->get_stats()->get_spell_crit_chance(MagicSchool::Holy)));
    assert(almost_equal(1.02, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Nature)));
    assert(almost_equal(spell_crit_before_nature + 200, pchar->get_stats()->get_spell_crit_chance(MagicSchool::Nature)));
    assert(almost_equal(1.02, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Shadow)));
    assert(almost_equal(spell_crit_before_shadow + 200, pchar->get_stats()->get_spell_crit_chance(MagicSchool::Shadow)));

    assert(talent->increment_rank());
    assert(almost_equal(1.03, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Arcane)));
    assert(almost_equal(spell_crit_before_arcane + 300, pchar->get_stats()->get_spell_crit_chance(MagicSchool::Arcane)));
    assert(almost_equal(1.03, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Fire)));
    assert(almost_equal(spell_crit_before_fire + 300, pchar->get_stats()->get_spell_crit_chance(MagicSchool::Fire)));
    assert(almost_equal(1.03, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Frost)));
    assert(almost_equal(spell_crit_before_frost + 300, pchar->get_stats()->get_spell_crit_chance(MagicSchool::Frost)));
    assert(almost_equal(1.03, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Holy)));
    assert(almost_equal(spell_crit_before_holy + 300, pchar->get_stats()->get_spell_crit_chance(MagicSchool::Holy)));
    assert(almost_equal(1.03, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Nature)));
    assert(almost_equal(spell_crit_before_nature + 300, pchar->get_stats()->get_spell_crit_chance(MagicSchool::Nature)));
    assert(almost_equal(1.03, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Shadow)));
    assert(almost_equal(spell_crit_before_shadow + 300, pchar->get_stats()->get_spell_crit_chance(MagicSchool::Shadow)));

    assert(talent->decrement_rank());
    assert(almost_equal(1.02, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Arcane)));
    assert(almost_equal(spell_crit_before_arcane + 200, pchar->get_stats()->get_spell_crit_chance(MagicSchool::Arcane)));
    assert(almost_equal(1.02, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Fire)));
    assert(almost_equal(spell_crit_before_fire + 200, pchar->get_stats()->get_spell_crit_chance(MagicSchool::Fire)));
    assert(almost_equal(1.02, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Frost)));
    assert(almost_equal(spell_crit_before_frost + 200, pchar->get_stats()->get_spell_crit_chance(MagicSchool::Frost)));
    assert(almost_equal(1.02, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Holy)));
    assert(almost_equal(spell_crit_before_holy + 200, pchar->get_stats()->get_spell_crit_chance(MagicSchool::Holy)));
    assert(almost_equal(1.02, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Nature)));
    assert(almost_equal(spell_crit_before_nature + 200, pchar->get_stats()->get_spell_crit_chance(MagicSchool::Nature)));
    assert(almost_equal(1.02, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Shadow)));
    assert(almost_equal(spell_crit_before_shadow + 200, pchar->get_stats()->get_spell_crit_chance(MagicSchool::Shadow)));

    assert(talent->decrement_rank());
    assert(almost_equal(1.01, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Arcane)));
    assert(almost_equal(spell_crit_before_arcane + 100, pchar->get_stats()->get_spell_crit_chance(MagicSchool::Arcane)));
    assert(almost_equal(1.01, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Fire)));
    assert(almost_equal(spell_crit_before_fire + 100, pchar->get_stats()->get_spell_crit_chance(MagicSchool::Fire)));
    assert(almost_equal(1.01, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Frost)));
    assert(almost_equal(spell_crit_before_frost + 100, pchar->get_stats()->get_spell_crit_chance(MagicSchool::Frost)));
    assert(almost_equal(1.01, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Holy)));
    assert(almost_equal(spell_crit_before_holy + 100, pchar->get_stats()->get_spell_crit_chance(MagicSchool::Holy)));
    assert(almost_equal(1.01, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Nature)));
    assert(almost_equal(spell_crit_before_nature + 100, pchar->get_stats()->get_spell_crit_chance(MagicSchool::Nature)));
    assert(almost_equal(1.01, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Shadow)));
    assert(almost_equal(spell_crit_before_shadow + 100, pchar->get_stats()->get_spell_crit_chance(MagicSchool::Shadow)));

    assert(talent->decrement_rank());
    assert(almost_equal(1.0, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Arcane)));
    assert(almost_equal(spell_crit_before_arcane, pchar->get_stats()->get_spell_crit_chance(MagicSchool::Arcane)));
    assert(almost_equal(1.0, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Fire)));
    assert(almost_equal(spell_crit_before_fire, pchar->get_stats()->get_spell_crit_chance(MagicSchool::Fire)));
    assert(almost_equal(1.0, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Frost)));
    assert(almost_equal(spell_crit_before_frost, pchar->get_stats()->get_spell_crit_chance(MagicSchool::Frost)));
    assert(almost_equal(1.0, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Holy)));
    assert(almost_equal(spell_crit_before_holy, pchar->get_stats()->get_spell_crit_chance(MagicSchool::Holy)));
    assert(almost_equal(1.0, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Nature)));
    assert(almost_equal(spell_crit_before_nature, pchar->get_stats()->get_spell_crit_chance(MagicSchool::Nature)));
    assert(almost_equal(1.0, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Shadow)));
    assert(almost_equal(spell_crit_before_shadow, pchar->get_stats()->get_spell_crit_chance(MagicSchool::Shadow)));
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

void TestMageTalentStatIncrease::test_name_correct() {}

void TestMageTalentStatIncrease::test_spell_cooldown() {}

void TestMageTalentStatIncrease::test_how_spell_observes_global_cooldown() {}

void TestMageTalentStatIncrease::test_resource_cost() {}

void TestMageTalentStatIncrease::test_is_ready_conditions() {}

void TestMageTalentStatIncrease::test_whether_spell_causes_global_cooldown() {}
