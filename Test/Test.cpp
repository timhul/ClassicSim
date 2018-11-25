#include <cassert>
#include <QDebug>

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
#include "Weapon.h"
#include "WhiteHitTable.h"
#include "MeleeSpecialTable.h"
#include "CombatRoll.h"
#include "AttackResult.h"
#include "Random.h"
#include "Mechanics.h"
#include "Target.h"
#include "Talents.h"
#include "Faction.h"
#include "ItemNamespace.h"
#include "SimSettings.h"

#include "WarriorSpells.h"

#include "Test.h"
#include "TestAttackTables.h"
#include "TestCharacterStats.h"
#include "TestFelstrikerProc.h"
#include "TestRogue.h"
#include "TestWarrior.h"

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

    TestAttackTables().test_all();
    TestCharacterStats().test_all();
    TestFelstrikerProc(equipment_db).test_all();

    qDebug() << "test_warrior";
    TestWarrior().test_all();

    qDebug() << "test_rogue";
    TestRogue().test_all();
}

void Test::test_queue() {
    Race* race = new Orc();
    auto* sim_settings = new SimSettings();
    auto* pchar = new Warrior(race, equipment_db, sim_settings);
    pchar->get_equipment()->set_mainhand("Frostbite");
    pchar->get_equipment()->set_offhand("Vis'kag the Bloodletter");
    pchar->set_clvl(60);
    pchar->prepare_set_of_combat_iterations();
    auto* start_event = new EncounterStart(pchar);
    auto* end_event = new EncounterEnd(pchar->get_engine(), pchar, 300);

    pchar->get_engine()->add_event(end_event);
    pchar->get_engine()->add_event(start_event);
    pchar->get_engine()->run();
    pchar->get_engine()->dump();

    delete pchar;
    delete race;
    delete sim_settings;
}

void Test::test_random() {
    auto* random = new Random(0, 9999);

    for (int i = 0; i < 10; ++i) {
        qDebug() << "Random rolling " << random->get_roll();
    }

    delete random;
}

void Test::test_combat_roll_melee_hit_result() {
    Race* race = new Orc();
    auto* sim_settings = new SimSettings();
    auto* pchar = new Warrior(race, equipment_db, sim_settings);
    pchar->get_equipment()->set_mainhand("Frostbite");

    for(int i = 0; i < 30; ++i) {
        pchar->get_combat_roll()->get_melee_hit_result(300);
    }

    delete sim_settings;
    delete race;
    delete pchar;
}

void Test::test_combat_roll_creation() {
    auto* race = new Orc();
    auto* sim_settings = new SimSettings();
    auto* pchar = new Warrior(race, equipment_db, sim_settings);
    pchar->get_equipment()->set_mainhand("Frostbite");

    pchar->get_combat_roll()->get_white_hit_table(300);
    pchar->get_combat_roll()->get_white_hit_table(300);
    pchar->get_combat_roll()->get_white_hit_table(315);
    pchar->get_combat_roll()->get_white_hit_table(315);
    pchar->get_combat_roll()->get_white_hit_table(300);

    delete sim_settings;
    delete race;
    delete pchar;
}

void Test::test_mechanics_dodge() {
    auto* target = new Target(63);
    auto* mechanics = new Mechanics(target);

    assert(fabs(0.05 - mechanics->get_dodge_chance(300)) < 0.001);
    assert(fabs(0.05 - mechanics->get_dodge_chance(315)) < 0.001);

    target->set_lvl(60);
    assert(fabs(0.044 - mechanics->get_dodge_chance(315)) < 0.001);

    delete mechanics;
    delete target;
}

void Test::test_mechanics_glancing_rate() {
    auto* target = new Target(63);
    auto* mechanics = new Mechanics(target);

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

void Test::test_mechanics_glancing_dmg_penalty() {
    auto* target = new Target(63);
    auto* mechanics = new Mechanics(target);

    assert(fabs(0.7 - mechanics->get_glancing_blow_dmg_penalty(5)) < 0.001);

    assert(fabs(0.7 - mechanics->get_glancing_blow_dmg_penalty(300)) < 0.001);
    assert(fabs(0.85 - mechanics->get_glancing_blow_dmg_penalty(305)) < 0.001);
    assert(fabs(1.0 - mechanics->get_glancing_blow_dmg_penalty(310)) < 0.001);
    assert(fabs(1.0 - mechanics->get_glancing_blow_dmg_penalty(10000)) < 0.001);

    delete mechanics;
    delete target;
}

void Test::test_mechanics_dw_white_miss() {
    auto* target = new Target(63);
    auto* mechanics = new Mechanics(target);

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

void Test::test_equipment_creation() {
    auto* equipment = new Equipment(equipment_db, nullptr);
    equipment->set_mainhand("Frostbite");
    Weapon* mh = equipment->get_mainhand();

    assert(mh->get_name() == "Frostbite");
    assert(mh->get_weapon_type() == WeaponTypes::AXE);
    assert(mh->get_min_dmg() == 80);
    assert(mh->get_max_dmg() == 150);
    assert(mh->get_base_weapon_speed() - 2.7 < 0.01);

    delete equipment;
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

    auto* priest = new Priest(race, equipment_db, nullptr);
    delete priest;

    auto* rogue = new Rogue(race, equipment_db, nullptr);
    delete rogue;

    auto* mage = new Mage(race, equipment_db, nullptr);
    delete mage;

    auto* druid = new Druid(race, equipment_db, nullptr);
    delete druid;

    auto* hunter = new Hunter(race, equipment_db, nullptr);
    delete hunter;

    auto* warlock = new Warlock(race, equipment_db, nullptr);
    delete warlock;

    auto* shaman = new Shaman(race, equipment_db, nullptr);
    delete shaman;

    auto* paladin = new Paladin(race, equipment_db, nullptr);
    paladin->set_clvl(60);
    assert(paladin->get_clvl() == 60);
    delete paladin;

    delete race;
}
