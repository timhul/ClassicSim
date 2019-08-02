#include "TestMoonkinForm.h"

#include "Buff.h"
#include "CharacterStats.h"
#include "Druid.h"
#include "DruidSpells.h"
#include "MoonkinForm.h"
#include "RaidControl.h"

TestMoonkinForm::TestMoonkinForm(EquipmentDb* equipment_db) :
    TestSpellDruid(equipment_db, "Moonkin Form")
{}

void TestMoonkinForm::test_all() {
    run_mandatory_tests();

    set_up(false);
    test_gives_spell_crit_to_party_members();
    tear_down();
}

void TestMoonkinForm::test_name_correct() {
    assert(moonkin_form()->get_name() == "Moonkin Form");
}

void TestMoonkinForm::test_spell_cooldown() {
    assert(almost_equal(0.0, moonkin_form()->get_base_cooldown()));
}

void TestMoonkinForm::test_whether_spell_causes_global_cooldown() {
    given_balance_talent_rank("Moonkin Form", 1);
    assert(druid->action_ready());

    when_moonkin_form_is_performed();

    assert(!druid->action_ready());
}

void TestMoonkinForm::test_how_spell_observes_global_cooldown() {

}

void TestMoonkinForm::test_is_ready_conditions() {
    given_balance_talent_rank("Moonkin Form", 1);
    assert(moonkin_form()->get_spell_status() == SpellStatus::Available);
}

void TestMoonkinForm::test_gives_spell_crit_to_party_members() {
    Druid* druid_2 = new Druid(race, equipment_db, sim_settings, raid_control, 0, 1);
    given_balance_talent_rank("Moonkin Form", 1);
    raid_control->prepare_set_of_combat_iterations();

    const unsigned self_spell_crit_before = pchar->get_stats()->get_spell_crit_chance(MagicSchool::Nature);
    const unsigned druid_2_spell_crit_before = druid_2->get_stats()->get_spell_crit_chance(MagicSchool::Nature);

    when_moonkin_form_is_performed();

    assert(self_spell_crit_before + 300 == pchar->get_stats()->get_spell_crit_chance(MagicSchool::Nature));
    assert(druid_2_spell_crit_before + 300 == druid_2->get_stats()->get_spell_crit_chance(MagicSchool::Nature));

    given_engine_priority_pushed_forward(1.01);
    druid->cancel_form();
    assert(druid->get_current_form() == DruidForm::Caster);

    assert(self_spell_crit_before == pchar->get_stats()->get_spell_crit_chance(MagicSchool::Nature));
    assert(druid_2_spell_crit_before == druid_2->get_stats()->get_spell_crit_chance(MagicSchool::Nature));

    delete druid_2;
}

void TestMoonkinForm::test_resource_cost() {
    given_balance_talent_rank("Moonkin Form", 1);
    given_druid_has_mana(101);

    when_moonkin_form_is_performed();

    then_druid_has_mana(1);
}

void TestMoonkinForm::when_moonkin_form_is_performed() {
    druid->switch_to_form(DruidForm::Moonkin);
}
