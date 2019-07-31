#include "TestMoonfire.h"

#include "CharacterStats.h"
#include "Druid.h"
#include "Event.h"
#include "Moonfire.h"

TestMoonfire::TestMoonfire(EquipmentDb* equipment_db) :
    TestSpellDruid(equipment_db, "Moonfire")
{}

void TestMoonfire::test_all() {
    run_mandatory_tests();

    set_up();
    test_hit_dmg();
    tear_down();

    set_up();
    test_crit_dmg();
    tear_down();

    set_up();
    test_crit_dmg_5_of_5_vengeance_and_5_of_imp_moonfire();
    tear_down();

    set_up();
    test_duration_dmg_after_hit();
    tear_down();

    set_up();
    test_duration_dmg_after_crit();
    tear_down();

    set_up();
    test_hit_damage_1_of_5_moonfury();
    tear_down();

    set_up();
    test_hit_damage_5_of_5_moonfury();
    tear_down();

    set_up();
    test_resource_cost_3_of_3_moonglow();
    tear_down();
}

void TestMoonfire::test_name_correct() {
    assert(moonfire()->get_name() == "Moonfire");
}

void TestMoonfire::test_spell_cooldown() {
    assert(almost_equal(0.0, moonfire()->get_base_cooldown()));
}

void TestMoonfire::test_whether_spell_causes_global_cooldown() {
    assert(druid->action_ready());

    when_moonfire_is_performed();

    assert(!druid->action_ready());
}

void TestMoonfire::test_how_spell_observes_global_cooldown() {

}

void TestMoonfire::test_is_ready_conditions() {
    assert(moonfire()->get_spell_status() == SpellStatus::Available);
}

void TestMoonfire::test_resource_cost() {
    given_druid_has_mana(376);

    when_moonfire_is_performed();

    then_druid_has_mana(1);
}

void TestMoonfire::test_hit_dmg() {
    given_a_guaranteed_magic_hit(MagicSchool::Arcane);
    given_1000_spell_power();
    given_no_previous_damage_dealt();

    when_moonfire_is_performed();

    // [Damage] = base_dmg + spell_power * spell_coefficient
    // [345 - 378] = [195 - 228] + 1000 * ((1.5 / 3.5) ^ 2) / (1.5 / 3.5 + 12 / 15))
    then_damage_dealt_is_in_range(345, 378);
}

void TestMoonfire::test_crit_dmg() {
    given_a_guaranteed_magic_crit(MagicSchool::Arcane);
    given_1000_spell_power();
    given_no_previous_damage_dealt();

    when_moonfire_is_performed();

    // [Damage] = (base_dmg + spell_power * spell_coefficient) * spell_crit_dmg_modifier
    // [517 - 566] = ([195 - 228] + 1000 * ((1.5 / 3.5) ^ 2) / (1.5 / 3.5 + 12 / 15))) * 1.5
    then_damage_dealt_is_in_range(517, 566);
}

void TestMoonfire::test_crit_dmg_5_of_5_vengeance_and_5_of_imp_moonfire() {
    given_balance_talent_ranks({{"Improved Moonfire", 5}, {"Vengeance", 5}});
    given_a_guaranteed_magic_crit(MagicSchool::Arcane);
    given_1000_spell_power();
    given_no_previous_damage_dealt();

    when_moonfire_is_performed();

    // [Damage] = (base_dmg * imp_moonfire + spell_power * spell_coefficient) * spell_crit_dmg_modifier
    // [729 - 801] = ([195 * 1.1 - 228 * 1.1] + 1000 * ((1.5 / 3.5) ^ 2) / (1.5 / 3.5 + 12 / 15))) * 2
    then_damage_dealt_is_in_range(729, 801);
}

void TestMoonfire::test_duration_dmg_after_hit() {
    test_hit_dmg();
    given_event_is_ignored("PlayerAction");

    when_running_queued_events_until(12.01);

    // [Damage] = instant_dmg + full_duration_dmg * spell_coefficient
    // [1250 - 1283] = [345 - 378] + (384 + 1000 * ((12/15) ^ 2) / (1.5 / 3.5 + 12 / 15)))
    then_damage_dealt_is_in_range(1250, 1283);
}

void TestMoonfire::test_duration_dmg_after_crit() {
    test_crit_dmg();
    given_event_is_ignored("PlayerAction");

    when_running_queued_events_until(12.01);

    // [Damage] = instant_dmg + full_duration_dmg * spell_coefficient
    // [1422 - 1471] = ([345 - 378] + (384 + 1000 * ((12/15) ^ 2) / (1.5 / 3.5 + 12 / 15)))) * 1.5
    then_damage_dealt_is_in_range(1422, 1471);
}

void TestMoonfire::test_hit_damage_1_of_5_moonfury() {
    given_balance_talent_ranks({{"Nature's Grace", 1}, {"Moonfury", 1}});
    given_a_guaranteed_magic_hit(MagicSchool::Arcane);
    given_1000_spell_power();
    given_no_previous_damage_dealt();

    when_moonfire_is_performed();

    // [Damage] = base_dmg * moonfury + spell_power * spell_coefficient
    // [349 - 383] = [195 * 1.02 - 228 * 1.02] + 1000 * ((1.5 / 3.5) ^ 2) / (1.5 / 3.5 + 12 / 15))
    then_damage_dealt_is_in_range(349, 383);
}

void TestMoonfire::test_hit_damage_5_of_5_moonfury() {
    given_balance_talent_ranks({{"Nature's Grace", 1}, {"Moonfury", 5}});
    given_a_guaranteed_magic_hit(MagicSchool::Arcane);
    given_1000_spell_power();
    given_no_previous_damage_dealt();

    when_moonfire_is_performed();

    // [Damage] = base_dmg * moonfury + spell_power * spell_coefficient
    // [365 - 401] = [195 * 1.10 - 228 * 1.10] + 1000 * ((1.5 / 3.5) ^ 2) / (1.5 / 3.5 + 12 / 15))
    then_damage_dealt_is_in_range(365, 401);
}

void TestMoonfire::test_resource_cost_3_of_3_moonglow() {
    given_balance_talent_rank("Moonglow", 3);
    given_druid_has_mana(static_cast<unsigned>(std::round(375 * 0.91) + 1));

    when_moonfire_is_performed();

    then_druid_has_mana(1);
}

void TestMoonfire::when_moonfire_is_performed() {
    moonfire()->perform();
}
