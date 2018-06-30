
#include "TestSpell.h"

#include "Character.h"
#include "CharacterStats.h"
#include "ClassStatistics.h"
#include "CombatRoll.h"
#include "Engine.h"
#include "Equipment.h"
#include "EquipmentDb.h"
#include "Faction.h"
#include "Item.h"
#include "MainhandMeleeHit.h"
#include "MeleeSpecialTable.h"
#include "Onehand.h"
#include "Orc.h"
#include "Stats.h"
#include "Target.h"
#include "WhiteHitTable.h"

TestSpell::TestSpell(QString spell_under_test) :
    equipment(nullptr),
    spell_under_test(spell_under_test)
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
    faction = new Faction();
}

void TestSpell::tear_down_general() {
    // not thread safe
    delete engine;
    delete combat;
    delete target;
    delete race;
    delete faction;
}

void TestSpell::given_no_previous_damage_dealt() {
    then_damage_dealt_is(0);
}

void TestSpell::given_a_guaranteed_white_hit() {
    set_melee_auto_table_for_hit(pchar->get_mh_wpn_skill());
    set_melee_auto_table_for_hit(pchar->get_oh_wpn_skill());
}

void TestSpell::given_a_guaranteed_white_glancing_blow() {
    set_melee_auto_table_for_glancing(pchar->get_mh_wpn_skill());
    set_melee_auto_table_for_glancing(pchar->get_oh_wpn_skill());
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
    table->update_crit_chance(0.0);
    table->update_miss_chance(0.0);
    table->update_dodge_chance(0.0);
    table->update_parry_chance(0.0);
    table->update_block_chance(0.0);

    assert(table->get_outcome(0, 0.0) == AttackResult::HIT);
    assert(table->get_outcome(9999, 0.0) == AttackResult::HIT);

}

void TestSpell::set_melee_special_table_for_crit(const int wpn_skill) {
    MeleeSpecialTable* table = combat->get_melee_special_table(wpn_skill);
    table->update_crit_chance(1.0);
    table->update_miss_chance(0.0);
    table->update_dodge_chance(0.0);
    table->update_parry_chance(0.0);
    table->update_block_chance(0.0);

    assert(table->get_outcome(0, 0.0) == AttackResult::CRITICAL);
    assert(table->get_outcome(9999, 0.0) == AttackResult::CRITICAL);
}

void TestSpell::set_melee_auto_table_for_hit(const int wpn_skill) {
    WhiteHitTable* table = combat->get_white_hit_table(wpn_skill);
    table->update_miss_chance(0.0);
    table->update_dodge_chance(0.0);
    table->update_parry_chance(0.0);
    table->update_block_chance(0.0);
    table->update_glancing_chance(0.0);
    table->update_crit_chance(0.0);

    assert(table->get_outcome(0, 0.0) == AttackResult::HIT);
    assert(table->get_outcome(9999, 0.0) == AttackResult::HIT);
}

void TestSpell::set_melee_auto_table_for_glancing(const int wpn_skill) {
    WhiteHitTable* table = combat->get_white_hit_table(wpn_skill);
    table->update_miss_chance(0.0);
    table->update_dodge_chance(0.0);
    table->update_parry_chance(0.0);
    table->update_block_chance(0.0);
    table->update_glancing_chance(1.0);
    table->update_crit_chance(0.0);

    assert(table->get_outcome(0, 0.0) == AttackResult::GLANCING);
    assert(table->get_outcome(9999, 0.0) == AttackResult::GLANCING);
}

void TestSpell::set_melee_auto_table_for_crit(const int wpn_skill) {
    WhiteHitTable* table = combat->get_white_hit_table(wpn_skill);
    table->update_miss_chance(0.0);
    table->update_dodge_chance(0.0);
    table->update_parry_chance(0.0);
    table->update_block_chance(0.0);
    table->update_glancing_chance(0.0);
    table->update_crit_chance(1.0);

    assert(table->get_outcome(0, 0.0) == AttackResult::CRITICAL);
    assert(table->get_outcome(9999, 0.0) == AttackResult::CRITICAL);
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

void TestSpell::given_300_weapon_skill_mh() {
    assert(pchar->get_mh_wpn_skill() == 300);
}

void TestSpell::given_305_weapon_skill_mh() {
    if (equipment->get_db()->get_ring("Test +5 Sword Skill") == nullptr) {
        QMap<QString, QString> info = {{"slot", "RING"}};
        QVector<QPair<QString, QString>> stats;
        stats.append(QPair<QString, QString>("SWORD_SKILL", "5"));

        Item* ring = new Item("Test +5 Sword Skill", stats, info);
        equipment->get_db()->add_ring(ring);
    }

    pchar->get_equipment()->set_ring1("Test +5 Sword Skill");

    assert(pchar->get_mh_wpn_skill() == 305);
}

void TestSpell::given_310_weapon_skill_mh() {
    if (equipment->get_db()->get_ring("Test +10 Sword Skill") == nullptr) {
        QMap<QString, QString> info = {{"slot", "RING"}};
        QVector<QPair<QString, QString>> stats;
        stats.append(QPair<QString, QString>("SWORD_SKILL", "10"));

        Item* ring = new Item("Test +10 Sword Skill", stats, info);
        equipment->get_db()->add_ring(ring);
    }

    pchar->get_equipment()->set_ring1("Test +10 Sword Skill");

    assert(pchar->get_mh_wpn_skill() == 310);
}

void TestSpell::given_315_weapon_skill_mh() {
    if (equipment->get_db()->get_ring("Test +15 Sword Skill") == nullptr) {
        QMap<QString, QString> info = {{"slot", "RING"}};
        QVector<QPair<QString, QString>> stats;
        stats.append(QPair<QString, QString>("SWORD_SKILL", "15"));

        Item* ring = new Item("Test +15 Sword Skill", stats, info);
        equipment->get_db()->add_ring(ring);
    }

    pchar->get_equipment()->set_ring1("Test +15 Sword Skill");

    assert(pchar->get_mh_wpn_skill() == 315);
}

void TestSpell::given_300_weapon_skill_oh() {
    assert(pchar->get_oh_wpn_skill() == 300);
}

void TestSpell::given_305_weapon_skill_oh() {
    if (equipment->get_db()->get_ring("Test +5 Sword Skill") == nullptr) {
        QMap<QString, QString> info = {{"slot", "RING"}};
        QVector<QPair<QString, QString>> stats;
        stats.append(QPair<QString, QString>("SWORD_SKILL", "5"));

        Item* ring = new Item("Test +5 Sword Skill", stats, info);
        equipment->get_db()->add_ring(ring);
    }

    pchar->get_equipment()->set_ring1("Test +5 Sword Skill");

    assert(pchar->get_oh_wpn_skill() == 305);
}

void TestSpell::given_310_weapon_skill_oh() {
    if (equipment->get_db()->get_ring("Test +10 Sword Skill") == nullptr) {
        QMap<QString, QString> info = {{"slot", "RING"}};
        QVector<QPair<QString, QString>> stats;
        stats.append(QPair<QString, QString>("SWORD_SKILL", "10"));

        Item* ring = new Item("Test +10 Sword Skill", stats, info);
        equipment->get_db()->add_ring(ring);
    }

    pchar->get_equipment()->set_ring1("Test +10 Sword Skill");

    assert(pchar->get_oh_wpn_skill() == 310);
}

void TestSpell::given_315_weapon_skill_oh() {
    if (equipment->get_db()->get_ring("Test +15 Sword Skill") == nullptr) {
        QMap<QString, QString> info = {{"slot", "RING"}};
        QVector<QPair<QString, QString>> stats;
        stats.append(QPair<QString, QString>("SWORD_SKILL", "15"));

        Item* ring = new Item("Test +15 Sword Skill", stats, info);
        equipment->get_db()->add_ring(ring);
    }

    pchar->get_equipment()->set_ring1("Test +15 Sword Skill");

    assert(pchar->get_oh_wpn_skill() == 315);
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
    if (damage != pchar->get_statistics()->get_total_damage_dealt())
        qDebug() << spell_under_test << "then_damage_dealt_is() assertion failed, expected"
                 << damage << "got" << pchar->get_statistics()->get_total_damage_dealt();
    assert(pchar->get_statistics()->get_total_damage_dealt() == damage);
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
