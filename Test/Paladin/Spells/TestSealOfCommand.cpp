#include "TestSealOfCommand.h"

#include "Buff.h"
#include "Equipment.h"
#include "Paladin.h"
#include "PaladinSpells.h"
#include "SealOfCommand.h"
#include "SealOfCommandProc.h"
#include "SealOfTheCrusader.h"
#include "Weapon.h"

TestSealOfCommand::TestSealOfCommand(EquipmentDb *equipment_db) :
    TestSpellPaladin(equipment_db, "Seal of Command")
{}

void TestSealOfCommand::test_all() {
    run_mandatory_tests(false);

    set_up(false);
    test_resource_cost_1_of_5_benediction();
    tear_down();

    set_up(false);
    test_resource_cost_2_of_5_benediction();
    tear_down();

    set_up(false);
    test_resource_cost_3_of_5_benediction();
    tear_down();

    set_up(false);
    test_resource_cost_4_of_5_benediction();
    tear_down();

    set_up(false);
    test_resource_cost_5_of_5_benediction();
    tear_down();

    set_up(false);
    test_seal_of_command_removes_active_seal_of_the_crusader();
    tear_down();

    set_up(false);
    test_libram_of_hope_reduces_mana_cost();
    tear_down();

    set_up(false);
    test_proc_rate_with_given_weapon_speed();
    tear_down();
}

Proc* TestSealOfCommand::seal_of_command_proc() const {
    return dynamic_cast<SealOfCommand*>(get_max_rank_spell_by_name("Seal of Command"))->get_proc();
}

void TestSealOfCommand::test_name_correct() {
    assert(seal_of_command()->get_name() == "Seal of Command");
}

void TestSealOfCommand::test_spell_cooldown() {
    assert(almost_equal(seal_of_command()->get_base_cooldown(), 0.0));
}

void TestSealOfCommand::test_how_spell_observes_global_cooldown() {
    given_seal_of_command_is_enabled();
    assert(seal_of_command()->get_spell_status() == SpellStatus::Available);

    given_paladin_is_on_gcd();

    assert(seal_of_command()->get_spell_status() == SpellStatus::OnGCD);
}

void TestSealOfCommand::test_resource_cost() {
    given_seal_of_command_is_enabled();

    given_paladin_has_mana(64);
    assert(seal_of_command()->get_spell_status() == SpellStatus::InsufficientResources);

    given_paladin_has_mana(65);
    assert(seal_of_command()->get_spell_status() == SpellStatus::Available);

    given_paladin_has_mana(66);
    when_seal_of_command_is_performed();
    then_paladin_has_mana(1);
}

void TestSealOfCommand::test_is_ready_conditions() {
    // No conditions not tested in other mandatory tests.
}

void TestSealOfCommand::test_whether_spell_causes_global_cooldown() {
    assert(paladin->action_ready());

    when_seal_of_command_is_performed();

    assert(!paladin->action_ready());
}

void TestSealOfCommand::test_resource_cost_1_of_5_benediction() {
    given_seal_of_command_is_enabled();
    given_retribution_talent_rank("Benediction", 1);

    given_paladin_has_mana(62);
    assert(seal_of_command()->get_spell_status() == SpellStatus::InsufficientResources);

    given_paladin_has_mana(63);
    assert(seal_of_command()->get_spell_status() == SpellStatus::Available);

    given_paladin_has_mana(64);
    when_seal_of_command_is_performed();
    then_paladin_has_mana(1);
}

void TestSealOfCommand::test_resource_cost_2_of_5_benediction() {
    given_seal_of_command_is_enabled();
    given_retribution_talent_rank("Benediction", 2);

    given_paladin_has_mana(60);
    assert(seal_of_command()->get_spell_status() == SpellStatus::InsufficientResources);

    given_paladin_has_mana(61);
    assert(seal_of_command()->get_spell_status() == SpellStatus::Available);

    given_paladin_has_mana(62);
    when_seal_of_command_is_performed();
    then_paladin_has_mana(1);
}

void TestSealOfCommand::test_resource_cost_3_of_5_benediction() {
    given_seal_of_command_is_enabled();
    given_retribution_talent_rank("Benediction", 3);

    given_paladin_has_mana(58);
    assert(seal_of_command()->get_spell_status() == SpellStatus::InsufficientResources);

    given_paladin_has_mana(59);
    assert(seal_of_command()->get_spell_status() == SpellStatus::Available);

    given_paladin_has_mana(60);
    when_seal_of_command_is_performed();
    then_paladin_has_mana(1);
}

void TestSealOfCommand::test_resource_cost_4_of_5_benediction() {
    given_seal_of_command_is_enabled();
    given_retribution_talent_rank("Benediction", 4);

    given_paladin_has_mana(56);
    assert(seal_of_command()->get_spell_status() == SpellStatus::InsufficientResources);

    given_paladin_has_mana(57);
    assert(seal_of_command()->get_spell_status() == SpellStatus::Available);

    given_paladin_has_mana(58);
    when_seal_of_command_is_performed();
    then_paladin_has_mana(1);
}

void TestSealOfCommand::test_resource_cost_5_of_5_benediction() {
    given_seal_of_command_is_enabled();
    given_retribution_talent_rank("Benediction", 5);

    given_paladin_has_mana(54);
    assert(seal_of_command()->get_spell_status() == SpellStatus::InsufficientResources);

    given_paladin_has_mana(55);
    assert(seal_of_command()->get_spell_status() == SpellStatus::Available);

    given_paladin_has_mana(56);
    when_seal_of_command_is_performed();
    then_paladin_has_mana(1);
}

void TestSealOfCommand::test_seal_of_command_removes_active_seal_of_the_crusader() {
    given_seal_of_command_is_enabled();
    given_seal_of_the_crusader_is_active();
    given_engine_priority_pushed_forward(1.5);
    assert(seal_of_the_crusader()->get_buff()->is_active());

    when_seal_of_command_is_performed();

    assert(!seal_of_the_crusader()->get_buff()->is_active());
}

void TestSealOfCommand::test_libram_of_hope_reduces_mana_cost() {
    given_seal_of_command_is_enabled();
    const double original_mana_cost = seal_of_the_crusader()->get_resource_cost();

    given_relic_equipped(22401);
    assert(almost_equal(20.0, original_mana_cost - seal_of_the_crusader()->get_resource_cost()));

    given_no_relic_equipped();
    assert(almost_equal(0.0, original_mana_cost - seal_of_the_crusader()->get_resource_cost()));
}

void TestSealOfCommand::test_proc_rate_with_given_weapon_speed() {
    given_2h_axe_equipped(paladin);
    assert(almost_equal(3.8, paladin->get_equipment()->get_mainhand()->get_base_weapon_speed()));

    // proc_rate% = ppm / (60 / wpn_speed)
    // 44.3% ~= 7.0 / (60 / 3.8)

    // Implementation specific detail: proc rate is a 10000 die roll.
    assert(4433 == seal_of_command_proc()->get_proc_range());
}
