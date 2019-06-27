#include "TestStormstrike.h"

#include "CharacterStats.h"
#include "Queue.h"
#include "Shaman.h"
#include "Stormstrike.h"

TestStormstrike::TestStormstrike(EquipmentDb *equipment_db) :
    TestSpellShaman(equipment_db, "Stormstrike")
{}

void TestStormstrike::test_all() {
    run_mandatory_tests(false);

    set_up();
    test_hit_dmg();
    tear_down();

    set_up();
    test_crit_dmg();
    tear_down();

    set_up();
    test_stormstrikes_applies_nature_damage_debuff();
    tear_down();
}

void TestStormstrike::test_name_correct() {
    assert(stormstrike()->get_name() == "Stormstrike");
}

void TestStormstrike::test_spell_cooldown() {
    given_stormstrike_enabled();
    ignored_events = {"BuffRemoval", "ResourceGain"};
    given_a_guaranteed_melee_ability_hit();
    assert(QString::number(stormstrike()->get_base_cooldown(), 'f', 3) == "12.000");

    when_stormstrike_is_performed();

    then_next_event_is(EventType::PlayerAction, "1.500");
    then_next_event_is(EventType::PlayerAction, "12.000");
}

void TestStormstrike::test_whether_spell_causes_global_cooldown() {
    given_stormstrike_enabled();
    assert(shaman->action_ready());

    when_stormstrike_is_performed();

    assert(!shaman->action_ready());
}

void TestStormstrike::test_how_spell_observes_global_cooldown() {

}

void TestStormstrike::test_is_ready_conditions() {
    assert(stormstrike()->get_spell_status() == SpellStatus::NotEnabled);

    given_stormstrike_enabled();
    assert(stormstrike()->get_spell_status() == SpellStatus::Available);
}

void TestStormstrike::test_resource_cost() {
    given_stormstrike_enabled();
    given_a_guaranteed_melee_ability_hit();
    given_shaman_has_mana(320);

    when_stormstrike_is_performed();

    then_shaman_has_mana(1);
}

void TestStormstrike::test_hit_dmg() {
    given_stormstrike_enabled();
    given_target_has_0_armor();
    given_a_twohand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_hit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();

    when_stormstrike_is_performed();

    // [Damage] = base_dmg + (normalized_wpn_speed * AP / 14)
    // [336] = 100 + (3.3 * 1000 / 14)
    then_damage_dealt_is(336);
}

void TestStormstrike::test_crit_dmg() {
    given_stormstrike_enabled();
    given_target_has_0_armor();
    given_a_twohand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();

    when_stormstrike_is_performed();

    // [Damage] = (base_dmg + (normalized_wpn_speed * AP / 14)) * crit_dmg_modifier
    // [671] = (100 + (3.3 * 1000 / 14)) * 2.0
    then_damage_dealt_is(671);
}

void TestStormstrike::test_stormstrikes_applies_nature_damage_debuff() {
    given_stormstrike_enabled();
    given_a_guaranteed_melee_ability_hit();
    assert(almost_equal(1.0, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Arcane)));
    assert(almost_equal(1.0, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Fire)));
    assert(almost_equal(1.0, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Frost)));
    assert(almost_equal(1.0, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Holy)));
    assert(almost_equal(1.0, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Nature)));
    assert(almost_equal(1.0, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Physical)));

    when_stormstrike_is_performed();

    assert(almost_equal(1.0, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Arcane)));
    assert(almost_equal(1.0, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Fire)));
    assert(almost_equal(1.0, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Frost)));
    assert(almost_equal(1.0, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Holy)));
    assert(almost_equal(1.0, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Physical)));

    // Two charges, get_spell_dmg_mod uses a charge each time.
    assert(almost_equal(1.2, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Nature)));
    assert(almost_equal(1.2, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Nature)));
    assert(almost_equal(1.0, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Nature)));
}
