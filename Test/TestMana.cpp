#include "TestMana.h"

#include "CharacterStats.h"
#include "Hunter.h"
#include "HunterSpells.h"
#include "MultiShot.h"
#include "Orc.h"

TestMana::TestMana(EquipmentDb* equipment_db) :
    TestSpellHunter(equipment_db, "Mana")
{}

void TestMana::test_all() {
    run_mandatory_tests();

    set_up();
    test_mana_gain_when_tick_is_within_5sr();
    tear_down();

    set_up();
    test_mana_gain_when_tick_is_outside_5sr();
    tear_down();
}

void TestMana::test_mana_gain_when_tick_is_within_5sr() {
    spend_mana();

    then_next_event_is("PlayerAction", "1.500");
    spend_mana();
    then_next_event_is("PlayerAction", "3.000");

    unsigned mana_before_tick = pchar->get_resource_level(ResourceType::Mana);
    then_next_event_is("ResourceGain", "5.000", RUN_EVENT);

    unsigned gain_from_tick = pchar->get_resource_level(ResourceType::Mana) - mana_before_tick;
    // This will be zero until mp5 from gear is available.
    assert(gain_from_tick == 0);
}

void TestMana::test_mana_gain_when_tick_is_outside_5sr() {
    spend_mana();
    unsigned mana_before_tick = pchar->get_resource_level(ResourceType::Mana);

    then_next_event_is("PlayerAction", "1.500");
    then_next_event_is("ResourceGain", "5.000", RUN_EVENT);

    unsigned gain_from_tick = pchar->get_resource_level(ResourceType::Mana) - mana_before_tick;
    // [Mana gain] = base_mp5 + mp5_from_spirit
    // 33 = 15 + (94 / 5)
    assert(pchar->get_stats()->get_spirit() == 94);
    assert(gain_from_tick == 33);
}

void TestMana::spend_mana() {
    unsigned mana_before = pchar->get_resource_level(ResourceType::Mana);
    given_a_ranged_weapon_with_100_min_max_dmg();
    dynamic_cast<HunterSpells*>(hunter->get_spells())->get_multi_shot()->perform();
    assert(mana_before - pchar->get_resource_level(ResourceType::Mana) == 230);
}

void TestMana::test_name_correct() {
}

void TestMana::test_spell_cooldown() {
}

void TestMana::test_obeys_global_cooldown() {
}

void TestMana::test_resource_cost() {
}

void TestMana::test_is_ready_conditions() {
}

void TestMana::test_incurs_global_cooldown() {
}
