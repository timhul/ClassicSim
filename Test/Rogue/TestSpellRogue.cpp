#include "TestSpellRogue.h"

#include <cassert>
#include <QDebug>

#include "Assassination.h"
#include "Backstab.h"
#include "Combat.h"
#include "Equipment.h"
#include "RaidControl.h"
#include "Rogue.h"
#include "RogueSpells.h"
#include "SimSettings.h"
#include "Spell.h"
#include "Subtlety.h"
#include "Talent.h"

TestSpellRogue::TestSpellRogue(EquipmentDb *equipment_db, const QString& spell_under_test) :
    TestSpellDamage(equipment_db, spell_under_test),
    rogue(nullptr)
{}

void TestSpellRogue::set_up(const bool prepare_combat_iterations) {
    set_up_general();
    rogue = new Rogue(race, equipment_db, sim_settings, raid_control);
    rogue->set_clvl(60);
    pchar = rogue;

    if (prepare_combat_iterations) {
        raid_control->prepare_set_of_combat_iterations();
        pchar->prepare_set_of_combat_iterations();
    }
}

void TestSpellRogue::tear_down() {
    delete rogue;
    tear_down_general();
}

void TestSpellRogue::given_rogue_is_on_gcd() {
    if (pchar->get_equipment()->get_mainhand() == nullptr)
        given_a_mainhand_weapon_with_100_min_max_dmg();

    given_rogue_is_on_gcd(dynamic_cast<RogueSpells*>(pchar->get_spells())->get_backstab());
}

void TestSpellRogue::given_rogue_is_on_gcd(Spell *spell) {
    unsigned energy_before = rogue->get_resource_level(ResourceType::Energy);
    rogue->gain_energy(100 - energy_before);

    spell->perform();

    int energy_delta = static_cast<int>(rogue->get_resource_level(ResourceType::Energy)) - static_cast<int>(energy_before);

    if (energy_delta < 0)
        rogue->gain_energy(static_cast<unsigned>(energy_delta * -1));
    else
        rogue->lose_energy(static_cast<unsigned>(energy_delta));

    assert(rogue->on_global_cooldown());
}

void TestSpellRogue::given_rogue_in_stealth() {
    rogue->enter_stealth();
    assert(rogue->is_stealthed());
}

void TestSpellRogue::given_rogue_not_in_stealth() {
    rogue->exit_stealth();
    assert(!rogue->is_stealthed());
}

void TestSpellRogue::given_rogue_has_energy(const unsigned energy) {
    if (rogue->get_resource_level(ResourceType::Energy) > 0)
        rogue->lose_energy(rogue->get_resource_level(ResourceType::Energy));
    rogue->gain_energy(energy);
    then_rogue_has_energy(energy);
}

void TestSpellRogue::given_rogue_has_combo_points(const unsigned combo_points) {
    rogue->spend_combo_points();
    rogue->gain_combo_points(combo_points);
    assert(rogue->get_combo_points() == combo_points);
}

void TestSpellRogue::then_rogue_has_energy(const unsigned energy) const {
    if (energy != rogue->get_resource_level(ResourceType::Energy))
        qDebug() << spell_under_test << "Expected" << energy << "energy but actually has" << rogue->get_resource_level(ResourceType::Energy);
    assert(rogue->get_resource_level(ResourceType::Energy) == energy);
}

void TestSpellRogue::then_rogue_has_combo_points(const unsigned combo_points) const {
    if (combo_points != rogue->get_combo_points())
        qDebug() << spell_under_test << "Expected" << combo_points << "combo points but actually has" << rogue->get_combo_points();
    assert(rogue->get_combo_points() == combo_points);
}

void TestSpellRogue::given_assassination_talent_rank(const QString& talent_name, const unsigned num) {
    given_talent_rank(Assassination(rogue), talent_name, num);
}

void TestSpellRogue::given_combat_talent_rank(const QString& talent_name, const unsigned num) {
    given_talent_rank(Combat(rogue), talent_name, num);
}

void TestSpellRogue::given_subtlety_talent_rank(const QString& talent_name, const unsigned num) {
    given_talent_rank(Subtlety(rogue), talent_name, num);
}

void TestSpellRogue::given_lethality_talent_rank(const unsigned num) {
    auto assa = Assassination(rogue);

    given_talent_rank(assa, "Malice", 5);
    given_talent_rank(assa, "Lethality", num);
}
