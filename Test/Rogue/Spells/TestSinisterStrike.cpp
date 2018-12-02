#include "TestSinisterStrike.h"

#include "Equipment.h"
#include "Queue.h"
#include "RogueSpells.h"
#include "SinisterStrike.h"

TestSinisterStrike::TestSinisterStrike(EquipmentDb *equipment_db) :
    TestSpellRogue(equipment_db, "Sinister Strike")
{}

void TestSinisterStrike::test_all() {
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
}

SinisterStrike *TestSinisterStrike::sinister_strike() {
    return dynamic_cast<RogueSpells*>(rogue->get_spells())->get_sinister_strike();
}

void TestSinisterStrike::test_name_correct() {
    assert(sinister_strike()->get_name() == "Sinister Strike");
}

void TestSinisterStrike::test_spell_cooldown() {
    assert(QString::number(sinister_strike()->get_base_cooldown(), 'f', 3) == "0.000");
}

void TestSinisterStrike::test_incurs_global_cooldown() {
    when_sinister_strike_is_performed();

    then_next_event_is("CooldownReady", QString::number(rogue->global_cooldown(), 'f', 3));
}

void TestSinisterStrike::test_obeys_global_cooldown() {
    given_rogue_has_energy(100);
    assert(sinister_strike()->is_available());

    given_rogue_is_on_gcd();

    given_rogue_has_energy(100);
    assert(!sinister_strike()->is_available());
}

void TestSinisterStrike::test_is_ready_conditions() {
}

void TestSinisterStrike::test_resource_cost() {
    given_1h_sword_equipped_in_mainhand(pchar);
    given_a_guaranteed_melee_ability_hit();

    given_rogue_has_energy(45);
    when_sinister_strike_is_performed();
    then_rogue_has_energy(0);

    given_engine_priority_at(1.01);

    given_rogue_has_energy(55);
    when_sinister_strike_is_performed();
    then_rogue_has_energy(10);
}

void TestSinisterStrike::test_combo_points() {
    given_1h_sword_equipped_in_mainhand(pchar);
    given_a_guaranteed_melee_ability_hit();
    then_rogue_has_combo_points(0);

    when_sinister_strike_is_performed();

    then_rogue_has_combo_points(1);
}

void TestSinisterStrike::test_stealth() {
    given_1h_sword_equipped_in_mainhand(pchar);
    given_rogue_not_in_stealth();
    assert(sinister_strike()->is_available());
    given_rogue_in_stealth();
    assert(sinister_strike()->is_available());

    when_sinister_strike_is_performed();

    assert(!rogue->is_stealthed());
}

void TestSinisterStrike::test_hit_dmg() {
    given_target_has_0_armor();
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_hit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();

    when_sinister_strike_is_performed();

    // [Damage] = base_dmg + normalized_wpn_speed * AP / 14 + flat_damage_bonus
    // [339] = 100 + 2.4 * 1000 / 14 + 68
    then_damage_dealt_is(339);
}

void TestSinisterStrike::test_crit_dmg() {
    given_target_has_0_armor();
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();

    when_sinister_strike_is_performed();

    // [Damage] = (base_dmg + normalized_wpn_speed * AP / 14 + flat_damage_bonus) * crit_dmg_modifier
    // [579] = (100 + 2.4 * 1000 / 14 + 68) * 2.0
    then_damage_dealt_is(679);
}

void TestSinisterStrike::when_sinister_strike_is_performed() {
    if (pchar->get_equipment()->get_mainhand() == nullptr)
        given_1h_sword_equipped_in_mainhand(pchar);

    sinister_strike()->perform();
}
