#include "TestSpellPaladin.h"

#include <QDebug>
#include <utility>

#include "CharacterStats.h"
#include "Equipment.h"
#include "Paladin.h"
#include "PaladinSpells.h"
#include "SealOfTheCrusader.h"
#include "SimSettings.h"
#include "Spell.h"

TestSpellPaladin::TestSpellPaladin(EquipmentDb *equipment_db, QString spell_under_test) :
    TestSpellDamage(equipment_db, std::move(spell_under_test)),
    paladin(nullptr)
{}

void TestSpellPaladin::set_up(const bool prepare_combat_iterations) {
    set_up_general();
    paladin = new Paladin(race, equipment_db, sim_settings);
    paladin->set_clvl(60);
    pchar = paladin;

    if (prepare_combat_iterations)
        pchar->prepare_set_of_combat_iterations();
}

void TestSpellPaladin::tear_down() {
    tear_down_general();
    delete paladin;
}

void TestSpellPaladin::run_class_specific_tests() {

}

void TestSpellPaladin::given_paladin_is_on_gcd() {
    given_paladin_is_on_gcd(dynamic_cast<PaladinSpells*>(pchar->get_spells())->get_seal_of_the_crusader());
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

void TestSpellPaladin::given_paladin_has_mana(const unsigned mana) {
    if (paladin->get_resource_level(ResourceType::Mana) > 0)
        paladin->lose_mana(paladin->get_resource_level(ResourceType::Mana));
    paladin->gain_mana(mana);
    then_paladin_has_mana(mana);
}

void TestSpellPaladin::then_paladin_has_mana(const unsigned mana) {
    assert(paladin->get_resource_level(ResourceType::Mana) == mana);
}
