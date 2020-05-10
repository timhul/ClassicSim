#include "TestCatForm.h"

#include <cassert>

#include "Buff.h"
#include "CatForm.h"
#include "CharacterStats.h"
#include "Druid.h"
#include "DruidSpells.h"
#include "EnchantProc.h"
#include "Equipment.h"
#include "Event.h"
#include "RaidControl.h"
#include "Weapon.h"

TestCatForm::TestCatForm(EquipmentDb* equipment_db) : TestSpellDruid(equipment_db, "Cat Form") {}

void TestCatForm::test_all() {
    run_mandatory_tests();

    set_up();
    test_resource_cost_with_3_of_3_natural_shapeshifter();
    tear_down();

    set_up();
    test_claws_equipped_upon_entering_cat_form();
    tear_down();

    set_up();
    test_proc_enchants_on_weapon_disabled_in_cat_form();
    tear_down();

    set_up();
    test_attack_speed_in_and_out_of_cat_form();
    tear_down();

    set_up();
    test_how_spell_observes_global_cooldown();
    tear_down();

    set_up();
    test_hit_dmg();
    tear_down();

    set_up();
    test_crit_dmg();
    tear_down();

    set_up();
    test_glancing_dmg();
    tear_down();

    set_up(false);
    test_leader_of_the_pack_gives_crit_to_party_members();
    tear_down();

    set_up();
    test_0_of_5_furor_gives_0_energy_on_entering_cat_form();
    tear_down();

    set_up(false);
    test_5_of_5_furor_gives_40_energy_on_entering_cat_form();
    tear_down();
}

void TestCatForm::test_name_correct() {
    assert(cat_form()->get_name() == "Cat Form");
}

void TestCatForm::test_spell_cooldown() {
    assert(almost_equal(0.0, cat_form()->get_base_cooldown()));
}

void TestCatForm::test_whether_spell_causes_global_cooldown() {
    assert(druid->action_ready());

    when_cat_form_is_performed();

    assert(!druid->action_ready());
}

void TestCatForm::test_how_spell_observes_global_cooldown() {
    assert(druid->action_ready());

    when_cat_form_is_performed();
    assert(!druid->action_ready());

    druid->cancel_form();
    assert(!druid->action_ready());

    when_cat_form_is_performed();
    assert(!druid->action_ready());
    assert(druid->get_current_form() == DruidForm::Caster);
}

void TestCatForm::test_is_ready_conditions() {
    assert(cat_form()->get_spell_status() == SpellStatus::Available);
}

void TestCatForm::test_resource_cost() {
    given_druid_has_mana(101);

    when_cat_form_is_performed();

    then_druid_has_mana(1);
}

void TestCatForm::test_resource_cost_with_3_of_3_natural_shapeshifter() {
    given_balance_talent_rank("Natural Shapeshifter", 3);
    given_druid_has_mana(71);

    when_cat_form_is_performed();

    then_druid_has_mana(1);
}

void TestCatForm::test_claws_equipped_upon_entering_cat_form() {
    given_staff_equipped(druid);

    when_cat_form_is_performed();

    assert(pchar->get_equipment()->get_mainhand() != nullptr);
    assert(pchar->get_equipment()->get_mainhand()->name == "Claw level 60");
}

void TestCatForm::test_proc_enchants_on_weapon_disabled_in_cat_form() {
    given_staff_equipped(druid);
    Weapon* mh = pchar->get_equipment()->get_mainhand();
    mh->apply_enchant(EnchantName::Name::Crusader, druid, WeaponSlots::MAINHAND);
    mh->apply_temporary_enchant(EnchantName::Name::ShadowOil, druid, WeaponSlots::MAINHAND);
    assert(true == static_cast<EnchantProc*>(mh->get_enchant())->proc_enabled());
    assert(true == static_cast<EnchantProc*>(mh->get_enchant())->proc_enabled());

    when_cat_form_is_performed();
    assert(false == static_cast<EnchantProc*>(mh->get_enchant())->proc_enabled());
    assert(false == static_cast<EnchantProc*>(mh->get_enchant())->proc_enabled());

    druid->cancel_form();
    assert(true == static_cast<EnchantProc*>(mh->get_enchant())->proc_enabled());
    assert(true == static_cast<EnchantProc*>(mh->get_enchant())->proc_enabled());
}

void TestCatForm::test_attack_speed_in_and_out_of_cat_form() {
    given_event_is_ignored(EventType::PlayerAction);
    given_event_is_ignored(EventType::DotTick);
    given_in_melee_attack_mode();
    given_staff_equipped(druid);
    pchar->get_spells()->start_attack();

    then_next_event_is(EventType::MainhandMeleeHit, "0.000", RUN_EVENT);
    when_cat_form_is_performed();
    then_next_event_is(EventType::MainhandMeleeHit, "3.800", RUN_EVENT);
    then_next_event_is(EventType::MainhandMeleeHit, "4.800", RUN_EVENT);
    then_next_event_is(EventType::MainhandMeleeHit, "5.800", RUN_EVENT);
    druid->cancel_form();
    then_next_event_is(EventType::MainhandMeleeHit, "6.800", RUN_EVENT);
    then_next_event_is(EventType::MainhandMeleeHit, "10.600", RUN_EVENT);
}

void TestCatForm::test_hit_dmg() {
    given_target_has_0_armor();
    given_in_melee_attack_mode();
    when_cat_form_is_performed();
    given_1000_melee_ap();
    given_a_guaranteed_white_hit();
    pchar->get_spells()->start_attack();

    then_next_event_is(EventType::MainhandMeleeHit, "0.000", RUN_EVENT);

    // [Damage] = [min - max] + AP / 14
    // [122 - 146] = [60 * 0.85 - 60 * 1.25] + 1000 / 14
    then_damage_dealt_is_in_range(122, 146);
}

void TestCatForm::test_crit_dmg() {
    given_target_has_0_armor();
    given_in_melee_attack_mode();
    when_cat_form_is_performed();
    given_1000_melee_ap();
    given_a_guaranteed_white_crit();
    pchar->get_spells()->start_attack();

    then_next_event_is(EventType::MainhandMeleeHit, "0.000", RUN_EVENT);

    // [Damage] = ([min - max] + AP / 14) * crit_dmg_modifier
    // [245 - 293] = ([60 * 0.85 - 60 * 1.25] + 1000 / 14) * 2.0
    then_damage_dealt_is_in_range(245, 293);
}

void TestCatForm::test_glancing_dmg() {
    given_target_has_0_armor();
    given_in_melee_attack_mode();
    when_cat_form_is_performed();
    given_1000_melee_ap();
    given_a_guaranteed_white_glancing_blow();
    pchar->get_spells()->start_attack();

    then_next_event_is(EventType::MainhandMeleeHit, "0.000", RUN_EVENT);

    // [Damage] = ([min - max] + AP / 14) * glancing_dmg_modifier
    // [67 - 110] = ([60 * 0.85 - 60 * 1.25] + 1000 / 14) * [0.55 - 0.75]
    then_damage_dealt_is_in_range(67, 110);
}

void TestCatForm::test_leader_of_the_pack_gives_crit_to_party_members() {
    Druid* druid_2 = new Druid(race, equipment_db, sim_settings, raid_control, 0, 1);
    given_feral_talent_rank("Leader of the Pack", 1);
    pchar->prepare_set_of_combat_iterations();
    raid_control->prepare_set_of_combat_iterations();

    const unsigned self_melee_crit_before = pchar->get_stats()->get_mh_crit_chance();
    const unsigned druid_2_melee_crit_before = druid_2->get_stats()->get_mh_crit_chance();

    when_cat_form_is_performed();

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

void TestCatForm::test_0_of_5_furor_gives_0_energy_on_entering_cat_form() {
    given_druid_has_energy(0);

    when_cat_form_is_performed();

    then_druid_has_energy(0);
}

void TestCatForm::test_5_of_5_furor_gives_40_energy_on_entering_cat_form() {
    given_restoration_talent_rank("Furor", 5);
    pchar->prepare_set_of_combat_iterations();
    given_druid_has_energy(0);

    when_cat_form_is_performed();

    then_druid_has_energy(40);
}

void TestCatForm::when_cat_form_is_performed() {
    cat_form()->perform();
}
