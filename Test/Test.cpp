
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

#include <iostream>
#include <assert.h>

void Test::test_queue(void) {
    Engine* engine = new Engine();
    Race* race = new Orc();
    Class* pclass = new Warrior(race, engine);
    EncounterStart* start_event = new EncounterStart(pclass);
    EncounterEnd* end_event = new EncounterEnd(engine);

    engine->add_event(end_event);
    engine->add_event(start_event);
    engine->run();

    delete pclass;
    delete race;
    delete engine;
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

    MeleeWeapon* mh = dynamic_cast<MeleeWeapon*>(equipment->get_mainhand());
    assert(mh->get_name() == "Frostbite");
    assert(mh->get_weapon_type() == 0);
    assert(mh->get_min_dmg() == 80);
    assert(mh->get_max_dmg() == 150);
    assert(mh->get_base_weapon_speed() - 2.7 < 0.01);
    assert(mh->get_weapon_proc_rate() == 0.0);

    delete mainhand;
    delete equipment;
}


void Test::test_character_creation(void) {
    Engine* engine = new Engine();

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

    Class* pclass = new Warrior(race, engine);
    std::cout << "Name: " << pclass->get_name() << "\n";
    std::cout << "STR Mod " << pclass->get_strength_modifier() << "\n";
    std::cout << "AGI Mod " << pclass->get_agility_modifier() << "\n";
    std::cout << "STA Mod " << pclass->get_stamina_modifier() << "\n";
    std::cout << "INT Mod " << pclass->get_intellect_modifier() << "\n";
    std::cout << "SPI Mod " << pclass->get_spirit_modifier()<< "\n";
    delete pclass;

    pclass = new Priest(race, engine);
    std::cout << "Name: " << pclass->get_name() << "\n";
    std::cout << "STR Mod " << pclass->get_strength_modifier() << "\n";
    std::cout << "AGI Mod " << pclass->get_agility_modifier() << "\n";
    std::cout << "STA Mod " << pclass->get_stamina_modifier() << "\n";
    std::cout << "INT Mod " << pclass->get_intellect_modifier() << "\n";
    std::cout << "SPI Mod " << pclass->get_spirit_modifier()<< "\n";
    delete pclass;

    pclass = new Rogue(race, engine);
    std::cout << "Name: " << pclass->get_name() << "\n";
    std::cout << "STR Mod " << pclass->get_strength_modifier() << "\n";
    std::cout << "AGI Mod " << pclass->get_agility_modifier() << "\n";
    std::cout << "STA Mod " << pclass->get_stamina_modifier() << "\n";
    std::cout << "INT Mod " << pclass->get_intellect_modifier() << "\n";
    std::cout << "SPI Mod " << pclass->get_spirit_modifier()<< "\n";
    delete pclass;

    pclass = new Mage(race, engine);
    std::cout << "Name: " << pclass->get_name() << "\n";
    std::cout << "STR Mod " << pclass->get_strength_modifier() << "\n";
    std::cout << "AGI Mod " << pclass->get_agility_modifier() << "\n";
    std::cout << "STA Mod " << pclass->get_stamina_modifier() << "\n";
    std::cout << "INT Mod " << pclass->get_intellect_modifier() << "\n";
    std::cout << "SPI Mod " << pclass->get_spirit_modifier()<< "\n";
    delete pclass;

    pclass = new Druid(race, engine);
    std::cout << "Name: " << pclass->get_name() << "\n";
    std::cout << "STR Mod " << pclass->get_strength_modifier() << "\n";
    std::cout << "AGI Mod " << pclass->get_agility_modifier() << "\n";
    std::cout << "STA Mod " << pclass->get_stamina_modifier() << "\n";
    std::cout << "INT Mod " << pclass->get_intellect_modifier() << "\n";
    std::cout << "SPI Mod " << pclass->get_spirit_modifier()<< "\n";
    delete pclass;

    pclass = new Hunter(race, engine);
    std::cout << "Name: " << pclass->get_name() << "\n";
    std::cout << "STR Mod " << pclass->get_strength_modifier() << "\n";
    std::cout << "AGI Mod " << pclass->get_agility_modifier() << "\n";
    std::cout << "STA Mod " << pclass->get_stamina_modifier() << "\n";
    std::cout << "INT Mod " << pclass->get_intellect_modifier() << "\n";
    std::cout << "SPI Mod " << pclass->get_spirit_modifier()<< "\n";
    delete pclass;

    pclass = new Warlock(race, engine);
    std::cout << "Name: " << pclass->get_name() << "\n";
    std::cout << "STR Mod " << pclass->get_strength_modifier() << "\n";
    std::cout << "AGI Mod " << pclass->get_agility_modifier() << "\n";
    std::cout << "STA Mod " << pclass->get_stamina_modifier() << "\n";
    std::cout << "INT Mod " << pclass->get_intellect_modifier() << "\n";
    std::cout << "SPI Mod " << pclass->get_spirit_modifier()<< "\n";
    delete pclass;

    pclass = new Shaman(race, engine);
    std::cout << "Name: " << pclass->get_name() << "\n";
    std::cout << "STR Mod " << pclass->get_strength_modifier() << "\n";
    std::cout << "AGI Mod " << pclass->get_agility_modifier() << "\n";
    std::cout << "STA Mod " << pclass->get_stamina_modifier() << "\n";
    std::cout << "INT Mod " << pclass->get_intellect_modifier() << "\n";
    std::cout << "SPI Mod " << pclass->get_spirit_modifier()<< "\n";
    delete pclass;

    pclass = new Paladin(race, engine);
    std::cout << "Name: " << pclass->get_name() << "\n";
    std::cout << "STR Mod " << pclass->get_strength_modifier() << "\n";
    std::cout << "AGI Mod " << pclass->get_agility_modifier() << "\n";
    std::cout << "STA Mod " << pclass->get_stamina_modifier() << "\n";
    std::cout << "INT Mod " << pclass->get_intellect_modifier() << "\n";
    std::cout << "SPI Mod " << pclass->get_spirit_modifier()<< "\n";
    delete pclass;

    race = new Orc();
    pclass = new Warrior(race, engine);
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
}
