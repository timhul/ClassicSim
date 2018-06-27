
#include "Test.h"

#include "EncounterStart.h"
#include "EncounterEnd.h"
#include "Human.h"
#include "Dwarf.h"
#include "NightElf.h"
#include "Gnome.h"
#include "Orc.h"
#include "Undead.h"
#include "Tauren.h"
#include "Troll.h"

#include "Warrior.h"
#include "Priest.h"
#include "Rogue.h"
#include "Mage.h"
#include "Druid.h"
#include "Hunter.h"
#include "Warlock.h"
#include "Shaman.h"
#include "Paladin.h"

#include "Character.h"
#include "CharacterStats.h"
#include "Equipment.h"
#include "EquipmentDb.h"
#include "Onehand.h"
#include "Mainhand.h"
#include "Offhand.h"
#include "WhiteHitTable.h"
#include "MeleeSpecialTable.h"
#include "CombatRoll.h"
#include "AttackResult.h"
#include "Random.h"
#include "Mechanics.h"
#include "Target.h"
#include "Talents.h"
#include "Faction.h"

#include "WarriorSpells.h"

#include <assert.h>
#include <QDebug>

#include "TestWarrior.h"


void Test::test_all(void) {
    qDebug() << "test_character_creation";
    test_character_creation();
    qDebug() << "test_equipment_creation";
    test_equipment_creation();
    qDebug() << "test_white_hit_table";
    test_white_hit_table();
    qDebug() << "test_white_hit_table_update";
    test_white_hit_table_update();
    qDebug() << "test_special_hit_table";
    test_special_hit_table();
    qDebug() << "test_mechanics_glancing_rate";
    test_mechanics_glancing_rate();
    qDebug() << "test_mechanics_glancing_dmg_penalty";
    test_mechanics_glancing_dmg_penalty();
    qDebug() << "test_mechanics_dw_white_miss";
    test_mechanics_dw_white_miss();
    qDebug() << "test_mechanics_dodge";
    test_mechanics_dodge();
    qDebug() << "test_combat_roll_creation";
    test_combat_roll_creation();
    qDebug() << "test_random";
    test_random();
    qDebug() << "test_combat_roll_melee_hit_result";
    test_combat_roll_melee_hit_result();
    qDebug() << "test_queue";
    test_queue();
    qDebug() << "test_warrior";
    test_warrior();
}

void add_frostbite(EquipmentDb* db) {
    Onehand* wpn = new Onehand("Frostbite", WeaponTypes::AXE, 80, 150, 2.7);
    db->add_melee_weapon(wpn);
}

void Test::test_queue(void) {
    Engine* engine = new Engine();
    Equipment* equipment = new Equipment();
    add_frostbite(equipment->get_db());
    equipment->set_mainhand("Frostbite");
    equipment->set_offhand("Frostbite");
    Race* race = new Orc();
    Target* target = new Target(63);
    CombatRoll* combat = new CombatRoll(target);
    Faction* faction = new Faction();
    Warrior* pchar = new Warrior(race, engine, equipment, combat, faction);
    pchar->set_clvl(60);
    EncounterStart* start_event = new EncounterStart(pchar);
    EncounterEnd* end_event = new EncounterEnd(engine, pchar);

    engine->add_event(end_event);
    engine->add_event(start_event);
    engine->run();
    engine->dump();

    delete faction;
    delete combat;
    delete target;
    delete equipment;
    delete pchar;
    delete race;
    delete engine;
}

void Test::test_random(void) {
    Random* random = new Random(0, 9999);

    for (int i = 0; i < 10; ++i) {
        qDebug() << "Random rolling " << random->get_roll();
    }

    delete random;
}

void Test::test_combat_roll_melee_hit_result(void) {
    Target* target = new Target(63);
    Engine* engine = new Engine();
    Equipment* equipment = new Equipment();
    add_frostbite(equipment->get_db());
    Race* race = new Orc();
    CombatRoll* combat = new CombatRoll(target);
    Faction* faction = new Faction();
    Warrior* pchar = new Warrior(race, engine, equipment, combat, faction);
    combat->set_character(pchar);

    for(int i = 0; i < 30; ++i) {
        combat->get_melee_hit_result(300);
    }

    delete faction;
    delete target;
    delete engine;
    delete equipment;
    delete race;
    delete pchar;
    delete combat;
}

void Test::test_combat_roll_creation(void) {
    Target* target = new Target(63);
    Engine* engine = new Engine();
    Equipment* equipment = new Equipment();
    add_frostbite(equipment->get_db());
    Race* race = new Orc();
    CombatRoll* combat = new CombatRoll(target);
    Faction* faction = new Faction();
    Warrior* pchar = new Warrior(race, engine, equipment, combat, faction);
    combat->set_character(dynamic_cast<Character*>(pchar));

    combat->get_white_hit_table(300);
    combat->get_white_hit_table(300);
    combat->get_white_hit_table(315);
    combat->get_white_hit_table(315);
    combat->get_white_hit_table(300);

    delete faction;
    delete target;
    delete engine;
    delete equipment;
    delete race;
    delete pchar;
    delete combat;
}

void Test::test_mechanics_dodge(void) {
    Target* target = new Target(63);
    Mechanics* mechanics = new Mechanics(target);

    assert(fabs(0.05 - mechanics->get_dodge_chance(300)) < 0.001);
    assert(fabs(0.05 - mechanics->get_dodge_chance(315)) < 0.001);

    target->set_lvl(60);
    assert(fabs(0.044 - mechanics->get_dodge_chance(315)) < 0.001);

    delete mechanics;
    delete target;
}

void Test::test_mechanics_glancing_rate(void) {
    Target* target = new Target(63);
    Mechanics* mechanics = new Mechanics(target);

    assert(fabs(6.3 - mechanics->get_glancing_blow_chance(1)) < 0.001);

    assert(fabs(0.4 -  mechanics->get_glancing_blow_chance(60)) < 0.001);

    target->set_lvl(62);
    assert(fabs(0.3 - mechanics->get_glancing_blow_chance(60)) < 0.001);

    target->set_lvl(61);
    assert(fabs(0.2 - mechanics->get_glancing_blow_chance(60)) < 0.001);

    target->set_lvl(60);
    assert(fabs(0.1 - mechanics->get_glancing_blow_chance(60)) < 0.001);

    target->set_lvl(59);
    assert(fabs(0.0 - mechanics->get_glancing_blow_chance(60)) < 0.001);

    delete mechanics;
    delete target;
}

void Test::test_mechanics_glancing_dmg_penalty(void) {
    Target* target = new Target(63);
    Mechanics* mechanics = new Mechanics(target);

    assert(fabs(0.7 - mechanics->get_glancing_blow_dmg_penalty(5)) < 0.001);

    assert(fabs(0.7 - mechanics->get_glancing_blow_dmg_penalty(300)) < 0.001);
    assert(fabs(0.85 - mechanics->get_glancing_blow_dmg_penalty(305)) < 0.001);
    assert(fabs(1.0 - mechanics->get_glancing_blow_dmg_penalty(310)) < 0.001);
    assert(fabs(1.0 - mechanics->get_glancing_blow_dmg_penalty(10000)) < 0.001);

    delete mechanics;
    delete target;
}

void Test::test_mechanics_dw_white_miss(void) {
    Target* target = new Target(63);
    Mechanics* mechanics = new Mechanics(target);

    assert(fabs(0.28 - mechanics->get_dw_white_miss_chance(300)) < 0.001);
    assert(fabs(0.24 - mechanics->get_dw_white_miss_chance(315)) < 0.001);

    target->set_lvl(62);
    assert(fabs(0.25 - mechanics->get_dw_white_miss_chance(300)) < 0.001);

    target->set_lvl(61);
    assert(fabs(0.245 - mechanics->get_dw_white_miss_chance(300)) < 0.001);

    target->set_lvl(60);
    assert(fabs(0.24 - mechanics->get_dw_white_miss_chance(300)) < 0.001);

    delete mechanics;
    delete target;
}

void Test::test_white_hit_table(void) {
   WhiteHitTable* table = new WhiteHitTable(300, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
   assert(table->get_outcome(0, 0.0) == AttackResult::HIT);
   assert(table->get_outcome(9999, 0.0) == AttackResult::HIT);
   delete table;

   table = new WhiteHitTable(300, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001);
   assert(table->get_outcome(0, 0.0) == AttackResult::MISS);
   assert(table->get_outcome(1, 0.0) == AttackResult::DODGE);
   assert(table->get_outcome(2, 0.0) == AttackResult::PARRY);
   assert(table->get_outcome(3, 0.0) == AttackResult::GLANCING);
   assert(table->get_outcome(4, 0.0) == AttackResult::BLOCK);
   assert(table->get_outcome(5, 0.0) == AttackResult::CRITICAL);
   assert(table->get_outcome(6, 0.0) == AttackResult::HIT);
   assert(table->get_outcome(9999, 0.0) == AttackResult::HIT);
   assert(table->get_outcome(6, 1.0) == AttackResult::CRITICAL);
   delete table;
}

void Test::test_white_hit_table_update(void) {
    Target* target = new Target(63);
    Engine* engine = new Engine();
    Equipment* equipment = new Equipment();
    add_frostbite(equipment->get_db());
    Race* race = new Orc();
    CombatRoll* combat = new CombatRoll(target);
    Faction* faction = new Faction();
    Warrior* pchar = new Warrior(race, engine, equipment, combat, faction);
    combat->set_character(dynamic_cast<Character*>(pchar));

    WhiteHitTable* table = combat->get_white_hit_table(300);

    assert(table->get_outcome(0, 0.0) == AttackResult::MISS);
    assert(table->get_outcome(2799, 0.0) == AttackResult::MISS);
    assert(table->get_outcome(2800, 0.0) == AttackResult::DODGE);
    assert(table->get_outcome(3299, 0.0) == AttackResult::DODGE);
    assert(table->get_outcome(3300, 0.0) == AttackResult::GLANCING);
    assert(table->get_outcome(7299, 0.0) == AttackResult::GLANCING);
    assert(table->get_outcome(7300, 0.0) == AttackResult::CRITICAL);
    // TODO: This will fail when changing base agility or agi needed per crit.
    assert(table->get_outcome(7984, 0.0) == AttackResult::CRITICAL);
    assert(table->get_outcome(7985, 0.0) == AttackResult::HIT);

    pchar->get_stats()->increase_crit(0.0001);
    assert(table->get_outcome(7985, 0.0) == AttackResult::CRITICAL);
    assert(table->get_outcome(7986, 0.0) == AttackResult::HIT);

    pchar->get_stats()->increase_crit(0.9999);
    assert(table->get_outcome(7986, 0.0) == AttackResult::CRITICAL);
    assert(table->get_outcome(9999, 0.0) == AttackResult::CRITICAL);

    delete faction;
    delete target;
    delete engine;
    delete equipment;
    delete race;
    delete pchar;
    delete combat;
}

void Test::test_special_hit_table(void) {
    Random* random = new Random(0, 9999);
    MeleeSpecialTable* table = new MeleeSpecialTable(random, 300, 0.0, 0.0, 0.0, 0.0, 0.0);
    assert(table->get_outcome(0, 0.0) == AttackResult::HIT);
    delete table;

    table = new MeleeSpecialTable(random, 300, 0.0001, 0.0001, 0.0001, 0.0001, 1.0);
    assert(table->get_outcome(0, 0.0) == AttackResult::MISS);
    assert(table->get_outcome(1, 0.0) == AttackResult::DODGE);
    assert(table->get_outcome(2, 0.0) == AttackResult::PARRY);
    assert(table->get_outcome(3, 0.0) == AttackResult::BLOCK_CRITICAL);
    assert(table->get_outcome(4, 0.0) == AttackResult::CRITICAL);
    assert(table->get_outcome(9999, 0.0) == AttackResult::CRITICAL);
    delete table;
    delete random;
}

void Test::test_equipment_creation(void) {
    Equipment* equipment = new Equipment();
    add_frostbite(equipment->get_db());
    equipment->set_mainhand("Frostbite");
    Weapon* mh = equipment->get_mainhand();

    assert(mh->get_name() == "Frostbite");
    assert(mh->get_weapon_type() == WeaponTypes::AXE);
    assert(mh->get_min_dmg() == 80);
    assert(mh->get_max_dmg() == 150);
    assert(mh->get_base_weapon_speed() - 2.7 < 0.01);

    delete equipment;
}


void Test::test_character_creation(void) {
    Engine* engine = new Engine();
    Equipment* equipment = new Equipment();
    Target* target = new Target(63);
    CombatRoll* combat = new CombatRoll(target);
    Faction* faction = new Faction();

    Race* race = new Human();
    // TODO: Add assertions
    delete race;

    race = new Dwarf();
    // TODO: Add assertions
    delete race;

    race = new NightElf();
    // TODO: Add assertions
    delete race;

    race = new Gnome();
    // TODO: Add assertions
    delete race;

    race = new Orc();
    // TODO: Add assertions
    delete race;

    race = new Undead();
    // TODO: Add assertions
    delete race;

    race = new Tauren();
    // TODO: Add assertions
    delete race;

    race = new Troll();
    // TODO: Add assertions

    Priest* priest = new Priest(race, engine, equipment, combat, faction);
    // TODO: Add assertions
    delete priest;

    Rogue* rogue = new Rogue(race, engine, equipment, combat, faction);
    // TODO: Add assertions
    delete rogue;

    Mage* mage = new Mage(race, engine, equipment, combat, faction);
    // TODO: Add assertions
    delete mage;

    Druid* druid = new Druid(race, engine, equipment, combat, faction);
    // TODO: Add assertions
    delete druid;

    Hunter* hunter = new Hunter(race, engine, equipment, combat, faction);
    // TODO: Add assertions
    delete hunter;

    Warlock* warlock = new Warlock(race, engine, equipment, combat, faction);
    // TODO: Add assertions
    delete warlock;

    Shaman* shaman = new Shaman(race, engine, equipment, combat, faction);
    // TODO: Add assertions
    delete shaman;

    Paladin* paladin = new Paladin(race, engine, equipment, combat, faction);
    paladin->set_clvl(60);
    assert(paladin->get_clvl() == 60);
    // TODO: Add assertions
    delete paladin;

    delete faction;
    delete target;
    delete combat;
    delete race;
    delete engine;
    delete equipment;
}

void Test::test_warrior() {
    TestWarrior().test_all();
}
