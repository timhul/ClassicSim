#include "TestSpellWarlock.h"

#include <cassert>
#include <utility>

#include "Affliction.h"
#include "CharacterStats.h"
#include "Demonology.h"
#include "Destruction.h"
#include "LifeTap.h"
#include "RaidControl.h"
#include "ShadowBolt.h"
#include "Spell.h"
#include "Talent.h"
#include "Warlock.h"
#include "WarlockSpells.h"

TestSpellWarlock::TestSpellWarlock(EquipmentDb* equipment_db_, QString spell_under_test_) :
    TestSpellDamage(equipment_db_, std::move(spell_under_test_)), warlock(nullptr) {}

void TestSpellWarlock::set_up(const bool prepare_combat_iterations) {
    set_up_general();
    warlock = new Warlock(race, equipment_db, sim_settings, raid_control);
    warlock->set_clvl(60);
    pchar = warlock;

    if (prepare_combat_iterations) {
        raid_control->prepare_set_of_combat_iterations();
        pchar->prepare_set_of_combat_iterations();
    }
}

void TestSpellWarlock::tear_down() {
    delete warlock;
    tear_down_general();
}

LifeTap* TestSpellWarlock::life_tap() const {
    return static_cast<LifeTap*>(get_max_rank_spell_by_name("Life Tap"));
}

ShadowBolt* TestSpellWarlock::shadow_bolt() const {
    return static_cast<ShadowBolt*>(get_max_rank_spell_by_name("Shadow Bolt"));
}

void TestSpellWarlock::run_class_specific_tests() {}

void TestSpellWarlock::given_ruin_enabled() {
    auto tree = Destruction(warlock);
    given_talent_rank(tree, "Devastation", 5);
    given_talent_rank(tree, "Ruin", 1);
}

void TestSpellWarlock::given_affliction_talent_rank(const QString& talent_name, const unsigned num) {
    given_talent_rank(Affliction(warlock), talent_name, num);
}

void TestSpellWarlock::given_destruction_talent_rank(const QString& talent_name, const unsigned num) {
    given_talent_rank(Destruction(warlock), talent_name, num);
}

void TestSpellWarlock::given_demonology_talent_rank(const QString& talent_name, const unsigned num) {
    given_talent_rank(Demonology(warlock), talent_name, num);
}

void TestSpellWarlock::given_warlock_is_on_gcd(Spell* spell) {
    unsigned mana_before = warlock->get_resource_level(ResourceType::Mana);
    warlock->gain_mana(static_cast<unsigned>(spell->get_resource_cost()));

    spell->perform();

    int mana_delta = static_cast<int>(warlock->get_resource_level(ResourceType::Mana)) - static_cast<int>(mana_before);

    if (mana_delta < 0)
        warlock->gain_mana(static_cast<unsigned>(mana_delta * -1));
    else
        warlock->lose_mana(static_cast<unsigned>(mana_delta));

    assert(warlock->on_global_cooldown());
}

void TestSpellWarlock::given_warlock_has_mana(const unsigned mana) {
    if (warlock->get_resource_level(ResourceType::Mana) > 0)
        warlock->lose_mana(warlock->get_resource_level(ResourceType::Mana));
    warlock->gain_mana(mana);
    then_character_has_resource(warlock, ResourceType::Mana, mana);
}

void TestSpellWarlock::then_warlock_has_mana(const unsigned mana) {
    if (mana != warlock->get_resource_level(ResourceType::Mana))
        qDebug() << "Expected" << mana << "mana but has" << warlock->get_resource_level(ResourceType::Mana);
    assert(warlock->get_resource_level(ResourceType::Mana) == mana);
}
