
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
#include "Equipment.h"
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

#include <assert.h>
#include <QDebug>


void Test::test_all(void) {
    qDebug() << "test_character_creation";
    test_character_creation();
    qDebug() << "test_equipment_creation";
    test_equipment_creation();
    qDebug() << "test_white_hit_table";
    test_white_hit_table();
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
}

void Test::test_queue(void) {
    Engine* engine = new Engine();
    Equipment* equipment = new Equipment();
    Random* mh_dmg_range = new Random(80, 150);
    Mainhand* mainhand = new Mainhand("Frostbite", mh_dmg_range, 0, 80, 150, 2.7, 0.0);
    equipment->set_mainhand(mainhand);
    Random* oh_dmg_range = new Random(80, 150);
    Offhand* offhand = new Offhand("Frostbite", oh_dmg_range, 0, 80, 150, 2.7, 0.0);
    equipment->set_offhand(offhand);
    Race* race = new Orc();
    Target* target = new Target(63);
    CombatRoll* combat = new CombatRoll(target);
    Warrior* pchar = new Warrior(race, engine, equipment, combat);
    pchar->set_clvl(60);
    EncounterStart* start_event = new EncounterStart(pchar);
    EncounterEnd* end_event = new EncounterEnd(engine, pchar);

    engine->add_event(end_event);
    engine->add_event(start_event);
    engine->run();
    engine->dump();

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
    Race* race = new Orc();
    CombatRoll* combat = new CombatRoll(target);
    Warrior* pchar = new Warrior(race, engine, equipment, combat);
    combat->set_character(pchar);

    AttackResult* result = combat->get_melee_hit_result(300);

    for(int i = 0; i < 30; ++i) {
        delete result;
        result = combat->get_melee_hit_result(300);
    }
    delete result;

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
    Race* race = new Orc();
    CombatRoll* combat = new CombatRoll(target);
    Warrior* pchar = new Warrior(race, engine, equipment, combat);
    combat->set_character(dynamic_cast<Character*>(pchar));

    combat->get_white_hit_table(300);
    combat->get_white_hit_table(300);
    combat->get_white_hit_table(315);
    combat->get_white_hit_table(315);
    combat->get_white_hit_table(300);

    delete target;
    delete engine;
    delete equipment;
    delete race;
    delete pchar;
    delete combat;
}

void Test::test_mechanics_dodge(void) {
    Mechanics* mechanics = new Mechanics(63, 0);

    assert(fabs(0.05 - mechanics->get_dodge_chance(300)) < 0.001);
    assert(fabs(0.05 - mechanics->get_dodge_chance(315)) < 0.001);

    mechanics->set_tlvl(60);
    assert(fabs(0.044 - mechanics->get_dodge_chance(315)) < 0.001);

    delete mechanics;
}

void Test::test_mechanics_glancing_rate(void) {
    Mechanics* mechanics = new Mechanics(63, 0);

    assert(fabs(6.3 - mechanics->get_glancing_blow_chance(1)) < 0.001);

    assert(fabs(0.4 -  mechanics->get_glancing_blow_chance(60)) < 0.001);

    mechanics->set_tlvl(62);
    assert(fabs(0.3 - mechanics->get_glancing_blow_chance(60)) < 0.001);

    mechanics->set_tlvl(61);
    assert(fabs(0.2 - mechanics->get_glancing_blow_chance(60)) < 0.001);

    mechanics->set_tlvl(60);
    assert(fabs(0.1 - mechanics->get_glancing_blow_chance(60)) < 0.001);

    mechanics->set_tlvl(59);
    assert(fabs(0.0 - mechanics->get_glancing_blow_chance(60)) < 0.001);

    delete mechanics;
}

void Test::test_mechanics_glancing_dmg_penalty(void) {
    Mechanics* mechanics = new Mechanics(63, 0);

    assert(fabs(0.7 - mechanics->get_glancing_blow_dmg_penalty(5)) < 0.001);

    assert(fabs(0.7 - mechanics->get_glancing_blow_dmg_penalty(300)) < 0.001);
    assert(fabs(0.85 - mechanics->get_glancing_blow_dmg_penalty(305)) < 0.001);
    assert(fabs(1.0 - mechanics->get_glancing_blow_dmg_penalty(310)) < 0.001);
    assert(fabs(1.0 - mechanics->get_glancing_blow_dmg_penalty(10000)) < 0.001);

    delete mechanics;
}

void Test::test_mechanics_dw_white_miss(void) {
    Mechanics* mechanics = new Mechanics(63, 0);

    assert(fabs(0.28 - mechanics->get_dw_white_miss_chance(300)) < 0.001);
    assert(fabs(0.24 - mechanics->get_dw_white_miss_chance(315)) < 0.001);

    mechanics->set_tlvl(62);
    assert(fabs(0.25 - mechanics->get_dw_white_miss_chance(300)) < 0.001);

    mechanics->set_tlvl(61);
    assert(fabs(0.245 - mechanics->get_dw_white_miss_chance(300)) < 0.001);

    mechanics->set_tlvl(60);
    assert(fabs(0.24 - mechanics->get_dw_white_miss_chance(300)) < 0.001);

    delete mechanics;
}

void Test::test_white_hit_table(void) {
   WhiteHitTable* table = new WhiteHitTable(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
   assert(table->get_outcome(0, 0.0) == Outcome::HIT);
   assert(table->get_outcome(9999, 0.0) == Outcome::HIT);
   delete table;

   table = new WhiteHitTable(0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001);
   assert(table->get_outcome(0, 0.0) == Outcome::MISS);
   assert(table->get_outcome(1, 0.0) == Outcome::DODGE);
   assert(table->get_outcome(2, 0.0) == Outcome::PARRY);
   assert(table->get_outcome(3, 0.0) == Outcome::GLANCING);
   assert(table->get_outcome(4, 0.0) == Outcome::BLOCK);
   assert(table->get_outcome(5, 0.0) == Outcome::CRITICAL);
   assert(table->get_outcome(6, 0.0) == Outcome::HIT);
   assert(table->get_outcome(9999, 0.0) == Outcome::HIT);
   assert(table->get_outcome(6, 1.0) == Outcome::CRITICAL);
   delete table;
}

void Test::test_special_hit_table(void) {
    Random* random = new Random(0, 9999);
    MeleeSpecialTable* table = new MeleeSpecialTable(random, 0.0, 0.0, 0.0, 0.0, 0.0);
    assert(table->get_outcome(0, 0.0) == Outcome::HIT);
    delete table;

    table = new MeleeSpecialTable(random, 0.0001, 0.0001, 0.0001, 0.0001, 1.0);
    assert(table->get_outcome(0, 0.0) == Outcome::MISS);
    assert(table->get_outcome(1, 0.0) == Outcome::DODGE);
    assert(table->get_outcome(2, 0.0) == Outcome::PARRY);
    assert(table->get_outcome(3, 0.0) == Outcome::BLOCK_CRITICAL);
    assert(table->get_outcome(4, 0.0) == Outcome::CRITICAL);
    assert(table->get_outcome(9999, 0.0) == Outcome::CRITICAL);
    delete table;
    delete random;
}

void Test::test_equipment_creation(void) {
    Equipment* equipment = new Equipment();

    Random* mh_dmg_range = new Random(80, 150);
    Mainhand* mainhand = new Mainhand("Frostbite", mh_dmg_range, 0, 80, 150, 2.7, 0.0);
    assert(mainhand->get_name() == "Frostbite");
    assert(mainhand->get_weapon_type() == 0);
    assert(mainhand->get_min_dmg() == 80);
    assert(mainhand->get_max_dmg() == 150);
    assert(mainhand->get_base_weapon_speed() - 2.7 < 0.01);
    assert(mainhand->get_weapon_proc_rate() == 0.0);

    equipment->set_mainhand(mainhand);
    MeleeWeapon* mh = equipment->get_mainhand();

    assert(mh->get_name() == "Frostbite");
    assert(mh->get_weapon_type() == 0);
    assert(mh->get_min_dmg() == 80);
    assert(mh->get_max_dmg() == 150);
    assert(mh->get_base_weapon_speed() - 2.7 < 0.01);
    assert(mh->get_weapon_proc_rate() == 0.0);

    delete equipment;
}


void Test::test_character_creation(void) {
    Engine* engine = new Engine();
    Equipment* equipment = new Equipment();
    Target* target = new Target(63);
    CombatRoll* combat = new CombatRoll(target);

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

    Warrior* warr = new Warrior(race, engine, equipment, combat);
    // TODO: Add assertions
    delete warr;

    Priest* priest = new Priest(race, engine, equipment, combat);
    // TODO: Add assertions
    delete priest;

    Rogue* rogue = new Rogue(race, engine, equipment, combat);
    // TODO: Add assertions
    delete rogue;

    Mage* mage = new Mage(race, engine, equipment, combat);
    // TODO: Add assertions
    delete mage;

    Druid* druid = new Druid(race, engine, equipment, combat);
    // TODO: Add assertions
    delete druid;

    Hunter* hunter = new Hunter(race, engine, equipment, combat);
    // TODO: Add assertions
    delete hunter;

    Warlock* warlock = new Warlock(race, engine, equipment, combat);
    // TODO: Add assertions
    delete warlock;

    Shaman* shaman = new Shaman(race, engine, equipment, combat);
    // TODO: Add assertions
    delete shaman;

    Paladin* paladin = new Paladin(race, engine, equipment, combat);
    // TODO: Add assertions
    delete paladin;

    race = new Orc();
    warr = new Warrior(race, engine, equipment, combat);
    assert(warr->get_name() == "Warrior");
    assert(warr->get_race()->get_name() == "Orc");
    // TODO: Assert stats

    warr->set_clvl(60);
    assert(warr->get_clvl() == 60);
    delete target;
    delete combat;
    delete race;
    delete warr;
    delete engine;
    delete equipment;
}
