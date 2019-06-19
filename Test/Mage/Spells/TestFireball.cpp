#include "TestFireball.h"

#include "CharacterStats.h"
#include "Fireball.h"
#include "Mage.h"
#include "Queue.h"

TestFireball::TestFireball(EquipmentDb *equipment_db) :
    TestSpellMage(equipment_db, "Fireball")
{}

void TestFireball::test_all() {
    run_mandatory_tests();

    set_up();
    test_hit_dmg();
    tear_down();

    set_up();
    test_crit_dmg();
    tear_down();
}

void TestFireball::test_name_correct() {
    assert(fireball()->get_name() == "Fireball");
}

void TestFireball::test_spell_cooldown() {
    assert(almost_equal(0.0, fireball()->get_base_cooldown()));
}

void TestFireball::test_whether_spell_causes_global_cooldown() {
    assert(mage->action_ready());

    when_fireball_is_performed();

    assert(!mage->action_ready());
}

void TestFireball::test_how_spell_observes_global_cooldown() {

}

void TestFireball::test_is_ready_conditions() {
    assert(fireball()->get_spell_status() == SpellStatus::Available);
}

void TestFireball::test_resource_cost() {
    given_a_guaranteed_melee_ability_hit();
    given_mage_has_mana(411);

    when_fireball_is_performed();
    when_running_queued_events_until(3.501);

    then_mage_has_mana(1);
}

void TestFireball::test_hit_dmg() {
    given_a_guaranteed_magic_hit(MagicSchool::Fire);
    given_1000_spell_power();
    given_no_previous_damage_dealt();

    when_fireball_is_performed();
    when_running_queued_events_until(3.501);

    // [Damage] = base_dmg + spell_power * spell_coefficient
    // [1596 - 1761] = [596 - 761] + 1000 * 1.0
    then_damage_dealt_is_in_range(1596, 1761);
}

void TestFireball::test_crit_dmg() {
    given_a_guaranteed_magic_crit(MagicSchool::Fire);
    given_1000_spell_power();
    given_no_previous_damage_dealt();

    when_fireball_is_performed();
    when_running_queued_events_until(3.501);

    // [Damage] = (base_dmg + spell_power * spell_coefficient) * spell_crit_dmg_modifier
    // [2394 - 2642] = ([596 - 761] + 1000 * 1.0) * 1.5
    then_damage_dealt_is_in_range(2394, 2642);
}

void TestFireball::when_fireball_is_performed() {
    fireball()->perform();
}
