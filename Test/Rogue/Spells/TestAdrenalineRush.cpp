#include "TestAdrenalineRush.h"

#include "AdrenalineRush.h"
#include "Backstab.h"
#include "Combat.h"
#include "Equipment.h"
#include "MainhandAttack.h"
#include "RogueSpells.h"
#include "Talent.h"
#include "WarriorSpells.h"

TestAdrenalineRush::TestAdrenalineRush(EquipmentDb *equipment_db) :
    TestSpellRogue(equipment_db, "Adrenaline Rush")
{}

void TestAdrenalineRush::test_all() {
    run_mandatory_tests(false);

    set_up(false);
    test_combo_points();
    tear_down();

    set_up(false);
    test_stealth();
    tear_down();

    set_up(false);
    test_tick_rate_over_entire_duration();
    tear_down();
}

AdrenalineRush *TestAdrenalineRush::adrenaline_rush() {
    return dynamic_cast<RogueSpells*>(rogue->get_spells())->get_adrenaline_rush();
}

void TestAdrenalineRush::test_name_correct() {
    assert(adrenaline_rush()->get_name() == "Adrenaline Rush");
}

void TestAdrenalineRush::test_spell_cooldown() {
    assert(QString::number(adrenaline_rush()->get_base_cooldown(), 'f', 3) == "300.000");
}

void TestAdrenalineRush::test_incurs_global_cooldown() {
    given_1_of_1_adrenaline_rush();
    when_adrenaline_rush_is_performed();

    then_next_event_is("PlayerAction", QString::number(rogue->global_cooldown(), 'f', 3));
}

void TestAdrenalineRush::test_obeys_global_cooldown() {
    given_1_of_1_adrenaline_rush();
    assert(adrenaline_rush()->get_spell_status() == SpellStatus::Available);

    given_rogue_is_on_gcd();

    assert(adrenaline_rush()->get_spell_status() == SpellStatus::OnGCD);
}

void TestAdrenalineRush::test_is_ready_conditions() {

}

void TestAdrenalineRush::test_resource_cost() {
    given_1_of_1_adrenaline_rush();
    given_rogue_has_energy(0);
    assert(adrenaline_rush()->get_spell_status() == SpellStatus::Available);

    when_adrenaline_rush_is_performed();

    then_rogue_has_energy(0);
}

void TestAdrenalineRush::test_combo_points() {
    given_1_of_1_adrenaline_rush();

    given_rogue_has_combo_points(0);
    assert(adrenaline_rush()->get_spell_status() == SpellStatus::Available);

    given_rogue_has_combo_points(1);
    assert(adrenaline_rush()->get_spell_status() == SpellStatus::Available);

    given_rogue_has_combo_points(2);
    assert(adrenaline_rush()->get_spell_status() == SpellStatus::Available);

    given_rogue_has_combo_points(3);
    assert(adrenaline_rush()->get_spell_status() == SpellStatus::Available);

    given_rogue_has_combo_points(4);
    assert(adrenaline_rush()->get_spell_status() == SpellStatus::Available);

    given_rogue_has_combo_points(5);
    assert(adrenaline_rush()->get_spell_status() == SpellStatus::Available);

    when_adrenaline_rush_is_performed();
    then_rogue_has_combo_points(5);
}

void TestAdrenalineRush::test_stealth() {
    given_1_of_1_adrenaline_rush();
    given_rogue_not_in_stealth();
    assert(adrenaline_rush()->get_spell_status() == SpellStatus::Available);
    given_rogue_in_stealth();
    assert(adrenaline_rush()->get_spell_status() == SpellStatus::Available);

    when_adrenaline_rush_is_performed();

    assert(!rogue->is_stealthed());
}

void TestAdrenalineRush::test_tick_rate_over_entire_duration() {
    given_1_of_1_adrenaline_rush();
    given_rogue_has_energy(0);
    ignored_events = {"PlayerAction"};

    when_adrenaline_rush_is_performed();

    then_next_event_is("ResourceGain", "2.000", RUN_EVENT);
    then_rogue_has_energy(40);

    then_next_event_is("ResourceGain", "4.000", RUN_EVENT);
    then_rogue_has_energy(80);

    then_next_event_is("ResourceGain", "6.000", RUN_EVENT);
    then_rogue_has_energy(100);

    given_rogue_has_energy(0);

    then_next_event_is("ResourceGain", "8.000", RUN_EVENT);
    then_rogue_has_energy(40);

    then_next_event_is("ResourceGain", "10.000", RUN_EVENT);
    then_rogue_has_energy(80);

    then_next_event_is("ResourceGain", "12.000", RUN_EVENT);
    then_rogue_has_energy(100);

    given_rogue_has_energy(0);

    then_next_event_is("ResourceGain", "14.000", RUN_EVENT);
    then_rogue_has_energy(40);

    then_next_event_is("BuffRemoval", "15.000", RUN_EVENT);
    then_next_event_is("ResourceGain", "16.000", RUN_EVENT);
    then_rogue_has_energy(60);

    then_next_event_is("ResourceGain", "18.000", RUN_EVENT);
    then_rogue_has_energy(80);

    then_next_event_is("ResourceGain", "20.000", RUN_EVENT);
    then_rogue_has_energy(100);
}

void TestAdrenalineRush::when_adrenaline_rush_is_performed() {
    if (pchar->get_equipment()->get_mainhand() == nullptr)
        given_a_mainhand_dagger_with_100_min_max_dmg();

    adrenaline_rush()->perform();
}

void TestAdrenalineRush::given_1_of_1_adrenaline_rush() {
    Talent* talent = Combat(rogue).get_adrenaline_rush();

    assert(talent->increment_rank());

    rogue->prepare_set_of_combat_iterations();

    delete talent;
}
