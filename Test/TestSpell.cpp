
#include "TestSpell.h"

#include "Orc.h"
#include "CombatRoll.h"
#include "WhiteHitTable.h"
#include "MeleeSpecialTable.h"
#include "Engine.h"
#include "Equipment.h"
#include "Target.h"
#include "Character.h"
#include "CharacterStats.h"
#include "Onehand.h"
#include "EquipmentDb.h"
#include "MainhandMeleeHit.h"

TestSpell::TestSpell() :
    equipment(nullptr)
{}

TestSpell::~TestSpell() {
    delete equipment;
}

void TestSpell::set_up_general() {
    // not thread safe
    engine = new Engine();
    if (equipment == nullptr)
        equipment = new Equipment();
    target = new Target(63);
    combat = new CombatRoll(target);
    race = new Orc();
}

void TestSpell::tear_down_general() {
    // not thread safe
    delete engine;
    delete combat;
    delete target;
    delete race;
}

void TestSpell::given_no_previous_damage_dealt() {
    then_damage_dealt_is(0);
}

void TestSpell::given_a_guaranteed_white_hit() {
    set_melee_auto_table_for_hit(pchar->get_mh_wpn_skill());
    set_melee_auto_table_for_hit(pchar->get_oh_wpn_skill());
}

void TestSpell::given_a_guaranteed_white_crit() {
    set_melee_auto_table_for_crit(pchar->get_mh_wpn_skill());
    set_melee_auto_table_for_crit(pchar->get_oh_wpn_skill());
}

void TestSpell::given_a_guaranteed_melee_ability_crit() {
    set_melee_special_table_for_crit(pchar->get_mh_wpn_skill());
    set_melee_special_table_for_crit(pchar->get_oh_wpn_skill());
}

void TestSpell::given_a_guaranteed_melee_ability_hit() {
    set_melee_special_table_for_hit(pchar->get_mh_wpn_skill());
    set_melee_special_table_for_hit(pchar->get_oh_wpn_skill());
}

void TestSpell::set_melee_special_table_for_hit(const int wpn_skill) {
    MeleeSpecialTable* table = combat->get_melee_special_table(wpn_skill);
    table->set_miss_range(0);
    table->set_dodge_range(0);
    table->set_parry_range(0);
    table->set_block_range(0);
    table->update_crit_chance(0.0);

    assert(table->get_outcome(0, 0.0) == Outcome::HIT);
    assert(table->get_outcome(9999, 0.0) == Outcome::HIT);

}

void TestSpell::set_melee_special_table_for_crit(const int wpn_skill) {
    MeleeSpecialTable* table = combat->get_melee_special_table(wpn_skill);
    table->set_miss_range(0);
    table->set_dodge_range(0);
    table->set_parry_range(0);
    table->set_block_range(0);
    table->update_crit_chance(1.0);

    assert(table->get_outcome(0, 0.0) == Outcome::CRITICAL);
    assert(table->get_outcome(9999, 0.0) == Outcome::CRITICAL);
}

void TestSpell::set_melee_auto_table_for_hit(const int wpn_skill) {
    WhiteHitTable* table = combat->get_white_hit_table(wpn_skill);
    table->set_miss_range(0);
    table->set_dodge_range(0);
    table->set_parry_range(0);
    table->set_block_range(0);
    table->set_glancing_range(0);
    table->update_crit_chance(0.0);

    assert(table->get_outcome(0, 0.0) == Outcome::HIT);
    assert(table->get_outcome(9999, 0.0) == Outcome::HIT);
}

void TestSpell::set_melee_auto_table_for_crit(const int wpn_skill) {
    WhiteHitTable* table = combat->get_white_hit_table(wpn_skill);
    table->set_miss_range(0);
    table->set_dodge_range(0);
    table->set_parry_range(0);
    table->set_block_range(0);
    table->set_glancing_range(0);
    table->update_crit_chance(1.0);

    assert(table->get_outcome(0, 0.0) == Outcome::CRITICAL);
    assert(table->get_outcome(9999, 0.0) == Outcome::CRITICAL);
}

void TestSpell::given_a_mainhand_weapon_with_100_min_max_dmg() {
    if (equipment->get_db()->get_melee_weapon("Test 100 dmg") == nullptr) {
        Onehand* wpn = new Onehand("Test 100 dmg", WeaponTypes::SWORD, 100, 100, 2.6);
        equipment->get_db()->add_melee_weapon(wpn);
    }

    pchar->get_equipment()->set_mainhand("Test 100 dmg");
    assert(pchar->get_equipment()->get_mainhand()->get_min_dmg() == 100);
    assert(pchar->get_equipment()->get_mainhand()->get_max_dmg() == 100);
}

void TestSpell::given_a_mainhand_weapon_with_3_speed() {
    if (equipment->get_db()->get_melee_weapon("Test 3 Speed") == nullptr) {
        Onehand* wpn = new Onehand("Test 3 Speed", WeaponTypes::SWORD, 100, 100, 3.0);
        equipment->get_db()->add_melee_weapon(wpn);
    }

    pchar->get_equipment()->set_mainhand("Test 3 Speed");
    assert(int(pchar->get_equipment()->get_mainhand()->get_base_weapon_speed()) == 3);
}

void TestSpell::given_a_mainhand_weapon_with_2_speed() {
    if (equipment->get_db()->get_melee_weapon("Test 2 Speed") == nullptr) {
        Onehand* wpn = new Onehand("Test 2 Speed", WeaponTypes::SWORD, 100, 100, 2.0);
        equipment->get_db()->add_melee_weapon(wpn);
    }

    pchar->get_equipment()->set_mainhand("Test 2 Speed");
    assert(int(pchar->get_equipment()->get_mainhand()->get_base_weapon_speed()) == 2);
}

void TestSpell::given_no_mainhand() {
    pchar->get_equipment()->clear_mainhand();
    assert(pchar->get_equipment()->get_mainhand() == nullptr);
}

void TestSpell::given_no_offhand() {
    pchar->get_equipment()->clear_offhand();
    assert(pchar->get_equipment()->get_offhand() == nullptr);
}

void TestSpell::given_an_offhand_weapon_with_100_min_max_dmg() {
    if (equipment->get_db()->get_melee_weapon("Test 100 dmg") == nullptr) {
        Onehand* wpn = new Onehand("Test 100 dmg", WeaponTypes::SWORD, 100, 100, 2.6);
        equipment->get_db()->add_melee_weapon(wpn);
    }

    pchar->get_equipment()->set_offhand("Test 100 dmg");
    assert(pchar->get_equipment()->get_offhand()->get_min_dmg() == 100);
    assert(pchar->get_equipment()->get_offhand()->get_max_dmg() == 100);
}

void TestSpell::given_an_offhand_weapon_with_3_speed() {
    if (equipment->get_db()->get_melee_weapon("Test 3 Speed") == nullptr) {
        Onehand* wpn = new Onehand("Test 3 Speed", WeaponTypes::SWORD, 100, 100, 3.0);
        equipment->get_db()->add_melee_weapon(wpn);
    }

    pchar->get_equipment()->set_offhand("Test 3 Speed");
    assert(int(pchar->get_equipment()->get_offhand()->get_base_weapon_speed()) == 3);
}

void TestSpell::given_an_offhand_weapon_with_2_speed() {
    if (equipment->get_db()->get_melee_weapon("Test 2 Speed") == nullptr) {
        Onehand* wpn = new Onehand("Test 2 Speed", WeaponTypes::SWORD, 100, 100, 2.0);
        equipment->get_db()->add_melee_weapon(wpn);
    }

    pchar->get_equipment()->set_offhand("Test 2 Speed");
    assert(int(pchar->get_equipment()->get_offhand()->get_base_weapon_speed()) == 2);
}

void TestSpell::given_1000_melee_ap() {
    pchar->get_stats()->increase_melee_ap(1000 - pchar->get_stats()->get_melee_ap());
    assert(pchar->get_stats()->get_melee_ap() == 1000);
}

void TestSpell::given_engine_priority_at(const float priority) {
    MainhandMeleeHit* event = new MainhandMeleeHit(pchar->get_spells(), priority, 0);
    engine->set_current_priority(event);
    delete event;
}

void TestSpell::then_damage_dealt_is(const int damage) {
    assert(engine->get_statistics()->get_total_damage() == damage);
}

void TestSpell::then_next_event_is(const QString &name) {
    Event* event = engine->get_queue()->get_next();
    engine->set_current_priority(event);

    assert(event->get_name() == name);

    delete event;
}

void TestSpell::then_next_event_is(const QString &name, const QString &priority) {
    assert(!engine->get_queue()->empty());
    Event* event = engine->get_queue()->get_next();
    engine->set_current_priority(event);

    assert(event->get_name() == name);
    assert(QString::number(event->get_priority(), 'f', 3) == priority);

    delete event;
}
