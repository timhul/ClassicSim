#include "TestSpellMage.h"

#include <cassert>
#include <utility>

#include "Arcane.h"
#include "ArcaneMissiles.h"
#include "Buff.h"
#include "CharacterStats.h"
#include "Equipment.h"
#include "Evocation.h"
#include "Fire.h"
#include "Fireball.h"
#include "Frost.h"
#include "Frostbolt.h"
#include "Item.h"
#include "Mage.h"
#include "MageSpells.h"
#include "RaidControl.h"
#include "Scorch.h"
#include "SimSettings.h"
#include "Spell.h"
#include "Talent.h"

TestSpellMage::TestSpellMage(EquipmentDb* equipment_db, QString spell_under_test) :
    TestSpellDamage(equipment_db, std::move(spell_under_test)), mage(nullptr) {}

void TestSpellMage::set_up(const bool prepare_combat_iterations) {
    set_up_general();
    mage = new Mage(race, equipment_db, sim_settings, raid_control);
    mage->set_clvl(60);
    pchar = mage;

    if (prepare_combat_iterations) {
        raid_control->prepare_set_of_combat_iterations();
        pchar->prepare_set_of_combat_iterations();
    }
}

void TestSpellMage::tear_down() {
    delete mage;
    tear_down_general();
}

Fireball* TestSpellMage::fireball() const {
    return static_cast<Fireball*>(get_max_rank_spell_by_name("Fireball"));
}

Scorch* TestSpellMage::scorch() const {
    return static_cast<Scorch*>(get_max_rank_spell_by_name("Scorch"));
}

Frostbolt* TestSpellMage::frostbolt() const {
    return static_cast<Frostbolt*>(get_max_rank_spell_by_name("Frostbolt"));
}

ArcaneMissiles* TestSpellMage::arcane_missiles() const {
    return static_cast<ArcaneMissiles*>(get_max_rank_spell_by_name("Arcane Missiles"));
}

Evocation* TestSpellMage::evocation() const {
    return static_cast<Evocation*>(get_max_rank_spell_by_name("Evocation"));
}

void TestSpellMage::run_class_specific_tests() {}

void TestSpellMage::given_fire_talent_rank(const QString& talent_name, const unsigned num) {
    given_talent_rank(Fire(mage), talent_name, num);
}

void TestSpellMage::given_frost_talent_rank(const QString& talent_name, const unsigned num) {
    given_talent_rank(Frost(mage), talent_name, num);
}

void TestSpellMage::given_mage_is_on_gcd(Spell* spell) {
    unsigned mana_before = mage->get_resource_level(ResourceType::Mana);
    mage->gain_mana(static_cast<unsigned>(spell->get_resource_cost()));

    spell->perform();

    int mana_delta = static_cast<int>(mage->get_resource_level(ResourceType::Mana)) - static_cast<int>(mana_before);

    if (mana_delta < 0)
        mage->gain_mana(static_cast<unsigned>(mana_delta * -1));
    else
        mage->lose_mana(static_cast<unsigned>(mana_delta));

    assert(mage->on_global_cooldown());
}

void TestSpellMage::given_arcane_power_is_active() {
    auto tree = Arcane(mage);
    given_talent_rank(tree, "Presence of Mind", 1);
    given_talent_rank(tree, "Arcane Instability", 3);
    given_talent_rank(tree, "Arcane Power", 1);

    mage->prepare_set_of_combat_iterations();

    get_max_rank_spell_by_name("Arcane Power")->perform();

    const double arcane_instability = 1.03;
    const double arcane_power = 1.3;

    assert(almost_equal(arcane_power * arcane_instability, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Arcane)));
    assert(almost_equal(arcane_power * arcane_instability, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Fire)));
    assert(almost_equal(arcane_power * arcane_instability, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Frost)));
    assert(almost_equal(arcane_power * arcane_instability, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Holy)));
    assert(almost_equal(arcane_power * arcane_instability, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Nature)));
    assert(almost_equal(arcane_power * arcane_instability, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Shadow)));
}

void TestSpellMage::given_mage_has_mana(const unsigned mana) {
    if (mage->get_resource_level(ResourceType::Mana) > 0)
        mage->lose_mana(mage->get_resource_level(ResourceType::Mana));
    mage->gain_mana(mana);
    then_mage_has_mana(mana);
}

void TestSpellMage::then_mage_has_mana(const unsigned mana) {
    if (mana != mage->get_resource_level(ResourceType::Mana))
        qDebug() << "Expected" << mana << "mana but has" << mage->get_resource_level(ResourceType::Mana);
    assert(mage->get_resource_level(ResourceType::Mana) == mana);
}
