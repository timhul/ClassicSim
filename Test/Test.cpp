
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
#include "CombatRoll.h"
#include "AttackResult.h"
#include "Random.h"

#include <iostream>
#include <assert.h>


void Test::test_all(void) {
    std::cout << "test_queue\n";
    test_queue();
    std::cout << "test_character_creation\n";
    test_character_creation();
    std::cout << "test_equipment_creation\n";
    test_equipment_creation();
    std::cout << "test_white_hit_table\n";
    test_white_hit_table();
    std::cout << "test_combat_roll_glancing\n";
    test_combat_roll_glancing();
    std::cout << "test_combat_roll_white_miss\n";
    test_combat_roll_white_miss();
    std::cout << "test_combat_roll_dodge\n";
    test_combat_roll_dodge();
    std::cout << "test_combat_roll_creation\n";
    test_combat_roll_creation();
    std::cout << "test_random\n";
    test_random();
    std::cout << "test_combat_roll_melee_hit_result\n";
    test_combat_roll_melee_hit_result();
}

void Test::test_queue(void) {
    Engine* engine = new Engine();
    Equipment* equipment = new Equipment();
    Race* race = new Orc();
    Class* pclass = new Warrior(race, engine, equipment);
    EncounterStart* start_event = new EncounterStart(pclass);
    EncounterEnd* end_event = new EncounterEnd(engine);

    engine->add_action_event(end_event);
    engine->add_action_event(start_event);
    engine->run();

    delete equipment;
    delete pclass;
    delete race;
    delete engine;
}

void Test::test_random(void) {
    Random* random = new Random();

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
    Class* pclass = new Warrior(race, engine, equipment);
    Random* random = new Random();
    CombatRoll* combat = new CombatRoll(dynamic_cast<Character*>(pclass), target, random);

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
    delete pclass;
    delete random;
    delete combat;
}

void Test::test_combat_roll_creation(void) {
    Target* target = new Target(63);
    Engine* engine = new Engine();
    Equipment* equipment = new Equipment();
    Race* race = new Orc();
    Class* pclass = new Warrior(race, engine, equipment);
    Random* random = new Random();
    CombatRoll* combat = new CombatRoll(dynamic_cast<Character*>(pclass), target, random);

    combat->get_white_hit_table(300);
    combat->get_white_hit_table(300);
    combat->get_white_hit_table(315);
    combat->get_white_hit_table(315);
    combat->get_white_hit_table(300);

    delete target;
    delete engine;
    delete equipment;
    delete race;
    delete pclass;
    delete random;
    delete combat;
}

void Test::test_combat_roll_dodge(void) {
    Target* target = new Target(63);
    Engine* engine = new Engine();
    Equipment* equipment = new Equipment();
    Race* race = new Orc();
    Class* pclass = new Warrior(race, engine, equipment);
    Random* random = new Random();
    CombatRoll* combat = new CombatRoll(dynamic_cast<Character*>(pclass), target, random);

    assert(fabs(0.05 - combat->get_dodge_chance(300)) < 0.001);
    assert(fabs(0.05 - combat->get_dodge_chance(315)) < 0.001);

    delete target;
    target = new Target(60);
    combat->set_target(target);
    assert(fabs(0.044 - combat->get_dodge_chance(315)) < 0.001);

    delete target;
    delete engine;
    delete equipment;
    delete race;
    delete pclass;
    delete random;
    delete combat;
}

void Test::test_combat_roll_glancing(void) {
    Target* target = new Target(63);
    Engine* engine = new Engine();
    Equipment* equipment = new Equipment();
    Race* race = new Orc();
    Class* pclass = new Warrior(race, engine, equipment);
    Random* random = new Random();
    CombatRoll* combat = new CombatRoll(dynamic_cast<Character*>(pclass), target, random);

    pclass->set_clvl(1);
    assert(fabs(6.3 - combat->get_glancing_blow_chance()) < 0.001);

    pclass->set_clvl(60);
    assert(fabs(0.4 - combat->get_glancing_blow_chance()) < 0.001);

    delete target;
    target = new Target(62);
    assert(fabs(0.3 - combat->get_glancing_blow_chance()) < 0.001);

    delete target;
    target = new Target(61);
    assert(fabs(0.2 - combat->get_glancing_blow_chance()) < 0.001);

    delete target;
    target = new Target(60);
    assert(fabs(0.1 - combat->get_glancing_blow_chance()) < 0.001);

    delete target;
    target = new Target(59);
    assert(fabs(0.0 - combat->get_glancing_blow_chance()) < 0.001);

    delete target;
    delete engine;
    delete equipment;
    delete race;
    delete pclass;
    delete random;
    delete combat;
}

void Test::test_combat_roll_white_miss(void) {
    Target* target = new Target(63);
    Engine* engine = new Engine();
    Equipment* equipment = new Equipment();
    Offhand* offhand = new Offhand("Frostbite", 0, 80, 150, 2.7, 0.0);
    equipment->set_offhand(offhand);
    Race* race = new Orc();
    Class* pclass = new Warrior(race, engine, equipment);
    Random* random = new Random();
    CombatRoll* combat = new CombatRoll(dynamic_cast<Character*>(pclass), target, random);

    assert(fabs(0.28 - combat->get_white_miss_chance(300)) < 0.001);
    assert(fabs(0.24 - combat->get_white_miss_chance(315)) < 0.001);
    delete target;

    target = new Target(62);
    combat->set_target(target);
    assert(fabs(0.25 - combat->get_white_miss_chance(300)) < 0.001);
    delete target;

    target = new Target(61);
    combat->set_target(target);
    assert(fabs(0.245 - combat->get_white_miss_chance(300)) < 0.001);
    delete target;

    target = new Target(60);
    combat->set_target(target);
    assert(fabs(0.24 - combat->get_white_miss_chance(300)) < 0.001);
    delete target;

    delete engine;
    delete equipment;
    delete race;
    delete pclass;
    delete random;
    delete combat;
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

void Test::test_equipment_creation(void) {
    Equipment* equipment = new Equipment();

    Mainhand* mainhand = new Mainhand("Frostbite", 0, 80, 150, 2.7, 0.0);
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

    Class* pclass = new Warrior(race, engine, equipment);
    std::cout << "Name: " << pclass->get_name() << "\n";
    std::cout << "STR Mod " << pclass->get_strength_modifier() << "\n";
    std::cout << "AGI Mod " << pclass->get_agility_modifier() << "\n";
    std::cout << "STA Mod " << pclass->get_stamina_modifier() << "\n";
    std::cout << "INT Mod " << pclass->get_intellect_modifier() << "\n";
    std::cout << "SPI Mod " << pclass->get_spirit_modifier()<< "\n";
    delete pclass;

    pclass = new Priest(race, engine, equipment);
    std::cout << "Name: " << pclass->get_name() << "\n";
    std::cout << "STR Mod " << pclass->get_strength_modifier() << "\n";
    std::cout << "AGI Mod " << pclass->get_agility_modifier() << "\n";
    std::cout << "STA Mod " << pclass->get_stamina_modifier() << "\n";
    std::cout << "INT Mod " << pclass->get_intellect_modifier() << "\n";
    std::cout << "SPI Mod " << pclass->get_spirit_modifier()<< "\n";
    delete pclass;

    pclass = new Rogue(race, engine, equipment);
    std::cout << "Name: " << pclass->get_name() << "\n";
    std::cout << "STR Mod " << pclass->get_strength_modifier() << "\n";
    std::cout << "AGI Mod " << pclass->get_agility_modifier() << "\n";
    std::cout << "STA Mod " << pclass->get_stamina_modifier() << "\n";
    std::cout << "INT Mod " << pclass->get_intellect_modifier() << "\n";
    std::cout << "SPI Mod " << pclass->get_spirit_modifier()<< "\n";
    delete pclass;

    pclass = new Mage(race, engine, equipment);
    std::cout << "Name: " << pclass->get_name() << "\n";
    std::cout << "STR Mod " << pclass->get_strength_modifier() << "\n";
    std::cout << "AGI Mod " << pclass->get_agility_modifier() << "\n";
    std::cout << "STA Mod " << pclass->get_stamina_modifier() << "\n";
    std::cout << "INT Mod " << pclass->get_intellect_modifier() << "\n";
    std::cout << "SPI Mod " << pclass->get_spirit_modifier()<< "\n";
    delete pclass;

    pclass = new Druid(race, engine, equipment);
    std::cout << "Name: " << pclass->get_name() << "\n";
    std::cout << "STR Mod " << pclass->get_strength_modifier() << "\n";
    std::cout << "AGI Mod " << pclass->get_agility_modifier() << "\n";
    std::cout << "STA Mod " << pclass->get_stamina_modifier() << "\n";
    std::cout << "INT Mod " << pclass->get_intellect_modifier() << "\n";
    std::cout << "SPI Mod " << pclass->get_spirit_modifier()<< "\n";
    delete pclass;

    pclass = new Hunter(race, engine, equipment);
    std::cout << "Name: " << pclass->get_name() << "\n";
    std::cout << "STR Mod " << pclass->get_strength_modifier() << "\n";
    std::cout << "AGI Mod " << pclass->get_agility_modifier() << "\n";
    std::cout << "STA Mod " << pclass->get_stamina_modifier() << "\n";
    std::cout << "INT Mod " << pclass->get_intellect_modifier() << "\n";
    std::cout << "SPI Mod " << pclass->get_spirit_modifier()<< "\n";
    delete pclass;

    pclass = new Warlock(race, engine, equipment);
    std::cout << "Name: " << pclass->get_name() << "\n";
    std::cout << "STR Mod " << pclass->get_strength_modifier() << "\n";
    std::cout << "AGI Mod " << pclass->get_agility_modifier() << "\n";
    std::cout << "STA Mod " << pclass->get_stamina_modifier() << "\n";
    std::cout << "INT Mod " << pclass->get_intellect_modifier() << "\n";
    std::cout << "SPI Mod " << pclass->get_spirit_modifier()<< "\n";
    delete pclass;

    pclass = new Shaman(race, engine, equipment);
    std::cout << "Name: " << pclass->get_name() << "\n";
    std::cout << "STR Mod " << pclass->get_strength_modifier() << "\n";
    std::cout << "AGI Mod " << pclass->get_agility_modifier() << "\n";
    std::cout << "STA Mod " << pclass->get_stamina_modifier() << "\n";
    std::cout << "INT Mod " << pclass->get_intellect_modifier() << "\n";
    std::cout << "SPI Mod " << pclass->get_spirit_modifier()<< "\n";
    delete pclass;

    pclass = new Paladin(race, engine, equipment);
    std::cout << "Name: " << pclass->get_name() << "\n";
    std::cout << "STR Mod " << pclass->get_strength_modifier() << "\n";
    std::cout << "AGI Mod " << pclass->get_agility_modifier() << "\n";
    std::cout << "STA Mod " << pclass->get_stamina_modifier() << "\n";
    std::cout << "INT Mod " << pclass->get_intellect_modifier() << "\n";
    std::cout << "SPI Mod " << pclass->get_spirit_modifier()<< "\n";
    delete pclass;

    race = new Orc();
    pclass = new Warrior(race, engine, equipment);
    std::cout << "Character " << pclass->get_race()->get_name() << \
                 " " << pclass->get_name() << "\n";
    std::cout << "STR After mod " << pclass->get_strength() << "\n";
    std::cout << "AGI After mod " << pclass->get_agility() << "\n";
    std::cout << "STA After mod " << pclass->get_stamina() << "\n";
    std::cout << "INT After mod " << pclass->get_intellect() << "\n";
    std::cout << "SPI After mod " << pclass->get_spirit()<< "\n";

    pclass->set_clvl(60);
    assert(pclass->get_clvl() == 60);
    delete race;
    delete pclass;
    delete engine;
    delete equipment;
}
