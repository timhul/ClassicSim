#include "TestBloodthirst.h"

#include "Bloodthirst.h"
#include "Queue.h"

TestBloodthirst::TestBloodthirst(EquipmentDb *equipment_db) :
    TestSpellWarrior(equipment_db, "Bloodthirst")
{}

void TestBloodthirst::test_all() {
    run_mandatory_tests();

    set_up();
    test_hit_dmg();
    tear_down();

    set_up();
    test_crit_dmg_0_of_2_impale();
    tear_down();

    set_up();
    test_crit_dmg_1_of_2_impale();
    tear_down();

    set_up();
    test_crit_dmg_2_of_2_impale();
    tear_down();

    set_up();
    test_dodge_applies_overpower_buff();
    tear_down();
}

Bloodthirst* TestBloodthirst::bloodthirst() {
    return dynamic_cast<WarriorSpells*>(warrior->get_spells())->get_bloodthirst();
}

void TestBloodthirst::test_name_correct() {
    assert(bloodthirst()->get_name() == "Bloodthirst");
}

void TestBloodthirst::test_spell_cooldown() {
    given_a_guaranteed_melee_ability_hit();
    assert(QString::number(bloodthirst()->get_base_cooldown(), 'f', 3) == "6.000");

    when_bloodthirst_is_performed();

    then_next_event_is("PlayerAction", "1.500");
    then_next_event_is("PlayerAction", "6.000");
}

void TestBloodthirst::test_incurs_global_cooldown() {
    assert(warrior->action_ready());

    when_bloodthirst_is_performed();

    assert(!warrior->action_ready());
}

void TestBloodthirst::test_obeys_global_cooldown() {
    bloodthirst()->enable();
    given_warrior_has_rage(100);
    assert(bloodthirst()->get_spell_status() == SpellStatus::Available);

    given_warrior_is_on_gcd();

    assert(bloodthirst()->get_spell_status() == SpellStatus::OnGCD);
    assert(almost_equal(bloodthirst()->get_cooldown_remaining(), 0));
}

void TestBloodthirst::test_is_ready_conditions() {
    given_warrior_has_rage(100);
    assert(bloodthirst()->get_spell_status() == SpellStatus::NotEnabled);

    bloodthirst()->enable();
    assert(bloodthirst()->get_spell_status() == SpellStatus::Available);
}

void TestBloodthirst::test_resource_cost() {
    given_a_guaranteed_melee_ability_hit();
    given_warrior_has_rage(30);

    when_bloodthirst_is_performed();

    then_warrior_has_rage(0);
}

void TestBloodthirst::test_stance_cooldown() {
    given_warrior_has_rage(100);
    assert(bloodthirst()->get_spell_status() == SpellStatus::Available);

    when_switching_to_berserker_stance();
    given_warrior_has_rage(100);
    assert(warrior->on_stance_cooldown() == true);
    assert(bloodthirst()->get_spell_status() == SpellStatus::SpellSpecific);

    given_engine_priority_pushed_forward(0.99);
    assert(warrior->on_stance_cooldown() == true);
    assert(bloodthirst()->get_spell_status() == SpellStatus::SpellSpecific);

    given_engine_priority_pushed_forward(0.02);
    assert(warrior->on_stance_cooldown() == false);
    assert(bloodthirst()->get_spell_status() == SpellStatus::Available);
}

void TestBloodthirst::test_hit_dmg() {
    given_target_has_0_armor();
    given_a_guaranteed_melee_ability_hit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_2_of_2_impale();

    when_bloodthirst_is_performed();

    // [Damage] = melee_ap * 0.45
    // [450] = 1000 * 0.45
    then_damage_dealt_is(450);
}

void TestBloodthirst::test_crit_dmg_0_of_2_impale() {
    given_target_has_0_armor();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_0_of_2_impale();

    when_bloodthirst_is_performed();

    // [Damage] = melee_ap * 0.45 * crit_dmg_modifier
    // [900] = 1000 * 0.45 * 2.0
    then_damage_dealt_is(900);
}

void TestBloodthirst::test_crit_dmg_1_of_2_impale() {
    given_target_has_0_armor();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_1_of_2_impale();

    when_bloodthirst_is_performed();

    // [Damage] = melee_ap * 0.45 * crit_dmg_modifier
    // [945] = 1000 * 0.45 * 2.1
    then_damage_dealt_is(945);
}

void TestBloodthirst::test_crit_dmg_2_of_2_impale() {
    given_target_has_0_armor();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_2_of_2_impale();

    when_bloodthirst_is_performed();

    // [Damage] = melee_ap * 0.45 * crit_dmg_modifier
    // [990] = 1000 * 0.45 * 2.2
    then_damage_dealt_is(990);
}

void TestBloodthirst::test_dodge_applies_overpower_buff() {
    given_a_guaranteed_melee_ability_dodge();

    when_bloodthirst_is_performed();

    then_overpower_is_active();
}

void TestBloodthirst::when_bloodthirst_is_performed() {
    bloodthirst()->perform();
}
