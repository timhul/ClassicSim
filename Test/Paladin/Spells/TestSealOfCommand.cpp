#include "TestSealOfCommand.h"

#include "Buff.h"
#include "CharacterStats.h"
#include "Equipment.h"
#include "MainhandAttackPaladin.h"
#include "PaladinSpells.h"
#include "Retribution.h"
#include "SealOfCommand.h"
#include "Talent.h"

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
}

MainhandAttackPaladin* TestSealOfCommand::mh_attack() {
    auto* spells = dynamic_cast<PaladinSpells*>(paladin->get_spells());
    return dynamic_cast<MainhandAttackPaladin*>(spells->get_mh_attack());
}

SealOfCommand *TestSealOfCommand::seal_of_command() {
    auto* spells = dynamic_cast<PaladinSpells*>(paladin->get_spells());
    return dynamic_cast<SealOfCommand*>(spells->get_seal_of_command());
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
    given_benediction_rank(1);

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
    given_benediction_rank(2);

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
    given_benediction_rank(3);

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
    given_benediction_rank(4);

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
    given_benediction_rank(5);

    given_paladin_has_mana(54);
    assert(seal_of_command()->get_spell_status() == SpellStatus::InsufficientResources);

    given_paladin_has_mana(55);
    assert(seal_of_command()->get_spell_status() == SpellStatus::Available);

    given_paladin_has_mana(56);
    when_seal_of_command_is_performed();
    then_paladin_has_mana(1);
}

void TestSealOfCommand::when_mh_attack_is_performed() {
    if (pchar->get_equipment()->get_mainhand() == nullptr)
        given_a_mainhand_weapon_with_100_min_max_dmg();

    mh_attack()->perform();
}

void TestSealOfCommand::when_seal_of_command_is_performed() {
    if (pchar->get_equipment()->get_mainhand() == nullptr)
        given_a_mainhand_weapon_with_100_min_max_dmg();

    seal_of_command()->perform();
}

void TestSealOfCommand::given_benediction_rank(const unsigned num) {
    given_talent_rank(Retribution(paladin).get_benediction(), num);
}

void TestSealOfCommand::given_seal_of_command_is_enabled() {
    given_talent_rank(Retribution(paladin).get_seal_of_command(), 1);
    assert(seal_of_command()->is_enabled());
    paladin->prepare_set_of_combat_iterations();
}

void TestSealOfCommand::given_seal_of_command_is_active() {
    given_seal_of_command_is_enabled();
    seal_of_command()->perform();
    assert(seal_of_command()->get_buff()->is_active());
}
