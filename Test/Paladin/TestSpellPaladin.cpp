#include "TestSpellPaladin.h"

#include <QDebug>
#include <utility>

#include "Buff.h"
#include "CharacterStats.h"
#include "Equipment.h"
#include "Item.h"
#include "MainhandAttackPaladin.h"
#include "Paladin.h"
#include "PaladinSpells.h"
#include "RaidControl.h"
#include "Retribution.h"
#include "SealOfCommand.h"
#include "SealOfTheCrusader.h"
#include "SealOfTheCrusader.h"
#include "SimSettings.h"
#include "Spell.h"

TestSpellPaladin::TestSpellPaladin(EquipmentDb *equipment_db, QString spell_under_test) :
    TestSpellDamage(equipment_db, std::move(spell_under_test)),
    paladin(nullptr)
{}

void TestSpellPaladin::set_up(const bool prepare_combat_iterations) {
    set_up_general();
    paladin = new Paladin(race, equipment_db, sim_settings, raid_control);
    paladin->set_clvl(60);
    pchar = paladin;

    if (prepare_combat_iterations) {
        raid_control->prepare_set_of_combat_iterations();
        pchar->prepare_set_of_combat_iterations();
    }
}

void TestSpellPaladin::tear_down() {
    delete paladin;
    tear_down_general();
}

void TestSpellPaladin::run_class_specific_tests() {

}

MainhandAttackPaladin* TestSpellPaladin::mh_attack() {
    auto* spells = dynamic_cast<PaladinSpells*>(paladin->get_spells());
    return dynamic_cast<MainhandAttackPaladin*>(spells->get_mh_attack());
}

SealOfCommand* TestSpellPaladin::seal_of_command() {
    return dynamic_cast<SealOfCommand*>(get_max_rank_spell_by_name("Seal of Command"));
}

SealOfTheCrusader* TestSpellPaladin::seal_of_the_crusader() {
    return dynamic_cast<SealOfTheCrusader*>(get_max_rank_spell_by_name("Seal of the Crusader"));
}

void TestSpellPaladin::given_paladin_is_on_gcd() {
    given_paladin_is_on_gcd(seal_of_the_crusader());
}

void TestSpellPaladin::given_paladin_is_on_gcd(Spell* spell) {
    unsigned mana_before = paladin->get_resource_level(ResourceType::Mana);
    paladin->gain_mana(static_cast<unsigned>(spell->get_resource_cost()));

    spell->perform();

    int mana_delta = static_cast<int>(paladin->get_resource_level(ResourceType::Mana)) - static_cast<int>(mana_before);

    if (mana_delta < 0)
        paladin->gain_mana(static_cast<unsigned>(mana_delta * -1));
    else
        paladin->lose_mana(static_cast<unsigned>(mana_delta));

    assert(paladin->on_global_cooldown());
}

void TestSpellPaladin::given_relic_equipped(const int item_id) {
    paladin->get_equipment()->set_relic(item_id);
    assert(paladin->get_equipment()->get_relic());
    assert(paladin->get_equipment()->get_relic()->get_item_id());
}

void TestSpellPaladin::given_no_relic_equipped() {
    paladin->get_equipment()->clear_relic();
    assert(!paladin->get_equipment()->get_relic());
}

void TestSpellPaladin::given_paladin_has_mana(const unsigned mana) {
    if (paladin->get_resource_level(ResourceType::Mana) > 0)
        paladin->lose_mana(paladin->get_resource_level(ResourceType::Mana));
    paladin->gain_mana(mana);
    then_paladin_has_mana(mana);
}

void TestSpellPaladin::given_benediction_rank(const unsigned num) {
    given_talent_rank(Retribution(paladin).get_benediction(), num);
}

void TestSpellPaladin::given_improved_sotc_rank(const unsigned num) {
    given_talent_rank(Retribution(paladin).get_improved_seal_of_the_crusader(), num);
}

void TestSpellPaladin::given_seal_of_the_crusader_is_active() {
    seal_of_the_crusader()->perform();
    assert(seal_of_the_crusader()->get_buff()->is_active());
}

void TestSpellPaladin::given_seal_of_command_is_enabled() {
    given_talent_rank(Retribution(paladin).get_seal_of_command(), 1);
    assert(seal_of_command()->is_enabled());
    paladin->prepare_set_of_combat_iterations();
}

void TestSpellPaladin::given_seal_of_command_is_active() {
    given_seal_of_command_is_enabled();
    seal_of_command()->perform();
    assert(seal_of_command()->get_buff()->is_active());
}

void TestSpellPaladin::when_mh_attack_is_performed() {
    if (pchar->get_equipment()->get_mainhand() == nullptr)
        given_a_mainhand_weapon_with_100_min_max_dmg();

    mh_attack()->perform();
}

void TestSpellPaladin::when_seal_of_the_crusader_is_performed() {
    if (pchar->get_equipment()->get_mainhand() == nullptr)
        given_a_mainhand_weapon_with_100_min_max_dmg();

    seal_of_the_crusader()->perform();
}

void TestSpellPaladin::when_seal_of_command_is_performed() {
    if (pchar->get_equipment()->get_mainhand() == nullptr)
        given_a_mainhand_weapon_with_100_min_max_dmg();

    seal_of_command()->perform();
}

void TestSpellPaladin::then_paladin_has_mana(const unsigned mana) {
    assert(paladin->get_resource_level(ResourceType::Mana) == mana);
}
