#include "TestMaul.h"

#include <cassert>

#include "BearForm.h"
#include "Buff.h"
#include "ClassStatistics.h"
#include "Druid.h"
#include "DruidSpells.h"
#include "Maul.h"

TestMaul::TestMaul(EquipmentDb* equipment_db) : TestSpellDruid(equipment_db, "Maul") {}

void TestMaul::test_all() {
    run_mandatory_tests();

    set_up();
    test_resource_cost_1_of_5_ferocity();
    tear_down();

    set_up();
    test_resource_cost_2_of_5_ferocity();
    tear_down();

    set_up();
    test_resource_cost_3_of_5_ferocity();
    tear_down();

    set_up();
    test_resource_cost_4_of_5_ferocity();
    tear_down();

    set_up();
    test_resource_cost_5_of_5_ferocity();
    tear_down();

    set_up();
    test_hit_dmg();
    tear_down();

    set_up();
    test_hit_threat();
    tear_down();

    set_up();
    test_crit_dmg();
    tear_down();
}

void TestMaul::test_name_correct() {
    assert(maul()->get_name() == "Maul");
}

void TestMaul::test_spell_cooldown() {
    assert(almost_equal(0.0, maul()->get_base_cooldown()));
}

void TestMaul::test_whether_spell_causes_global_cooldown() {
    given_druid_in_bear_form();
    given_engine_priority_at(1.51);
    given_druid_has_rage(100);

    assert(druid->action_ready());

    when_maul_is_performed();

    assert(druid->action_ready());
}

void TestMaul::test_how_spell_observes_global_cooldown() {}

void TestMaul::test_resource_cost() {
    given_druid_in_bear_form();
    given_a_guaranteed_melee_ability_hit();
    given_druid_has_rage(100);

    when_maul_is_performed();

    then_druid_has_rage(85);
}

void TestMaul::test_is_ready_conditions() {
    assert(maul()->get_spell_status() == SpellStatus::InsufficientResources);

    given_druid_in_bear_form();

    assert(maul()->get_spell_status() == SpellStatus::InsufficientResources);

    given_druid_has_rage(100);

    assert(maul()->get_spell_status() == SpellStatus::Available);
}

void TestMaul::test_resource_cost_1_of_5_ferocity() {
    given_feral_talent_rank("Ferocity", 1);
    given_druid_in_bear_form();
    given_a_guaranteed_melee_ability_hit();
    given_druid_has_rage(100);

    when_maul_is_performed();

    then_druid_has_rage(86);
}

void TestMaul::test_resource_cost_2_of_5_ferocity() {
    given_feral_talent_rank("Ferocity", 2);
    given_druid_in_bear_form();
    given_a_guaranteed_melee_ability_hit();
    given_druid_has_rage(100);

    when_maul_is_performed();

    then_druid_has_rage(87);
}

void TestMaul::test_resource_cost_3_of_5_ferocity() {
    given_feral_talent_rank("Ferocity", 3);
    given_druid_in_bear_form();
    given_a_guaranteed_melee_ability_hit();
    given_druid_has_rage(100);

    when_maul_is_performed();

    then_druid_has_rage(88);
}

void TestMaul::test_resource_cost_4_of_5_ferocity() {
    given_feral_talent_rank("Ferocity", 4);
    given_druid_in_bear_form();
    given_a_guaranteed_melee_ability_hit();
    given_druid_has_rage(100);

    when_maul_is_performed();

    then_druid_has_rage(89);
}

void TestMaul::test_resource_cost_5_of_5_ferocity() {
    given_feral_talent_rank("Ferocity", 5);
    given_druid_in_bear_form();
    given_a_guaranteed_melee_ability_hit();
    given_druid_has_rage(100);

    when_maul_is_performed();

    then_druid_has_rage(90);
}

void TestMaul::test_hit_dmg_1_of_2_savage_fury() {
    given_feral_talent_rank("Savage Fury", 1);
    given_target_has_0_armor();
    given_in_melee_attack_mode();
    given_druid_in_bear_form();
    given_1000_melee_ap();
    given_druid_has_rage(100);
    given_a_guaranteed_melee_ability_hit();

    when_maul_is_performed();

    // [Damage] = (([min - max] + AP / 14) + bonus_damage) * 1.1
    // [477 - 544] = 2.5 * ([60 * 0.85 - 60 * 1.25] + 1000 / 14) + 128
    then_damage_dealt_is_in_range(477, 544);
}

void TestMaul::test_hit_dmg_2_of_2_savage_fury() {
    given_feral_talent_rank("Savage Fury", 2);
    given_target_has_0_armor();
    given_in_melee_attack_mode();
    given_druid_in_bear_form();
    given_1000_melee_ap();
    given_druid_has_rage(100);
    given_a_guaranteed_melee_ability_hit();

    when_maul_is_performed();

    // [Damage] = ([min - max] + AP / 14) + bonus_damage
    // [520 - 594] = 2.5 * ([60 * 0.85 - 60 * 1.25] + 1000 / 14) + 128
    then_damage_dealt_is_in_range(520, 594);
}

void TestMaul::test_hit_dmg() {
    given_target_has_0_armor();
    given_in_melee_attack_mode();
    given_druid_in_bear_form();
    given_1000_melee_ap();
    given_druid_has_rage(100);
    given_a_guaranteed_melee_ability_hit();

    when_maul_is_performed();

    // [Damage] = ([min - max] + AP / 14) + bonus_damage
    // [434 - 495] = 2.5 * ([60 * 0.85 - 60 * 1.25] + 1000 / 14) + 128
    then_damage_dealt_is_in_range(434, 495);
}

void TestMaul::test_hit_threat() {
    given_target_has_0_armor();
    given_in_melee_attack_mode();
    given_druid_in_bear_form();
    given_1000_melee_ap();
    given_druid_has_rage(100);
    given_a_guaranteed_melee_ability_hit();

    when_maul_is_performed();

    // [Damage] = ([min - max] + AP / 14) + bonus_damage
    // [434 - 495] = 2.5 * ([60 * 0.85 - 60 * 1.25] + 1000 / 14) + 128
    then_damage_dealt_is_in_range(434, 495);

    // [Threat] = [Damage*1.75*1.3] = [987 - 1127]
    then_threat_dealt_is_in_range(987, 1127);
}

void TestMaul::test_crit_dmg() {
    given_target_has_0_armor();
    given_in_melee_attack_mode();
    given_druid_in_bear_form();
    given_1000_melee_ap();
    given_druid_has_rage(100);
    given_a_guaranteed_melee_ability_crit();

    when_maul_is_performed();

    // [Damage] = (([min - max] + AP / 14) + bonus_damage) * crit_dmg_modifier
    // [868 - 1019] = (2.5 * ([60 * 0.85 - 60 * 1.25] + 1000 / 14) + 128) * 2.0
    then_damage_dealt_is_in_range(868, 990);
}

void TestMaul::when_maul_is_performed() {
    maul()->calculate_damage();
}

void TestMaul::given_druid_in_bear_form() {
    bear_form()->perform();
}
