#include "TestBearForm.h"

#include <cassert>

#include "BearForm.h"
#include "Buff.h"
#include "CharacterStats.h"
#include "Druid.h"
#include "DruidSpells.h"
#include "EnchantProc.h"
#include "Equipment.h"
#include "Event.h"
#include "RaidControl.h"
#include "Weapon.h"

TestBearForm::TestBearForm(EquipmentDb* equipment_db) : TestSpellDruid(equipment_db, "Bear Form") {}

void TestBearForm::test_all() {
    run_mandatory_tests();

    set_up();
    test_resource_cost_with_3_of_3_natural_shapeshifter();
    tear_down();

    set_up();
    test_paws_equipped_upon_entering_bear_form();
    tear_down();

    set_up();
    test_proc_enchants_on_weapon_disabled_in_bear_form();
    tear_down();

    set_up();
    test_attack_speed_in_and_out_of_bear_form();
    tear_down();

    set_up();
    test_hit_dmg();
    tear_down();

    set_up();
    test_hit_dmg_0_of_5_feral_instinct();
    tear_down();

    set_up();
    test_hit_dmg_1_of_5_feral_instinct();
    tear_down();

    set_up();
    test_hit_dmg_2_of_5_feral_instinct();
    tear_down();

    set_up();
    test_hit_dmg_3_of_5_feral_instinct();
    tear_down();

    set_up();
    test_hit_dmg_4_of_5_feral_instinct();
    tear_down();

    set_up();
    test_hit_dmg_5_of_5_feral_instinct();
    tear_down();

    set_up();
    test_crit_dmg();
    tear_down();

    set_up();
    test_glancing_dmg();
    tear_down();

    set_up();
    test_leader_of_the_pack_gives_crit_to_party_members();
    tear_down();

    set_up();
    test_0_of_5_furor_gives_0_rage_on_entering_bear_form();
    tear_down();

    set_up(false);
    test_5_of_5_furor_gives_10_rage_on_entering_bear_form();
    tear_down();
}

void TestBearForm::test_name_correct() {
    assert(bear_form()->get_name() == "Bear Form");
}

void TestBearForm::test_spell_cooldown() {
    assert(almost_equal(0.0, bear_form()->get_base_cooldown()));
}

void TestBearForm::test_whether_spell_causes_global_cooldown() {
    assert(druid->action_ready());

    when_bear_form_is_performed();

    assert(!druid->action_ready());
}

void TestBearForm::test_how_spell_observes_global_cooldown() {}

void TestBearForm::test_is_ready_conditions() {
    assert(bear_form()->get_spell_status() == SpellStatus::Available);
}

void TestBearForm::test_resource_cost() {
    given_druid_has_mana(101);

    when_bear_form_is_performed();

    then_druid_has_mana(1);
}

void TestBearForm::test_resource_cost_with_3_of_3_natural_shapeshifter() {
    given_balance_talent_rank("Natural Shapeshifter", 3);
    given_druid_has_mana(71);

    when_bear_form_is_performed();

    then_druid_has_mana(1);
}

void TestBearForm::test_paws_equipped_upon_entering_bear_form() {
    given_staff_equipped(druid);

    when_bear_form_is_performed();

    assert(pchar->get_equipment()->get_mainhand() != nullptr);
    assert(pchar->get_equipment()->get_mainhand()->name == "Paws level 60");
}

void TestBearForm::test_proc_enchants_on_weapon_disabled_in_bear_form() {
    given_staff_equipped(druid);
    Weapon* mh = pchar->get_equipment()->get_mainhand();
    mh->apply_enchant(EnchantName::Name::Crusader, druid, WeaponSlots::MAINHAND);
    mh->apply_temporary_enchant(EnchantName::Name::ShadowOil, druid, WeaponSlots::MAINHAND);
    assert(true == static_cast<EnchantProc*>(mh->get_enchant())->proc_enabled());
    assert(true == static_cast<EnchantProc*>(mh->get_enchant())->proc_enabled());

    when_bear_form_is_performed();
    assert(false == static_cast<EnchantProc*>(mh->get_enchant())->proc_enabled());
    assert(false == static_cast<EnchantProc*>(mh->get_enchant())->proc_enabled());

    druid->cancel_form();
    assert(true == static_cast<EnchantProc*>(mh->get_enchant())->proc_enabled());
    assert(true == static_cast<EnchantProc*>(mh->get_enchant())->proc_enabled());
}

void TestBearForm::test_attack_speed_in_and_out_of_bear_form() {
    given_event_is_ignored(EventType::PlayerAction);
    given_event_is_ignored(EventType::DotTick);
    given_in_melee_attack_mode();
    given_staff_equipped(druid);
    pchar->get_spells()->start_attack();

    then_next_event_is(EventType::MainhandMeleeHit, "0.000", RUN_EVENT);
    when_bear_form_is_performed();
    then_next_event_is(EventType::MainhandMeleeHit, "3.800", RUN_EVENT);
    then_next_event_is(EventType::MainhandMeleeHit, "6.300", RUN_EVENT);
    then_next_event_is(EventType::MainhandMeleeHit, "8.800", RUN_EVENT);
    druid->cancel_form();
    then_next_event_is(EventType::MainhandMeleeHit, "11.300", RUN_EVENT);
    then_next_event_is(EventType::MainhandMeleeHit, "15.100", RUN_EVENT);
}

void TestBearForm::test_hit_dmg() {
    given_target_has_0_armor();
    given_in_melee_attack_mode();
    when_bear_form_is_performed();
    given_1000_melee_ap();
    given_a_guaranteed_white_hit();
    pchar->get_spells()->start_attack();

    then_next_event_is(EventType::MainhandMeleeHit, "0.000", RUN_EVENT);

    // [Damage] = [min - max] + AP / 14
    // [306 - 367] = 2.5 * ([60 * 0.85 - 60 * 1.25] + 1000 / 14)
    then_damage_dealt_is_in_range(306, 367);
}

void TestBearForm::test_hit_dmg_0_of_5_feral_instinct() {
    given_target_has_0_armor();
    given_in_melee_attack_mode();
    when_bear_form_is_performed();
    given_1000_melee_ap();
    given_a_guaranteed_white_hit();
    pchar->get_spells()->start_attack();

    then_next_event_is(EventType::MainhandMeleeHit, "0.000", RUN_EVENT);

    // [Damage] = [min - max] + AP / 14
    // [306 - 367] = 2.5 * ([60 * 0.85 - 60 * 1.25] + 1000 / 14)
    then_damage_dealt_is_in_range(306, 367);

    then_threat_dealt_is_in_range(306 * 1.3, 367 * 1.3 + 1);
}

void TestBearForm::test_hit_dmg_1_of_5_feral_instinct() {
    given_feral_talent_rank("Feral Instinct", 1);
    given_target_has_0_armor();
    given_in_melee_attack_mode();
    when_bear_form_is_performed();
    given_1000_melee_ap();
    given_a_guaranteed_white_hit();
    pchar->get_spells()->start_attack();

    then_next_event_is(EventType::MainhandMeleeHit, "0.000", RUN_EVENT);

    // [Damage] = [min - max] + AP / 14
    // [306 - 367] = 2.5 * ([60 * 0.85 - 60 * 1.25] + 1000 / 14)
    then_damage_dealt_is_in_range(306, 367);

    then_threat_dealt_is_in_range(306 * (1.3 + 0.03), 367 * (1.3 + 0.03) + 1);
}

void TestBearForm::test_hit_dmg_2_of_5_feral_instinct() {
    given_feral_talent_rank("Feral Instinct", 2);
    given_target_has_0_armor();
    given_in_melee_attack_mode();
    when_bear_form_is_performed();
    given_1000_melee_ap();
    given_a_guaranteed_white_hit();
    pchar->get_spells()->start_attack();

    then_next_event_is(EventType::MainhandMeleeHit, "0.000", RUN_EVENT);

    // [Damage] = [min - max] + AP / 14
    // [306 - 367] = 2.5 * ([60 * 0.85 - 60 * 1.25] + 1000 / 14)
    then_damage_dealt_is_in_range(306, 367);

    then_threat_dealt_is_in_range(306 * (1.3 + 0.06), 367 * (1.3 + 0.06) + 1);
}

void TestBearForm::test_hit_dmg_3_of_5_feral_instinct() {
    given_feral_talent_rank("Feral Instinct", 3);
    given_target_has_0_armor();
    given_in_melee_attack_mode();
    when_bear_form_is_performed();
    given_1000_melee_ap();
    given_a_guaranteed_white_hit();
    pchar->get_spells()->start_attack();

    then_next_event_is(EventType::MainhandMeleeHit, "0.000", RUN_EVENT);

    // [Damage] = [min - max] + AP / 14
    // [306 - 367] = 2.5 * ([60 * 0.85 - 60 * 1.25] + 1000 / 14)
    then_damage_dealt_is_in_range(306, 367);

    then_threat_dealt_is_in_range(306 * (1.3 + 0.09), 367 * (1.3 + 0.09) + 1);
}

void TestBearForm::test_hit_dmg_4_of_5_feral_instinct() {
    given_feral_talent_rank("Feral Instinct", 4);
    given_target_has_0_armor();
    given_in_melee_attack_mode();
    when_bear_form_is_performed();
    given_1000_melee_ap();
    given_a_guaranteed_white_hit();
    pchar->get_spells()->start_attack();

    then_next_event_is(EventType::MainhandMeleeHit, "0.000", RUN_EVENT);

    // [Damage] = [min - max] + AP / 14
    // [306 - 367] = 2.5 * ([60 * 0.85 - 60 * 1.25] + 1000 / 14)
    then_damage_dealt_is_in_range(306, 367);

    then_threat_dealt_is_in_range(306 * (1.3 + 0.12), 367 * (1.3 + 0.12) + 1);
}

void TestBearForm::test_hit_dmg_5_of_5_feral_instinct() {
    given_feral_talent_rank("Feral Instinct", 5);
    given_target_has_0_armor();
    given_in_melee_attack_mode();
    when_bear_form_is_performed();
    given_1000_melee_ap();
    given_a_guaranteed_white_hit();
    pchar->get_spells()->start_attack();

    then_next_event_is(EventType::MainhandMeleeHit, "0.000", RUN_EVENT);

    // [Damage] = [min - max] + AP / 14
    // [306 - 367] = 2.5 * ([60 * 0.85 - 60 * 1.25] + 1000 / 14)
    then_damage_dealt_is_in_range(306, 367);

    then_threat_dealt_is_in_range(306 * (1.3 + 0.15), 367 * (1.3 + 0.15) + 1);
}

void TestBearForm::test_crit_dmg() {
    given_target_has_0_armor();
    given_in_melee_attack_mode();
    when_bear_form_is_performed();
    given_1000_melee_ap();
    given_a_guaranteed_white_crit();
    pchar->get_spells()->start_attack();

    then_next_event_is(EventType::MainhandMeleeHit, "0.000", RUN_EVENT);

    // [Damage] = ([min - max] + AP / 14) * crit_dmg_modifier
    // [613 - 733] = 2.5 * ([60 * 0.85 - 60 * 1.25] + 1000 / 14) * 2.0
    then_damage_dealt_is_in_range(613, 733);
}

void TestBearForm::test_glancing_dmg() {
    given_target_has_0_armor();
    given_in_melee_attack_mode();
    when_bear_form_is_performed();
    given_1000_melee_ap();
    given_a_guaranteed_white_glancing_blow();
    pchar->get_spells()->start_attack();

    then_next_event_is(EventType::MainhandMeleeHit, "0.000", RUN_EVENT);

    // [Damage] = ([min - max] + AP / 14) * glancing_dmg_modifier
    // [168 - 275] = 2.5 * ([60 * 0.85 - 60 * 1.25] + 1000 / 14) * [0.55 - 0.75]
    then_damage_dealt_is_in_range(168, 275);
}

void TestBearForm::test_leader_of_the_pack_gives_crit_to_party_members() {
    Druid* druid_2 = new Druid(race, equipment_db, sim_settings, raid_control, 0, 1);
    given_feral_talent_rank("Leader of the Pack", 1);

    const unsigned self_melee_crit_before = pchar->get_stats()->get_mh_crit_chance();
    const unsigned druid_2_melee_crit_before = druid_2->get_stats()->get_mh_crit_chance();

    when_bear_form_is_performed();

    const unsigned aura_suppression = 180;
    assert(self_melee_crit_before + 300 - aura_suppression == pchar->get_stats()->get_mh_crit_chance());
    assert(druid_2_melee_crit_before + 300 - aura_suppression == druid_2->get_stats()->get_mh_crit_chance());

    given_engine_priority_pushed_forward(1.01);
    druid->cancel_form();
    assert(druid->get_current_form() == DruidForm::Caster);

    assert(self_melee_crit_before == pchar->get_stats()->get_mh_crit_chance());
    assert(druid_2_melee_crit_before == druid_2->get_stats()->get_mh_crit_chance());

    delete druid_2;
}

void TestBearForm::test_0_of_5_furor_gives_0_rage_on_entering_bear_form() {
    given_druid_has_energy(0);

    when_bear_form_is_performed();

    then_druid_has_energy(0);
}

void TestBearForm::test_5_of_5_furor_gives_10_rage_on_entering_bear_form() {
    given_restoration_talent_rank("Furor", 5);
    given_druid_has_energy(0);
    pchar->prepare_set_of_combat_iterations();

    when_bear_form_is_performed();

    then_druid_has_rage(10);
}

void TestBearForm::when_bear_form_is_performed() {
    bear_form()->perform();
}
