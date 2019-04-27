#include "TestConsecration.h"

#include "CharacterStats.h"
#include "Consecration.h"
#include "Equipment.h"
#include "HolyPaladin.h"
#include "PaladinSpells.h"
#include "Talent.h"

TestConsecration::TestConsecration(EquipmentDb *equipment_db) :
    TestSpellPaladin(equipment_db, "Consecration")
{}

void TestConsecration::test_all() {
    run_mandatory_tests(false);

    set_up(false);
    test_damage();
    tear_down();
}

Consecration* TestConsecration::consecration() {
    auto* spells = dynamic_cast<PaladinSpells*>(paladin->get_spells());
    return dynamic_cast<Consecration*>(spells->get_consecration());
}

void TestConsecration::test_name_correct() {
    assert(consecration()->get_name() == "Consecration");
}

void TestConsecration::test_spell_cooldown() {
    assert(almost_equal(consecration()->get_base_cooldown(), 8.0));
}

void TestConsecration::test_how_spell_observes_global_cooldown() {
    given_consecration_is_enabled();
    assert(consecration()->get_spell_status() == SpellStatus::Available);

    given_paladin_is_on_gcd();

    assert(consecration()->get_spell_status() == SpellStatus::OnGCD);
}

void TestConsecration::test_whether_spell_causes_global_cooldown() {
    given_consecration_is_enabled();
    assert(paladin->action_ready());

    when_consecration_is_performed();

    assert(!paladin->action_ready());
}

void TestConsecration::test_resource_cost() {
    given_consecration_is_enabled();

    given_paladin_has_mana(564);
    assert(consecration()->get_spell_status() == SpellStatus::InsufficientResources);

    given_paladin_has_mana(565);
    assert(consecration()->get_spell_status() == SpellStatus::Available);

    given_paladin_has_mana(566);
    when_consecration_is_performed();
    then_paladin_has_mana(1);
}

void TestConsecration::test_is_ready_conditions() {
    assert(consecration()->get_spell_status() == SpellStatus::NotEnabled);

    given_consecration_is_enabled();

    assert(consecration()->get_spell_status() == SpellStatus::Available);
}

void TestConsecration::test_damage() {
    ignored_events = {"ResourceGain", "BuffRemoval", "PlayerAction"};
    given_consecration_is_enabled();
    given_character_has_spell_damage(100, MagicSchool::Holy);
    given_a_guaranteed_magic_hit(MagicSchool::Holy);

    when_consecration_is_performed();

    then_next_event_is("DotTick", "2.000", RUN_EVENT);
    then_next_event_is("DotTick", "4.000", RUN_EVENT);
    then_next_event_is("DotTick", "6.000", RUN_EVENT);
    then_next_event_is("DotTick", "8.000", RUN_EVENT);

    // [Damage] = base_dmg + holy_spell_dmg * spell_coefficient
    // [417] = 384 + 100 * 0.33
    then_damage_dealt_is(417);
}

void TestConsecration::given_consecration_is_enabled() {
    given_talent_rank(HolyPaladin(paladin).get_consecration(), 1);
    assert(consecration()->is_enabled());
    paladin->prepare_set_of_combat_iterations();
}

void TestConsecration::when_consecration_is_performed() {
    consecration()->perform();
}
