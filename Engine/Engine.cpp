
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

#include <iostream>

void Engine::run(void) {
    while(!queue.empty()) {
        Event* event = queue.get_next();
        event->act();
        delete event;
    }
}

void Engine::test_queue(void) {
    EncounterStart* start_event = new EncounterStart();
    EncounterEnd* end_event = new EncounterEnd();
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

    race = new Dwarf();
    std::cout << "Name: " << race->get_name() << "\n";
    std::cout << "STR " << race->get_base_strength() << "\n";
    std::cout << "AGI " << race->get_base_agility() << "\n";
    std::cout << "STA " << race->get_base_stamina() << "\n";
    std::cout << "INT " << race->get_base_intellect() << "\n";
    std::cout << "SPI " << race->get_base_spirit() << "\n";

    race = new NightElf();
    std::cout << "Name: " << race->get_name() << "\n";
    std::cout << "STR " << race->get_base_strength() << "\n";
    std::cout << "AGI " << race->get_base_agility() << "\n";
    std::cout << "STA " << race->get_base_stamina() << "\n";
    std::cout << "INT " << race->get_base_intellect() << "\n";
    std::cout << "SPI " << race->get_base_spirit() << "\n";

    race = new Gnome();
    std::cout << "Name: " << race->get_name() << "\n";
    std::cout << "STR " << race->get_base_strength() << "\n";
    std::cout << "AGI " << race->get_base_agility() << "\n";
    std::cout << "STA " << race->get_base_stamina() << "\n";
    std::cout << "INT " << race->get_base_intellect() << "\n";
    std::cout << "SPI " << race->get_base_spirit() << "\n";

    race = new Orc();
    std::cout << "Name: " << race->get_name() << "\n";
    std::cout << "STR " << race->get_base_strength() << "\n";
    std::cout << "AGI " << race->get_base_agility() << "\n";
    std::cout << "STA " << race->get_base_stamina() << "\n";
    std::cout << "INT " << race->get_base_intellect() << "\n";
    std::cout << "SPI " << race->get_base_spirit() << "\n";

    race = new Undead();
    std::cout << "Name: " << race->get_name() << "\n";
    std::cout << "STR " << race->get_base_strength() << "\n";
    std::cout << "AGI " << race->get_base_agility() << "\n";
    std::cout << "STA " << race->get_base_stamina() << "\n";
    std::cout << "INT " << race->get_base_intellect() << "\n";
    std::cout << "SPI " << race->get_base_spirit() << "\n";

    race = new Tauren();
    std::cout << "Name: " << race->get_name() << "\n";
    std::cout << "STR " << race->get_base_strength() << "\n";
    std::cout << "AGI " << race->get_base_agility() << "\n";
    std::cout << "STA " << race->get_base_stamina() << "\n";
    std::cout << "INT " << race->get_base_intellect() << "\n";
    std::cout << "SPI " << race->get_base_spirit() << "\n";

    race = new Troll();
    std::cout << "Name: " << race->get_name() << "\n";
    std::cout << "STR " << race->get_base_strength() << "\n";
    std::cout << "AGI " << race->get_base_agility() << "\n";
    std::cout << "STA " << race->get_base_stamina() << "\n";
    std::cout << "INT " << race->get_base_intellect() << "\n";
    std::cout << "SPI " << race->get_base_spirit() << "\n";

    Class* pclass = new Warrior();
    std::cout << "Name: " << pclass->get_name() << "\n";
    std::cout << "STR Mod " << pclass->get_strength_modifier() << "\n";
    std::cout << "AGI Mod " << pclass->get_agility_modifier() << "\n";
    std::cout << "STA Mod " << pclass->get_stamina_modifier() << "\n";
    std::cout << "INT Mod " << pclass->get_intellect_modifier() << "\n";
    std::cout << "SPI Mod " << pclass->get_spirit_modifier()<< "\n";

    pclass = new Priest();
    std::cout << "Name: " << pclass->get_name() << "\n";
    std::cout << "STR Mod " << pclass->get_strength_modifier() << "\n";
    std::cout << "AGI Mod " << pclass->get_agility_modifier() << "\n";
    std::cout << "STA Mod " << pclass->get_stamina_modifier() << "\n";
    std::cout << "INT Mod " << pclass->get_intellect_modifier() << "\n";
    std::cout << "SPI Mod " << pclass->get_spirit_modifier()<< "\n";

    pclass = new Rogue();
    std::cout << "Name: " << pclass->get_name() << "\n";
    std::cout << "STR Mod " << pclass->get_strength_modifier() << "\n";
    std::cout << "AGI Mod " << pclass->get_agility_modifier() << "\n";
    std::cout << "STA Mod " << pclass->get_stamina_modifier() << "\n";
    std::cout << "INT Mod " << pclass->get_intellect_modifier() << "\n";
    std::cout << "SPI Mod " << pclass->get_spirit_modifier()<< "\n";

    pclass = new Mage();
    std::cout << "Name: " << pclass->get_name() << "\n";
    std::cout << "STR Mod " << pclass->get_strength_modifier() << "\n";
    std::cout << "AGI Mod " << pclass->get_agility_modifier() << "\n";
    std::cout << "STA Mod " << pclass->get_stamina_modifier() << "\n";
    std::cout << "INT Mod " << pclass->get_intellect_modifier() << "\n";
    std::cout << "SPI Mod " << pclass->get_spirit_modifier()<< "\n";

    pclass = new Druid();
    std::cout << "Name: " << pclass->get_name() << "\n";
    std::cout << "STR Mod " << pclass->get_strength_modifier() << "\n";
    std::cout << "AGI Mod " << pclass->get_agility_modifier() << "\n";
    std::cout << "STA Mod " << pclass->get_stamina_modifier() << "\n";
    std::cout << "INT Mod " << pclass->get_intellect_modifier() << "\n";
    std::cout << "SPI Mod " << pclass->get_spirit_modifier()<< "\n";

    pclass = new Hunter();
    std::cout << "Name: " << pclass->get_name() << "\n";
    std::cout << "STR Mod " << pclass->get_strength_modifier() << "\n";
    std::cout << "AGI Mod " << pclass->get_agility_modifier() << "\n";
    std::cout << "STA Mod " << pclass->get_stamina_modifier() << "\n";
    std::cout << "INT Mod " << pclass->get_intellect_modifier() << "\n";
    std::cout << "SPI Mod " << pclass->get_spirit_modifier()<< "\n";

    pclass = new Warlock();
    std::cout << "Name: " << pclass->get_name() << "\n";
    std::cout << "STR Mod " << pclass->get_strength_modifier() << "\n";
    std::cout << "AGI Mod " << pclass->get_agility_modifier() << "\n";
    std::cout << "STA Mod " << pclass->get_stamina_modifier() << "\n";
    std::cout << "INT Mod " << pclass->get_intellect_modifier() << "\n";
    std::cout << "SPI Mod " << pclass->get_spirit_modifier()<< "\n";

    pclass = new Shaman();
    std::cout << "Name: " << pclass->get_name() << "\n";
    std::cout << "STR Mod " << pclass->get_strength_modifier() << "\n";
    std::cout << "AGI Mod " << pclass->get_agility_modifier() << "\n";
    std::cout << "STA Mod " << pclass->get_stamina_modifier() << "\n";
    std::cout << "INT Mod " << pclass->get_intellect_modifier() << "\n";
    std::cout << "SPI Mod " << pclass->get_spirit_modifier()<< "\n";

    pclass = new Paladin();
    std::cout << "Name: " << pclass->get_name() << "\n";
    std::cout << "STR Mod " << pclass->get_strength_modifier() << "\n";
    std::cout << "AGI Mod " << pclass->get_agility_modifier() << "\n";
    std::cout << "STA Mod " << pclass->get_stamina_modifier() << "\n";
    std::cout << "INT Mod " << pclass->get_intellect_modifier() << "\n";
    std::cout << "SPI Mod " << pclass->get_spirit_modifier()<< "\n";
}
