#include "Test.h"

#include <QDebug>
#include <cassert>

#include "Character.h"
#include "CharacterStats.h"
#include "CharacterTalents.h"
#include "ClassStatistics.h"
#include "CombatRoll.h"
#include "Druid.h"
#include "Dwarf.h"
#include "EncounterEnd.h"
#include "EncounterStart.h"
#include "Engine.h"
#include "Equipment.h"
#include "EquipmentDb.h"
#include "Faction.h"
#include "Gnome.h"
#include "Human.h"
#include "Hunter.h"
#include "ItemNamespace.h"
#include "Mage.h"
#include "NightElf.h"
#include "Orc.h"
#include "Paladin.h"
#include "Priest.h"
#include "RaidControl.h"
#include "Random.h"
#include "Rogue.h"
#include "Shaman.h"
#include "SimSettings.h"
#include "Tauren.h"
#include "Test/Target/TestTarget.h"
#include "TestAttackTables.h"
#include "TestBloodFury.h"
#include "TestCharacterStats.h"
#include "TestCombatRoll.h"
#include "TestConditionVariableBuiltin.h"
#include "TestFelstrikerProc.h"
#include "TestHunter.h"
#include "TestMage.h"
#include "TestMana.h"
#include "TestMechanics.h"
#include "TestPaladin.h"
#include "TestRogue.h"
#include "TestRotationFileReader.h"
#include "TestShaman.h"
#include "TestWarrior.h"
#include "Troll.h"
#include "Undead.h"
#include "Utils/CompareDouble.h"
#include "Warlock.h"
#include "Warrior.h"
#include "WarriorSpells.h"
#include "Weapon.h"

Test::Test() :
    equipment_db(new EquipmentDb())
{}

Test::~Test() {
    delete equipment_db;
}

void Test::test_all() {
    qDebug() << "test_character_creation";
    test_character_creation();
    qDebug() << "test_equipment_creation";
    test_equipment_creation();
    qDebug() << "test_combat_roll_creation";
    test_combat_roll_creation();
    qDebug() << "test_queue";
    test_queue();

    TestMechanics().test_all();
    TestCombatRoll(equipment_db).test_all();
    TestTarget().test_all();
    TestAttackTables(equipment_db).test_all();
    TestCharacterStats(equipment_db).test_all();
    TestConditionVariableBuiltin(equipment_db).test_all();
    TestRotationFileReader().test_all();
    TestMana(equipment_db).test_all();
    TestBloodFury(equipment_db).test_all();

    TestWarrior(equipment_db).test_all();
    TestRogue(equipment_db).test_all();
    TestHunter(equipment_db).test_all();
    TestPaladin(equipment_db).test_all();
    TestShaman(equipment_db).test_all();
    TestMage(equipment_db).test_all();

    TestFelstrikerProc(equipment_db).test_all();
}

void Test::test_queue() {
    Race* race = new Orc();
    auto* sim_settings = new SimSettings();
    auto* raid_control = new RaidControl(sim_settings);
    auto* pchar = new Warrior(race, equipment_db, sim_settings, raid_control);
    pchar->get_equipment()->set_mainhand(11684);
    pchar->get_equipment()->set_offhand(17075);
    assert(pchar->get_equipment()->get_mainhand()->get_name() == "Ironfoe");
    assert(pchar->get_equipment()->get_offhand()->get_name() == "Vis'kag the Bloodletter");
    pchar->set_clvl(60);
    auto* start_event = new EncounterStart(pchar->get_spells(), pchar->get_enabled_buffs());
    auto* end_event = new EncounterEnd(pchar->get_engine(), 300);

    pchar->prepare_set_of_combat_iterations();
    pchar->get_engine()->add_event(end_event);
    pchar->get_engine()->add_event(start_event);
    pchar->get_engine()->run();

    delete pchar;
    delete race;
    delete sim_settings;
    delete raid_control;
}

void Test::test_combat_roll_creation() {
    auto* race = new Orc();
    auto* sim_settings = new SimSettings();
    auto* raid_control = new RaidControl(sim_settings);
    auto* pchar = new Warrior(race, equipment_db, sim_settings, raid_control);
    pchar->get_equipment()->set_mainhand(19103);
    assert(pchar->get_equipment()->get_mainhand()->get_name() == "Frostbite");

    pchar->get_combat_roll()->get_melee_white_table(300);
    pchar->get_combat_roll()->get_melee_white_table(300);
    pchar->get_combat_roll()->get_melee_white_table(315);
    pchar->get_combat_roll()->get_melee_white_table(315);
    pchar->get_combat_roll()->get_melee_white_table(300);

    delete sim_settings;
    delete race;
    delete pchar;
    delete raid_control;
}

void Test::test_equipment_creation() {
    auto* race = new Orc();
    auto* sim_settings = new SimSettings();
    auto* raid_control = new RaidControl(sim_settings);
    auto* pchar = new Warrior(race, equipment_db, sim_settings, raid_control);
    auto* equipment = pchar->get_equipment();
    equipment->set_mainhand(19103);
    Weapon* mh = equipment->get_mainhand();

    assert(mh != nullptr);
    assert(mh->get_name() == "Frostbite");
    assert(mh->get_weapon_type() == WeaponTypes::AXE);
    assert(mh->get_min_dmg() == 80);
    assert(mh->get_max_dmg() == 150);
    assert(almost_equal(2.7, mh->get_base_weapon_speed()));

    equipment->set_ranged(17069);
    Weapon* ranged = equipment->get_ranged();
    assert(ranged != nullptr);
    assert(ranged->get_name() == "Striker's Mark");
    assert(ranged->get_weapon_type() == WeaponTypes::BOW);
    assert(ranged->get_min_dmg() == 69);
    assert(ranged->get_max_dmg() == 129);
    assert(almost_equal(2.5, ranged->get_base_weapon_speed()));

    delete sim_settings;
    delete race;
    delete pchar;
    delete raid_control;
}

void Test::test_character_creation() {
    Race* race = new Human();
    assert(race->get_name() == "Human");
    assert(race->get_axe_bonus() == 0);
    assert(race->get_mace_bonus() == 5);
    assert(race->get_sword_bonus() == 5);
    assert(race->get_bow_bonus() == 0);
    assert(race->get_gun_bonus() == 0);
    delete race;

    race = new Dwarf();
    assert(race->get_name() == "Dwarf");
    assert(race->get_axe_bonus() == 0);
    assert(race->get_mace_bonus() == 0);
    assert(race->get_sword_bonus() == 0);
    assert(race->get_bow_bonus() == 0);
    assert(race->get_gun_bonus() == 5);
    delete race;

    race = new NightElf();
    assert(race->get_name() == "Night Elf");
    assert(race->get_axe_bonus() == 0);
    assert(race->get_mace_bonus() == 0);
    assert(race->get_sword_bonus() == 0);
    assert(race->get_bow_bonus() == 0);
    assert(race->get_gun_bonus() == 0);
    delete race;

    race = new Gnome();
    assert(race->get_name() == "Gnome");
    assert(race->get_axe_bonus() == 0);
    assert(race->get_mace_bonus() == 0);
    assert(race->get_sword_bonus() == 0);
    assert(race->get_bow_bonus() == 0);
    assert(race->get_gun_bonus() == 0);
    delete race;

    race = new Orc();
    assert(race->get_name() == "Orc");
    assert(race->get_axe_bonus() == 5);
    assert(race->get_mace_bonus() == 0);
    assert(race->get_sword_bonus() == 0);
    assert(race->get_bow_bonus() == 0);
    assert(race->get_gun_bonus() == 0);
    delete race;

    race = new Undead();
    assert(race->get_name() == "Undead");
    assert(race->get_axe_bonus() == 0);
    assert(race->get_mace_bonus() == 0);
    assert(race->get_sword_bonus() == 0);
    assert(race->get_bow_bonus() == 0);
    assert(race->get_gun_bonus() == 0);
    delete race;

    race = new Tauren();
    assert(race->get_name() == "Tauren");
    assert(race->get_axe_bonus() == 0);
    assert(race->get_mace_bonus() == 0);
    assert(race->get_sword_bonus() == 0);
    assert(race->get_bow_bonus() == 0);
    assert(race->get_gun_bonus() == 0);
    delete race;

    race = new Troll();
    assert(race->get_name() == "Troll");
    assert(race->get_axe_bonus() == 0);
    assert(race->get_mace_bonus() == 0);
    assert(race->get_sword_bonus() == 0);
    assert(race->get_bow_bonus() == 5);
    assert(race->get_gun_bonus() == 0);

    auto* sim_settings = new SimSettings();
    auto* raid_control = new RaidControl(sim_settings);

    auto* priest = new Priest(race, equipment_db, sim_settings, raid_control);
    auto* rogue = new Rogue(race, equipment_db, sim_settings, raid_control);
    auto* mage = new Mage(race, equipment_db, sim_settings, raid_control);
    auto* druid = new Druid(race, equipment_db, sim_settings, raid_control);
    auto* hunter = new Hunter(race, equipment_db, sim_settings, raid_control);
    auto* warlock = new Warlock(race, equipment_db, sim_settings, raid_control);
    auto* shaman = new Shaman(race, equipment_db, sim_settings, raid_control);

    auto* paladin = new Paladin(race, equipment_db, sim_settings, raid_control);
    paladin->set_clvl(60);
    assert(paladin->get_clvl() == 60);
    delete paladin;
    delete priest;
    delete rogue;
    delete mage;
    delete druid;
    delete hunter;
    delete warlock;
    delete shaman;

    delete race;
    delete sim_settings;
    delete raid_control;
}
