
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

#include <iostream>
#include <assert.h>


void Test::test_all(void) {
    std::cout << "test_character_creation\n";
    test_character_creation();
    std::cout << "test_equipment_creation\n";
    test_equipment_creation();
    std::cout << "test_white_hit_table\n";
    test_white_hit_table();
    std::cout << "test_special_hit_table\n";
    test_special_hit_table();
    std::cout << "test_mechanics_glancing_rate\n";
    test_mechanics_glancing_rate();
    std::cout << "test_mechanics_glancing_dmg_penalty\n";
    test_mechanics_glancing_dmg_penalty();
    std::cout << "test_mechanics_dw_white_miss\n";
    test_mechanics_dw_white_miss();
    std::cout << "test_mechanics_dodge\n";
    test_mechanics_dodge();
    std::cout << "test_combat_roll_creation\n";
    test_combat_roll_creation();
    std::cout << "test_random\n";
    test_random();
    std::cout << "test_combat_roll_melee_hit_result\n";
    test_combat_roll_melee_hit_result();
    std::cout << "test_queue\n";
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
    Random* random = new Random(0, 9999);
    CombatRoll* combat = new CombatRoll(target, random);
    Warrior* pchar = new Warrior(race, engine, equipment, combat);
    pchar->set_clvl(60);
    combat->set_character(pchar);
    EncounterStart* start_event = new EncounterStart(pchar);
    EncounterEnd* end_event = new EncounterEnd(engine);

    engine->add_event(end_event);
    engine->add_event(start_event);
    engine->run();

    delete target;
    delete random;
    delete equipment;
    delete pchar;
    delete race;
    delete engine;
}

void Test::test_random(void) {
    Random* random = new Random(0, 9999);

    for (int i = 0; i < 10; ++i) {
        std::cout << "Random rolling " << random->get_roll() << "\n";
    }

    delete random;
}

void Test::test_combat_roll_melee_hit_result(void) {
    Target* target = new Target(63);
    Engine* engine = new Engine();
    Equipment* equipment = new Equipment();
    Race* race = new Orc();
    Random* random = new Random(0, 9999);
    CombatRoll* combat = new CombatRoll(target, random);
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
    delete random;
    delete combat;
}

void Test::test_combat_roll_creation(void) {
    Target* target = new Target(63);
    Engine* engine = new Engine();
    Equipment* equipment = new Equipment();
    Race* race = new Orc();
    Random* random = new Random(0, 9999);
    CombatRoll* combat = new CombatRoll(target, random);
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
    delete random;
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
   WhiteHitTable* table = new WhiteHitTable(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0);
   assert(table->get_outcome(0) == Outcome::HIT);
   assert(table->get_outcome(9999) == Outcome::HIT);
   delete table;

   table = new WhiteHitTable(0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0);
   assert(table->get_outcome(0) == Outcome::MISS);
   assert(table->get_outcome(1) == Outcome::DODGE);
   assert(table->get_outcome(2) == Outcome::PARRY);
   assert(table->get_outcome(3) == Outcome::GLANCING);
   assert(table->get_outcome(4) == Outcome::BLOCK);
   assert(table->get_outcome(5) == Outcome::CRITICAL);
   assert(table->get_outcome(6) == Outcome::HIT);
   assert(table->get_outcome(9999) == Outcome::HIT);
   delete table;
}

void Test::test_special_hit_table(void) {
    Random* random = new Random(0, 9999);
    MeleeSpecialTable* table = new MeleeSpecialTable(random, 0.0, 0.0, 0.0, 0.0, 0.0, 0);
    assert(table->get_outcome(0) == Outcome::HIT);
    delete table;

    table = new MeleeSpecialTable(random, 0.0001, 0.0001, 0.0001, 0.0001, 1.0, 0);
    assert(table->get_outcome(0) == Outcome::MISS);
    assert(table->get_outcome(1) == Outcome::DODGE);
    assert(table->get_outcome(2) == Outcome::PARRY);
    assert(table->get_outcome(3) == Outcome::BLOCK_CRITICAL);
    assert(table->get_outcome(4) == Outcome::CRITICAL);
    assert(table->get_outcome(9999) == Outcome::CRITICAL);
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
    Random* random = new Random(0, 9999);
    CombatRoll* combat = new CombatRoll(target, random);

    Race* race = new Human();
    std::cout << "Name: " << race->get_name() << "\n";
    std::cout << "STR " << race->get_base_strength() << "\n";
    std::cout << "AGI " << race->get_base_agility() << "\n";
    std::cout << "STA " << race->get_base_stamina() << "\n";
    std::cout << "INT " << race->get_base_intellect() << "\n";
    std::cout << "SPI " << race->get_base_spirit() << "\n";
    delete race;

    race = new Dwarf();
    std::cout << "Name: " << race->get_name() << "\n";
    std::cout << "STR " << race->get_base_strength() << "\n";
    std::cout << "AGI " << race->get_base_agility() << "\n";
    std::cout << "STA " << race->get_base_stamina() << "\n";
    std::cout << "INT " << race->get_base_intellect() << "\n";
    std::cout << "SPI " << race->get_base_spirit() << "\n";
    delete race;

    race = new NightElf();
    std::cout << "Name: " << race->get_name() << "\n";
    std::cout << "STR " << race->get_base_strength() << "\n";
    std::cout << "AGI " << race->get_base_agility() << "\n";
    std::cout << "STA " << race->get_base_stamina() << "\n";
    std::cout << "INT " << race->get_base_intellect() << "\n";
    std::cout << "SPI " << race->get_base_spirit() << "\n";
    delete race;

    race = new Gnome();
    std::cout << "Name: " << race->get_name() << "\n";
    std::cout << "STR " << race->get_base_strength() << "\n";
    std::cout << "AGI " << race->get_base_agility() << "\n";
    std::cout << "STA " << race->get_base_stamina() << "\n";
    std::cout << "INT " << race->get_base_intellect() << "\n";
    std::cout << "SPI " << race->get_base_spirit() << "\n";
    delete race;

    race = new Orc();
    std::cout << "Name: " << race->get_name() << "\n";
    std::cout << "STR " << race->get_base_strength() << "\n";
    std::cout << "AGI " << race->get_base_agility() << "\n";
    std::cout << "STA " << race->get_base_stamina() << "\n";
    std::cout << "INT " << race->get_base_intellect() << "\n";
    std::cout << "SPI " << race->get_base_spirit() << "\n";
    delete race;

    race = new Undead();
    std::cout << "Name: " << race->get_name() << "\n";
    std::cout << "STR " << race->get_base_strength() << "\n";
    std::cout << "AGI " << race->get_base_agility() << "\n";
    std::cout << "STA " << race->get_base_stamina() << "\n";
    std::cout << "INT " << race->get_base_intellect() << "\n";
    std::cout << "SPI " << race->get_base_spirit() << "\n";
    delete race;

    race = new Tauren();
    std::cout << "Name: " << race->get_name() << "\n";
    std::cout << "STR " << race->get_base_strength() << "\n";
    std::cout << "AGI " << race->get_base_agility() << "\n";
    std::cout << "STA " << race->get_base_stamina() << "\n";
    std::cout << "INT " << race->get_base_intellect() << "\n";
    std::cout << "SPI " << race->get_base_spirit() << "\n";
    delete race;

    race = new Troll();
    std::cout << "Name: " << race->get_name() << "\n";
    std::cout << "STR " << race->get_base_strength() << "\n";
    std::cout << "AGI " << race->get_base_agility() << "\n";
    std::cout << "STA " << race->get_base_stamina() << "\n";
    std::cout << "INT " << race->get_base_intellect() << "\n";
    std::cout << "SPI " << race->get_base_spirit() << "\n";

    Warrior* warr = new Warrior(race, engine, equipment, combat);
    std::cout << "Name: " << warr->get_name() << "\n";
    std::cout << "STR Mod " << warr->get_strength_modifier() << "\n";
    std::cout << "AGI Mod " << warr->get_agility_modifier() << "\n";
    std::cout << "STA Mod " << warr->get_stamina_modifier() << "\n";
    std::cout << "INT Mod " << warr->get_intellect_modifier() << "\n";
    std::cout << "SPI Mod " << warr->get_spirit_modifier()<< "\n";
    delete warr;

    Priest* priest = new Priest(race, engine, equipment, combat);
    std::cout << "Name: " << priest->get_name() << "\n";
    std::cout << "STR Mod " << priest->get_strength_modifier() << "\n";
    std::cout << "AGI Mod " << priest->get_agility_modifier() << "\n";
    std::cout << "STA Mod " << priest->get_stamina_modifier() << "\n";
    std::cout << "INT Mod " << priest->get_intellect_modifier() << "\n";
    std::cout << "SPI Mod " << priest->get_spirit_modifier()<< "\n";
    delete priest;

    Rogue* rogue = new Rogue(race, engine, equipment, combat);
    std::cout << "Name: " << rogue->get_name() << "\n";
    std::cout << "STR Mod " << rogue->get_strength_modifier() << "\n";
    std::cout << "AGI Mod " << rogue->get_agility_modifier() << "\n";
    std::cout << "STA Mod " << rogue->get_stamina_modifier() << "\n";
    std::cout << "INT Mod " << rogue->get_intellect_modifier() << "\n";
    std::cout << "SPI Mod " << rogue->get_spirit_modifier()<< "\n";
    delete rogue;

    Mage* mage = new Mage(race, engine, equipment, combat);
    std::cout << "Name: " << mage->get_name() << "\n";
    std::cout << "STR Mod " << mage->get_strength_modifier() << "\n";
    std::cout << "AGI Mod " << mage->get_agility_modifier() << "\n";
    std::cout << "STA Mod " << mage->get_stamina_modifier() << "\n";
    std::cout << "INT Mod " << mage->get_intellect_modifier() << "\n";
    std::cout << "SPI Mod " << mage->get_spirit_modifier()<< "\n";
    delete mage;

    Druid* druid = new Druid(race, engine, equipment, combat);
    std::cout << "Name: " << druid->get_name() << "\n";
    std::cout << "STR Mod " << druid->get_strength_modifier() << "\n";
    std::cout << "AGI Mod " << druid->get_agility_modifier() << "\n";
    std::cout << "STA Mod " << druid->get_stamina_modifier() << "\n";
    std::cout << "INT Mod " << druid->get_intellect_modifier() << "\n";
    std::cout << "SPI Mod " << druid->get_spirit_modifier()<< "\n";
    delete druid;

    Hunter* hunter = new Hunter(race, engine, equipment, combat);
    std::cout << "Name: " << hunter->get_name() << "\n";
    std::cout << "STR Mod " << hunter->get_strength_modifier() << "\n";
    std::cout << "AGI Mod " << hunter->get_agility_modifier() << "\n";
    std::cout << "STA Mod " << hunter->get_stamina_modifier() << "\n";
    std::cout << "INT Mod " << hunter->get_intellect_modifier() << "\n";
    std::cout << "SPI Mod " << hunter->get_spirit_modifier()<< "\n";
    delete hunter;

    Warlock* warlock = new Warlock(race, engine, equipment, combat);
    std::cout << "Name: " << warlock->get_name() << "\n";
    std::cout << "STR Mod " << warlock->get_strength_modifier() << "\n";
    std::cout << "AGI Mod " << warlock->get_agility_modifier() << "\n";
    std::cout << "STA Mod " << warlock->get_stamina_modifier() << "\n";
    std::cout << "INT Mod " << warlock->get_intellect_modifier() << "\n";
    std::cout << "SPI Mod " << warlock->get_spirit_modifier()<< "\n";
    delete warlock;

    Shaman* shaman = new Shaman(race, engine, equipment, combat);
    std::cout << "Name: " << shaman->get_name() << "\n";
    std::cout << "STR Mod " << shaman->get_strength_modifier() << "\n";
    std::cout << "AGI Mod " << shaman->get_agility_modifier() << "\n";
    std::cout << "STA Mod " << shaman->get_stamina_modifier() << "\n";
    std::cout << "INT Mod " << shaman->get_intellect_modifier() << "\n";
    std::cout << "SPI Mod " << shaman->get_spirit_modifier()<< "\n";
    delete shaman;

    Paladin* paladin = new Paladin(race, engine, equipment, combat);
    std::cout << "Name: " << paladin->get_name() << "\n";
    std::cout << "STR Mod " << paladin->get_strength_modifier() << "\n";
    std::cout << "AGI Mod " << paladin->get_agility_modifier() << "\n";
    std::cout << "STA Mod " << paladin->get_stamina_modifier() << "\n";
    std::cout << "INT Mod " << paladin->get_intellect_modifier() << "\n";
    std::cout << "SPI Mod " << paladin->get_spirit_modifier()<< "\n";
    delete paladin;

    race = new Orc();
    warr = new Warrior(race, engine, equipment, combat);
    std::cout << "Character " << warr->get_race()->get_name() << \
                 " " << warr->get_name() << "\n";
    std::cout << "STR After mod " << warr->get_strength() << "\n";
    std::cout << "AGI After mod " << warr->get_agility() << "\n";
    std::cout << "STA After mod " << warr->get_stamina() << "\n";
    std::cout << "INT After mod " << warr->get_intellect() << "\n";
    std::cout << "SPI After mod " << warr->get_spirit()<< "\n";

    warr->set_clvl(60);
    assert(warr->get_clvl() == 60);
    delete target;
    delete random;
    delete combat;
    delete race;
    delete warr;
    delete engine;
    delete equipment;
}
