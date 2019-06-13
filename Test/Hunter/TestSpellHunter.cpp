#include "TestSpellHunter.h"

#include <QDebug>
#include <utility>

#include "CharacterStats.h"
#include "Equipment.h"
#include "HunterSpells.h"
#include "Marksmanship.h"
#include "MultiShot.h"
#include "RaidControl.h"
#include "Spell.h"
#include "Survival.h"
#include "Talent.h"

TestSpellHunter::TestSpellHunter(EquipmentDb *equipment_db, QString spell_under_test) :
    TestSpellDamage(equipment_db, std::move(spell_under_test)),
    hunter(nullptr)
{}

void TestSpellHunter::set_up(const bool prepare_combat_iterations) {
    set_up_general();
    hunter = new Hunter(race, equipment_db, sim_settings, raid_control);
    hunter->set_clvl(60);
    pchar = hunter;
    given_in_ranged_attack_mode();

    // TODO: This will fail when the hardcoded quiver bonus is removed.
    hunter->get_stats()->decrease_ranged_attack_speed(15);

    if (prepare_combat_iterations) {
        raid_control->prepare_set_of_combat_iterations();
        pchar->prepare_set_of_combat_iterations();
    }
}

void TestSpellHunter::tear_down() {
    delete hunter;
    tear_down_general();
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

void TestSpellHunter::given_1_of_5_efficiency() {
    Talent* talent = Marksmanship(hunter).get_efficiency();

    assert(talent->increment_rank());

    delete talent;
}

void TestSpellHunter::given_2_of_5_efficiency() {
    Talent* talent = Marksmanship(hunter).get_efficiency();

    assert(talent->increment_rank());
    assert(talent->increment_rank());

    delete talent;
}

void TestSpellHunter::given_3_of_5_efficiency() {
    Talent* talent = Marksmanship(hunter).get_efficiency();

    assert(talent->increment_rank());
    assert(talent->increment_rank());
    assert(talent->increment_rank());

    delete talent;
}

void TestSpellHunter::given_4_of_5_efficiency() {
    Talent* talent = Marksmanship(hunter).get_efficiency();

    assert(talent->increment_rank());
    assert(talent->increment_rank());
    assert(talent->increment_rank());
    assert(talent->increment_rank());

    delete talent;
}

void TestSpellHunter::given_5_of_5_efficiency() {
    Talent* talent = Marksmanship(hunter).get_efficiency();

    assert(talent->increment_rank());
    assert(talent->increment_rank());
    assert(talent->increment_rank());
    assert(talent->increment_rank());
    assert(talent->increment_rank());

    delete talent;
}

void TestSpellHunter::given_1_of_5_mortal_shots() {
    Talent* talent = Marksmanship(hunter).get_mortal_shots();

    assert(talent->increment_rank());

    delete talent;
}

void TestSpellHunter::given_2_of_5_mortal_shots() {
    Talent* talent = Marksmanship(hunter).get_mortal_shots();

    assert(talent->increment_rank());
    assert(talent->increment_rank());
    delete talent;
}

void TestSpellHunter::given_3_of_5_mortal_shots() {
    Talent* talent = Marksmanship(hunter).get_mortal_shots();

    assert(talent->increment_rank());
    assert(talent->increment_rank());
    assert(talent->increment_rank());

    delete talent;
}

void TestSpellHunter::given_4_of_5_mortal_shots() {
    Talent* talent = Marksmanship(hunter).get_mortal_shots();

    assert(talent->increment_rank());
    assert(talent->increment_rank());
    assert(talent->increment_rank());
    assert(talent->increment_rank());

    delete talent;
}

void TestSpellHunter::given_5_of_5_mortal_shots() {
    Talent* talent = Marksmanship(hunter).get_mortal_shots();

    assert(talent->increment_rank());
    assert(talent->increment_rank());
    assert(talent->increment_rank());
    assert(talent->increment_rank());
    assert(talent->increment_rank());

    delete talent;
}

void TestSpellHunter::given_5_of_5_ranged_weapon_specialization() {
    Talent* talent = Marksmanship(hunter).get_ranged_weapon_specialization();

    assert(talent->increment_rank());
    assert(talent->increment_rank());
    assert(talent->increment_rank());
    assert(talent->increment_rank());
    assert(talent->increment_rank());

    delete talent;
}

void TestSpellHunter::given_1_of_3_monster_slaying() {
    Talent* talent = Survival(hunter).get_monster_slaying();

    assert(talent->increment_rank());

    delete talent;
}

void TestSpellHunter::given_2_of_3_monster_slaying() {
    Talent* talent = Survival(hunter).get_monster_slaying();

    assert(talent->increment_rank());
    assert(talent->increment_rank());
    delete talent;
}

void TestSpellHunter::given_3_of_3_monster_slaying() {
    Talent* talent = Survival(hunter).get_monster_slaying();

    assert(talent->increment_rank());
    assert(talent->increment_rank());
    assert(talent->increment_rank());

    delete talent;
}

void TestSpellHunter::given_1_of_3_humanoid_slaying() {
    Talent* talent = Survival(hunter).get_humanoid_slaying();

    assert(talent->increment_rank());

    delete talent;
}

void TestSpellHunter::given_2_of_3_humanoid_slaying() {
    Talent* talent = Survival(hunter).get_humanoid_slaying();

    assert(talent->increment_rank());
    assert(talent->increment_rank());
    delete talent;
}

void TestSpellHunter::given_3_of_3_humanoid_slaying() {
    Talent* talent = Survival(hunter).get_humanoid_slaying();

    assert(talent->increment_rank());
    assert(talent->increment_rank());
    assert(talent->increment_rank());

    delete talent;
}

void TestSpellHunter::given_1_of_3_barrage() {
    Talent* talent = Marksmanship(hunter).get_barrage();

    assert(talent->increment_rank());

    delete talent;
}

void TestSpellHunter::given_2_of_3_barrage() {
    Talent* talent = Marksmanship(hunter).get_barrage();

    assert(talent->increment_rank());
    assert(talent->increment_rank());
    delete talent;
}

void TestSpellHunter::given_3_of_3_barrage() {
    Talent* talent = Marksmanship(hunter).get_barrage();

    assert(talent->increment_rank());
    assert(talent->increment_rank());
    assert(talent->increment_rank());

    delete talent;
}
