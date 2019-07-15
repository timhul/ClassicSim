#include "TestArcaneMissiles.h"

#include "ArcaneMissiles.h"
#include "Mage.h"

TestArcaneMissiles::TestArcaneMissiles(EquipmentDb* equipment_db) :
    TestSpellMage(equipment_db, "Arcane Missiles")
{}

void TestArcaneMissiles::test_all() {
    run_mandatory_tests();

    set_up();
    test_hit_dmg();
    tear_down();

    set_up();
    test_crit_dmg();
    tear_down();

    set_up(false);
    test_hit_dmg_arcane_power();
    tear_down();
}

void TestArcaneMissiles::test_name_correct() {
    assert(arcane_missiles()->get_name() == "Arcane Missiles");
}

void TestArcaneMissiles::test_spell_cooldown() {
    assert(almost_equal(0.0, arcane_missiles()->get_base_cooldown()));
}

void TestArcaneMissiles::test_whether_spell_causes_global_cooldown() {
    assert(mage->action_ready());

    when_arcane_missiles_is_performed();

    assert(!mage->action_ready());
}

void TestArcaneMissiles::test_how_spell_observes_global_cooldown() {

}

void TestArcaneMissiles::test_is_ready_conditions() {
    assert(arcane_missiles()->get_spell_status() == SpellStatus::Available);
}

void TestArcaneMissiles::test_resource_cost() {
    given_a_guaranteed_magic_hit(MagicSchool::Arcane);
    given_mage_has_mana(656);

    when_arcane_missiles_is_performed();
    when_running_queued_events_until(5.01);

    then_mage_has_mana(1);
}

void TestArcaneMissiles::test_hit_dmg() {
    given_a_guaranteed_magic_hit(MagicSchool::Arcane);
    given_1000_spell_power();
    given_no_previous_damage_dealt();

    when_arcane_missiles_is_performed();
    when_running_queued_events_until(5.01);

    // [Damage] = (damage_per_missile + spell_power * spell_coefficient) * missiles
    // 2150 = (230 + 1000 * 0.2) * 5
    then_damage_dealt_is(2150);
}

void TestArcaneMissiles::test_crit_dmg() {
    given_a_guaranteed_magic_crit(MagicSchool::Arcane);
    given_1000_spell_power();
    given_no_previous_damage_dealt();

    when_arcane_missiles_is_performed();
    when_running_queued_events_until(5.01);

    // [Damage] = (damage_per_missile + spell_power * spell_coefficient) * spell_crit_dmg_modifier * missiles
    // 3225 = (230 + 1000 * 0.2) * 1.5 * 5
    then_damage_dealt_is(3225);
}

void TestArcaneMissiles::test_hit_dmg_arcane_power() {
    given_mage_has_mana(853);
    given_a_guaranteed_magic_hit(MagicSchool::Arcane);
    given_1000_spell_power();
    given_no_previous_damage_dealt();
    given_arcane_power_is_active();
    given_engine_priority_pushed_forward(1.5);

    when_arcane_missiles_is_performed();
    when_running_queued_events_until(6.51);

    // [Damage] = round((damage_per_missile + spell_power * spell_coefficient) * arcane_power * arcane_instability) * missiles
    // 2880 = round((230 + 1000 * 0.2) * 1.3 * 1.03) * 5
    then_damage_dealt_is(2880);
    then_mage_has_mana(1);
}

void TestArcaneMissiles::when_arcane_missiles_is_performed() {
    arcane_missiles()->perform();
}
