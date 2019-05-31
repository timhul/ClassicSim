#include "TestSpellShaman.h"

#include <QDebug>
#include <utility>

#include "Buff.h"
#include "CharacterStats.h"
#include "Enhancement.h"
#include "Equipment.h"
#include "Item.h"
#include "LightningBolt.h"
#include "MainhandAttack.h"
#include "Shaman.h"
#include "ShamanSpells.h"
#include "SimSettings.h"
#include "Spell.h"
#include "Stormstrike.h"

TestSpellShaman::TestSpellShaman(EquipmentDb *equipment_db, QString spell_under_test) :
    TestSpellDamage(equipment_db, std::move(spell_under_test)),
    shaman(nullptr)
{}

void TestSpellShaman::set_up(const bool prepare_combat_iterations) {
    set_up_general();
    shaman = new Shaman(race, equipment_db, sim_settings);
    shaman->set_clvl(60);
    pchar = shaman;

    if (prepare_combat_iterations)
        pchar->prepare_set_of_combat_iterations();
}

void TestSpellShaman::tear_down() {
    tear_down_general();
    delete shaman;
}

MainhandAttack* TestSpellShaman::mh_attack() const {
    return pchar->get_spells()->get_mh_attack();
}

Stormstrike* TestSpellShaman::stormstrike() const {
    return dynamic_cast<Stormstrike*>(get_max_rank_spell_by_name("Stormstrike"));
}

LightningBolt* TestSpellShaman::lightning_bolt() const {
    return dynamic_cast<LightningBolt*>(get_max_rank_spell_by_name("Lightning Bolt"));
}

void TestSpellShaman::run_class_specific_tests() {

}

/*void TestSpellShaman::given_Shaman_is_on_gcd() {
    given_Shaman_is_on_gcd(seal_of_the_crusader());
}*/

void TestSpellShaman::given_shaman_is_on_gcd(Spell* spell) {
    unsigned mana_before = shaman->get_resource_level(ResourceType::Mana);
    shaman->gain_mana(static_cast<unsigned>(spell->get_resource_cost()));

    spell->perform();

    int mana_delta = static_cast<int>(shaman->get_resource_level(ResourceType::Mana)) - static_cast<int>(mana_before);

    if (mana_delta < 0)
        shaman->gain_mana(static_cast<unsigned>(mana_delta * -1));
    else
        shaman->lose_mana(static_cast<unsigned>(mana_delta));

    assert(shaman->on_global_cooldown());
}

void TestSpellShaman::given_relic_equipped(const int item_id) {
    shaman->get_equipment()->set_relic(item_id);
    assert(shaman->get_equipment()->get_relic());
    assert(shaman->get_equipment()->get_relic()->get_item_id());
}

void TestSpellShaman::given_no_relic_equipped() {
    shaman->get_equipment()->clear_relic();
    assert(!shaman->get_equipment()->get_relic());
}

void TestSpellShaman::given_shaman_has_mana(const unsigned mana) {
    if (shaman->get_resource_level(ResourceType::Mana) > 0)
        shaman->lose_mana(shaman->get_resource_level(ResourceType::Mana));
    shaman->gain_mana(mana);
    then_shaman_has_mana(mana);
}

void TestSpellShaman::given_stormstrike_enabled() {
    given_talent_rank(Enhancement(shaman).get_stormstrike(), 1);
    pchar->prepare_set_of_combat_iterations();
}

void TestSpellShaman::when_mh_attack_is_performed() {
    if (pchar->get_equipment()->get_mainhand() == nullptr)
        given_a_mainhand_weapon_with_100_min_max_dmg();

    mh_attack()->perform();
}

void TestSpellShaman::when_stormstrike_is_performed() {
    if (pchar->get_equipment()->get_mainhand() == nullptr)
        given_a_twohand_weapon_with_100_min_max_dmg();

    stormstrike()->perform();
}

void TestSpellShaman::then_shaman_has_mana(const unsigned mana) {
    assert(shaman->get_resource_level(ResourceType::Mana) == mana);
}
