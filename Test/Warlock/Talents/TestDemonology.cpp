#include "TestDemonology.h"

#include <cassert>

#include "Orc.h"
#include "RaidControl.h"
#include "SimSettings.h"
#include "Warlock.h"

TestDemonology::TestDemonology(EquipmentDb* equipment_db_) : TestTalentTree(equipment_db_, "MID") {}

void TestDemonology::set_up() {
    race = new Orc();
    sim_settings = new SimSettings();
    raid_control = new RaidControl(sim_settings);
    pchar = new Warlock(race, equipment_db, sim_settings, raid_control);
}

void TestDemonology::tear_down() {
    delete pchar;
    delete race;
    delete sim_settings;
    delete raid_control;
}

void TestDemonology::test_spending_talent_points() {
    assert(increment("Improved Healthstone", 2));
    assert(increment("Improved Imp", 3));
    assert(increment("Demonic Embrace", 5));
    assert(increment("Improved Health Funnel", 2));
    assert(increment("Fel Intellect", 5));
    assert(increment("Improved Succubus", 3));
    assert(increment("Fel Stamina", 5));
    assert(increment("Improved Enslave Demon", 5));
    assert(tree_has_points(30));

    // Assert cannot spend points into Soul Link if 1/1 Demonic Sacrifice is missing
    assert(!increment("Soul Link"));
    assert(increment("Demonic Sacrifice"));
    assert(increment("Soul Link"));

    // Assert cannot remove points from Demonic Sacrifice once points are spent in Soul Link
    assert(!decrement("Demonic Sacrifice"));
    assert(decrement("Soul Link"));
    assert(decrement("Demonic Sacrifice"));
    assert(tree_has_points(30));

    // Assert cannot spend points into Master Demonologist if 5/5 Unholy Power is missing
    assert(!increment("Master Demonologist"));
    assert(increment("Unholy Power", 4));
    assert(!increment("Master Demonologist"));
    assert(increment("Unholy Power"));
    assert(increment("Master Demonologist"));

    // Assert cannot remove points from Unholy Power once points are spent in Master Demonologist
    assert(!decrement("Unholy Power"));
    assert(decrement("Master Demonologist"));
    assert(decrement("Unholy Power"));

    // Assert cannot increment Master Summoner without Fel Domination
    assert(!increment("Master Summoner"));
    assert(increment("Fel Domination"));
    assert(increment("Master Summoner"));

    assert(!decrement("Fel Domination"));
    assert(decrement("Master Summoner"));
    assert(decrement("Fel Domination"));
}

void TestDemonology::test_clearing_tree_after_filling() {
    spec_demonology();

    clear_tree();

    assert(tree_has_points(0));
}

void TestDemonology::test_refilling_tree_after_switching_talent_setup() {
    assert(tree_has_points(0));
    spec_demonology();
    assert(tree_has_points(51));

    switch_to_setup(1);
    assert(tree_has_points(0));
    spec_demonology();
    assert(tree_has_points(51));

    switch_to_setup(2);
    assert(tree_has_points(0));
    spec_demonology();
    assert(tree_has_points(51));
}

void TestDemonology::spec_demonology() {
    assert(increment("Improved Healthstone", 2));
    assert(increment("Improved Imp", 3));
    assert(increment("Demonic Embrace", 5));
    assert(increment("Improved Health Funnel", 2));
    assert(increment("Improved Voidwalker", 3));
    assert(increment("Fel Intellect", 5));
    assert(increment("Improved Succubus", 3));
    assert(increment("Fel Domination", 1));
    assert(increment("Fel Stamina", 5));
    assert(increment("Master Summoner", 2));
    assert(increment("Unholy Power", 5));
    assert(increment("Improved Enslave Demon", 5));
    assert(increment("Demonic Sacrifice", 1));
    assert(increment("Improved Firestone", 2));
    assert(increment("Master Demonologist", 5));
    assert(increment("Soul Link", 1));
    assert(increment("Improved Spellstone", 1));
}
