#include "TestSpellHunter.h"

#include <QDebug>
#include <utility>

#include "Equipment.h"
#include "HunterSpells.h"
#include "MultiShot.h"
#include "Spell.h"

TestSpellHunter::TestSpellHunter(EquipmentDb *equipment_db, QString spell_under_test) :
    TestSpellDamage(equipment_db, std::move(spell_under_test)),
    hunter(nullptr)
{}

void TestSpellHunter::set_up(const bool prepare_combat_iterations) {
    set_up_general();
    hunter = new Hunter(race, equipment_db, sim_settings);
    hunter->set_clvl(60);
    pchar = hunter;

    if (prepare_combat_iterations)
        pchar->prepare_set_of_combat_iterations();
}

void TestSpellHunter::tear_down() {
    tear_down_general();
    delete hunter;
}

void TestSpellHunter::given_hunter_has_mana(const unsigned mana) {
    if (hunter->get_resource_level(ResourceType::Mana) > 0)
        hunter->lose_mana(hunter->get_resource_level(ResourceType::Mana));
    hunter->gain_mana(mana);
    then_hunter_has_mana(mana);
}

void TestSpellHunter::then_hunter_has_mana(const unsigned mana) {
    if (mana != hunter->get_resource_level(ResourceType::Mana))
        qDebug() << spell_under_test << "expected" << mana << "mana but has" << hunter->get_resource_level(ResourceType::Mana);
    assert(hunter->get_resource_level(ResourceType::Mana) == mana);
}

void TestSpellHunter::given_hunter_is_on_gcd() {
    unsigned resource_before = hunter->get_resource_level(ResourceType::Mana);
    hunter->gain_mana(1000 - resource_before);

    if (pchar->get_equipment()->get_ranged() == nullptr)
        given_a_ranged_weapon_with_100_min_max_dmg();

    dynamic_cast<HunterSpells*>(hunter->get_spells())->get_multi_shot()->perform();

    int resource_delta = static_cast<int>(hunter->get_resource_level(ResourceType::Mana)) - static_cast<int>(resource_before);

    if (resource_delta < 0)
        hunter->gain_mana(static_cast<unsigned>(resource_delta * -1));
    else
        hunter->lose_mana(static_cast<unsigned>(resource_delta));

    assert(hunter->on_global_cooldown());
}
