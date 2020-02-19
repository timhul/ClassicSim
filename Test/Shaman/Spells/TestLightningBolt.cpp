#include "TestLightningBolt.h"

#include <cassert>

#include "CharacterStats.h"
#include "Event.h"
#include "LightningBolt.h"
#include "Shaman.h"

TestLightningBolt::TestLightningBolt(EquipmentDb* equipment_db) : TestSpellShaman(equipment_db, "Lightning Bolt") {}

void TestLightningBolt::test_all() {
    run_mandatory_tests();

    set_up();
    test_hit_dmg();
    tear_down();

    set_up();
    test_crit_dmg();
    tear_down();

    set_up(false);
    test_clearcasting_roll();
    tear_down();
}

void TestLightningBolt::test_name_correct() {
    assert(lightning_bolt()->get_name() == "Lightning Bolt");
}

void TestLightningBolt::test_spell_cooldown() {
    assert(almost_equal(0.0, lightning_bolt()->get_base_cooldown()));
}

void TestLightningBolt::test_whether_spell_causes_global_cooldown() {
    assert(shaman->action_ready());

    when_lightning_bolt_is_performed();

    assert(!shaman->action_ready());
}

void TestLightningBolt::test_how_spell_observes_global_cooldown() {
    assert(lightning_bolt()->get_spell_status() == SpellStatus::Available);
    given_stormstrike_enabled();
    when_stormstrike_is_performed();

    assert(lightning_bolt()->get_spell_status() == SpellStatus::OnGCD);
}

void TestLightningBolt::test_is_ready_conditions() {
    assert(lightning_bolt()->get_spell_status() == SpellStatus::Available);
}

void TestLightningBolt::test_resource_cost() {
    given_a_guaranteed_melee_ability_hit();
    given_shaman_has_mana(266);

    when_lightning_bolt_is_performed();
    when_running_queued_events_until(3.5);

    then_shaman_has_mana(1);
}

void TestLightningBolt::test_hit_dmg() {
    given_a_guaranteed_magic_hit(MagicSchool::Nature);
    given_1000_spell_power();
    given_no_previous_damage_dealt();

    when_lightning_bolt_is_performed();
    when_running_queued_events_until(3.5);

    // [Damage] = base_dmg + spell_power * spell_coefficient
    // [1276 - 1324] = [419 - 467] + 1000 * 3 / 3.5
    then_damage_dealt_is_in_range(1276, 1324);
}

void TestLightningBolt::test_crit_dmg() {
    given_a_guaranteed_magic_crit(MagicSchool::Nature);
    given_1000_spell_power();
    given_no_previous_damage_dealt();

    when_lightning_bolt_is_performed();
    when_running_queued_events_until(3.5);

    // [Damage] = base_dmg + spell_power * spell_coefficient * spell_crit_dmg_modifier
    // [1914 - 1986] = ([419 - 467] + 1000 * 3 / 3.5) * 1.5
    then_damage_dealt_is_in_range(1914, 1986);
}

void TestLightningBolt::test_clearcasting_roll() {
    given_a_guaranteed_magic_crit(MagicSchool::Nature);
    given_1000_spell_power();
    given_clearcasting_enabled();
    given_no_previous_damage_dealt();

    when_lightning_bolt_is_performed();
    when_running_queued_events_until(3.5);
}

void TestLightningBolt::when_lightning_bolt_is_performed() {
    lightning_bolt()->perform();
}
