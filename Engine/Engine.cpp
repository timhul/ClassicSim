
#include "Engine.h"
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

#include <iostream>

void Engine::run(void) {
    while(!queue.empty()) {
        Event* event = queue.get_next();
        event->act();
        delete event;
    }
}

void Engine::end_combat(void) {
    std::cout << "Engine: Ending combat.\n";
    queue.clear();
}

void Engine::test_queue(void) {
    Race* race = new Orc();
    Class* pclass = new Warrior();
    Character* pchar = new Character(race, pclass);
    EncounterStart* start_event = new EncounterStart(pchar);
    EncounterEnd* end_event = new EncounterEnd(this);
    this->queue.push(end_event);
    this->queue.push(start_event);
    run();
}

void Engine::test_character_creation(void) {
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
    delete race;

    Class* pclass = new Warrior();
    std::cout << "Name: " << pclass->get_name() << "\n";
    std::cout << "STR Mod " << pclass->get_strength_modifier() << "\n";
    std::cout << "AGI Mod " << pclass->get_agility_modifier() << "\n";
    std::cout << "STA Mod " << pclass->get_stamina_modifier() << "\n";
    std::cout << "INT Mod " << pclass->get_intellect_modifier() << "\n";
    std::cout << "SPI Mod " << pclass->get_spirit_modifier()<< "\n";
    delete pclass;

    pclass = new Priest();
    std::cout << "Name: " << pclass->get_name() << "\n";
    std::cout << "STR Mod " << pclass->get_strength_modifier() << "\n";
    std::cout << "AGI Mod " << pclass->get_agility_modifier() << "\n";
    std::cout << "STA Mod " << pclass->get_stamina_modifier() << "\n";
    std::cout << "INT Mod " << pclass->get_intellect_modifier() << "\n";
    std::cout << "SPI Mod " << pclass->get_spirit_modifier()<< "\n";
    delete pclass;

    pclass = new Rogue();
    std::cout << "Name: " << pclass->get_name() << "\n";
    std::cout << "STR Mod " << pclass->get_strength_modifier() << "\n";
    std::cout << "AGI Mod " << pclass->get_agility_modifier() << "\n";
    std::cout << "STA Mod " << pclass->get_stamina_modifier() << "\n";
    std::cout << "INT Mod " << pclass->get_intellect_modifier() << "\n";
    std::cout << "SPI Mod " << pclass->get_spirit_modifier()<< "\n";
    delete pclass;

    pclass = new Mage();
    std::cout << "Name: " << pclass->get_name() << "\n";
    std::cout << "STR Mod " << pclass->get_strength_modifier() << "\n";
    std::cout << "AGI Mod " << pclass->get_agility_modifier() << "\n";
    std::cout << "STA Mod " << pclass->get_stamina_modifier() << "\n";
    std::cout << "INT Mod " << pclass->get_intellect_modifier() << "\n";
    std::cout << "SPI Mod " << pclass->get_spirit_modifier()<< "\n";
    delete pclass;

    pclass = new Druid();
    std::cout << "Name: " << pclass->get_name() << "\n";
    std::cout << "STR Mod " << pclass->get_strength_modifier() << "\n";
    std::cout << "AGI Mod " << pclass->get_agility_modifier() << "\n";
    std::cout << "STA Mod " << pclass->get_stamina_modifier() << "\n";
    std::cout << "INT Mod " << pclass->get_intellect_modifier() << "\n";
    std::cout << "SPI Mod " << pclass->get_spirit_modifier()<< "\n";
    delete pclass;

    pclass = new Hunter();
    std::cout << "Name: " << pclass->get_name() << "\n";
    std::cout << "STR Mod " << pclass->get_strength_modifier() << "\n";
    std::cout << "AGI Mod " << pclass->get_agility_modifier() << "\n";
    std::cout << "STA Mod " << pclass->get_stamina_modifier() << "\n";
    std::cout << "INT Mod " << pclass->get_intellect_modifier() << "\n";
    std::cout << "SPI Mod " << pclass->get_spirit_modifier()<< "\n";
    delete pclass;

    pclass = new Warlock();
    std::cout << "Name: " << pclass->get_name() << "\n";
    std::cout << "STR Mod " << pclass->get_strength_modifier() << "\n";
    std::cout << "AGI Mod " << pclass->get_agility_modifier() << "\n";
    std::cout << "STA Mod " << pclass->get_stamina_modifier() << "\n";
    std::cout << "INT Mod " << pclass->get_intellect_modifier() << "\n";
    std::cout << "SPI Mod " << pclass->get_spirit_modifier()<< "\n";
    delete pclass;

    pclass = new Shaman();
    std::cout << "Name: " << pclass->get_name() << "\n";
    std::cout << "STR Mod " << pclass->get_strength_modifier() << "\n";
    std::cout << "AGI Mod " << pclass->get_agility_modifier() << "\n";
    std::cout << "STA Mod " << pclass->get_stamina_modifier() << "\n";
    std::cout << "INT Mod " << pclass->get_intellect_modifier() << "\n";
    std::cout << "SPI Mod " << pclass->get_spirit_modifier()<< "\n";
    delete pclass;

    pclass = new Paladin();
    std::cout << "Name: " << pclass->get_name() << "\n";
    std::cout << "STR Mod " << pclass->get_strength_modifier() << "\n";
    std::cout << "AGI Mod " << pclass->get_agility_modifier() << "\n";
    std::cout << "STA Mod " << pclass->get_stamina_modifier() << "\n";
    std::cout << "INT Mod " << pclass->get_intellect_modifier() << "\n";
    std::cout << "SPI Mod " << pclass->get_spirit_modifier()<< "\n";
    delete pclass;

    race = new Orc();
    pclass = new Warrior();
    Character* pchar = new Character(race, pclass);
    std::cout << "Character " << pchar->get_race()->get_name() << \
                 " " << pchar->get_class()->get_name() << "\n";
    delete pchar;
    delete race;
    delete pclass;

}
