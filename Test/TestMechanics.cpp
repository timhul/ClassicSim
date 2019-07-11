#include "TestMechanics.h"

#include <QDebug>

#include "Mechanics.h"
#include "Target.h"

void TestMechanics::test_all() {
    qDebug() << "TestMechanics";
    test_dodge_from_wpn_skill_diff();
    test_2h_white_miss();
    test_dw_white_miss();
    test_glancing_blow_rate();
    test_glancing_dmg_penalty();
    test_physical_crit_suppression_from_target_level();

    test_full_resistance_chance();
}

void TestMechanics::test_dodge_from_wpn_skill_diff() {
    auto* target = new Target(63);
    auto* mechanics = new Mechanics(target);

    assert(almost_equal(0.065, mechanics->get_dodge_chance(300)));
    assert(almost_equal(0.064, mechanics->get_dodge_chance(301)));
    assert(almost_equal(0.063, mechanics->get_dodge_chance(302)));
    assert(almost_equal(0.062, mechanics->get_dodge_chance(303)));
    assert(almost_equal(0.061, mechanics->get_dodge_chance(304)));
    assert(almost_equal(0.060, mechanics->get_dodge_chance(305)));
    assert(almost_equal(0.059, mechanics->get_dodge_chance(306)));
    assert(almost_equal(0.058, mechanics->get_dodge_chance(307)));
    assert(almost_equal(0.057, mechanics->get_dodge_chance(308)));
    assert(almost_equal(0.056, mechanics->get_dodge_chance(309)));
    assert(almost_equal(0.055, mechanics->get_dodge_chance(310)));
    assert(almost_equal(0.054, mechanics->get_dodge_chance(311)));
    assert(almost_equal(0.053, mechanics->get_dodge_chance(312)));
    assert(almost_equal(0.052, mechanics->get_dodge_chance(313)));
    assert(almost_equal(0.051, mechanics->get_dodge_chance(314)));
    assert(almost_equal(0.050, mechanics->get_dodge_chance(315)));
    assert(almost_equal(0.045, mechanics->get_dodge_chance(320)));

    target->set_lvl(60);
    assert(almost_equal(0.05, mechanics->get_dodge_chance(300)));

    delete mechanics;
    delete target;
}

void TestMechanics::test_physical_crit_suppression_from_target_level() {
    auto* target = new Target(63);
    auto* mechanics = new Mechanics(target);

    assert(almost_equal(0.03, mechanics->get_melee_crit_suppression(60)));
    assert(almost_equal(0.02, mechanics->get_melee_crit_suppression(61)));
    assert(almost_equal(0.01, mechanics->get_melee_crit_suppression(62)));
    assert(almost_equal(0.00, mechanics->get_melee_crit_suppression(63)));
    assert(almost_equal(0.00, mechanics->get_melee_crit_suppression(64)));

    delete mechanics;
    delete target;
}

void TestMechanics::test_glancing_blow_rate() {
    auto* target = new Target(63);
    auto* mechanics = new Mechanics(target);

    assert(almost_equal(6.3, mechanics->get_glancing_blow_chance(1)));

    assert(almost_equal(0.4,  mechanics->get_glancing_blow_chance(60)));

    target->set_lvl(62);
    assert(almost_equal(0.3, mechanics->get_glancing_blow_chance(60)));

    target->set_lvl(61);
    assert(almost_equal(0.2, mechanics->get_glancing_blow_chance(60)));

    target->set_lvl(60);
    assert(almost_equal(0.1, mechanics->get_glancing_blow_chance(60)));

    target->set_lvl(59);
    assert(almost_equal(0.0, mechanics->get_glancing_blow_chance(60)));

    delete mechanics;
    delete target;
}

void TestMechanics::test_glancing_dmg_penalty() {
    auto* target = new Target(63);
    auto* mechanics = new Mechanics(target);

    assert(almost_equal(0.55, mechanics->get_glancing_blow_dmg_penalty_min(60, 5)));
    assert(almost_equal(0.55, mechanics->get_glancing_blow_dmg_penalty_min(60, 300)));
    assert(almost_equal(0.80, mechanics->get_glancing_blow_dmg_penalty_min(60, 305)));
    assert(almost_equal(0.91, mechanics->get_glancing_blow_dmg_penalty_min(60, 310)));
    assert(almost_equal(0.91, mechanics->get_glancing_blow_dmg_penalty_min(60, 315)));
    assert(almost_equal(0.91, mechanics->get_glancing_blow_dmg_penalty_min(60, 10000)));

    assert(almost_equal(0.75, mechanics->get_glancing_blow_dmg_penalty_max(60, 5)));
    assert(almost_equal(0.75, mechanics->get_glancing_blow_dmg_penalty_max(60, 300)));
    assert(almost_equal(0.90, mechanics->get_glancing_blow_dmg_penalty_max(60, 305)));
    assert(almost_equal(0.99, mechanics->get_glancing_blow_dmg_penalty_max(60, 310)));
    assert(almost_equal(0.99, mechanics->get_glancing_blow_dmg_penalty_max(60, 315)));
    assert(almost_equal(0.99, mechanics->get_glancing_blow_dmg_penalty_max(60, 10000)));

    delete mechanics;
    delete target;
}

void TestMechanics::test_dw_white_miss() {
    auto* target = new Target(63);
    auto* mechanics = new Mechanics(target);

    assert(almost_equal(0.272, mechanics->get_dw_white_miss_chance(300)));
    assert(almost_equal(0.2704, mechanics->get_dw_white_miss_chance(301)));
    assert(almost_equal(0.2688, mechanics->get_dw_white_miss_chance(302)));
    assert(almost_equal(0.2672, mechanics->get_dw_white_miss_chance(303)));
    assert(almost_equal(0.2656, mechanics->get_dw_white_miss_chance(304)));
    assert(almost_equal(0.248, mechanics->get_dw_white_miss_chance(305)));
    assert(almost_equal(0.2472, mechanics->get_dw_white_miss_chance(306)));
    assert(almost_equal(0.2464, mechanics->get_dw_white_miss_chance(307)));
    assert(almost_equal(0.2456, mechanics->get_dw_white_miss_chance(308)));
    assert(almost_equal(0.2448, mechanics->get_dw_white_miss_chance(309)));
    assert(almost_equal(0.244, mechanics->get_dw_white_miss_chance(310)));
    assert(almost_equal(0.2432, mechanics->get_dw_white_miss_chance(311)));
    assert(almost_equal(0.2424, mechanics->get_dw_white_miss_chance(312)));
    assert(almost_equal(0.2416, mechanics->get_dw_white_miss_chance(313)));
    assert(almost_equal(0.2408, mechanics->get_dw_white_miss_chance(314)));
    assert(almost_equal(0.24, mechanics->get_dw_white_miss_chance(315)));
    assert(almost_equal(0.236, mechanics->get_dw_white_miss_chance(320)));

    delete mechanics;
    delete target;
}

void TestMechanics::test_2h_white_miss() {
    auto* target = new Target(63);
    auto* mechanics = new Mechanics(target);

    assert(almost_equal(0.090, mechanics->get_2h_white_miss_chance(300)));
    assert(almost_equal(0.088, mechanics->get_2h_white_miss_chance(301)));
    assert(almost_equal(0.086, mechanics->get_2h_white_miss_chance(302)));
    assert(almost_equal(0.084, mechanics->get_2h_white_miss_chance(303)));
    assert(almost_equal(0.082, mechanics->get_2h_white_miss_chance(304)));
    assert(almost_equal(0.060, mechanics->get_2h_white_miss_chance(305)));
    assert(almost_equal(0.059, mechanics->get_2h_white_miss_chance(306)));
    assert(almost_equal(0.058, mechanics->get_2h_white_miss_chance(307)));
    assert(almost_equal(0.057, mechanics->get_2h_white_miss_chance(308)));
    assert(almost_equal(0.056, mechanics->get_2h_white_miss_chance(309)));
    assert(almost_equal(0.055, mechanics->get_2h_white_miss_chance(310)));
    assert(almost_equal(0.054, mechanics->get_2h_white_miss_chance(311)));
    assert(almost_equal(0.053, mechanics->get_2h_white_miss_chance(312)));
    assert(almost_equal(0.052, mechanics->get_2h_white_miss_chance(313)));
    assert(almost_equal(0.051, mechanics->get_2h_white_miss_chance(314)));
    assert(almost_equal(0.050, mechanics->get_2h_white_miss_chance(315)));
    assert(almost_equal(0.045, mechanics->get_2h_white_miss_chance(320)));

    delete mechanics;
    delete target;
}

void TestMechanics::test_full_resistance_chance() {
    assert(almost_equal(0.0, Mechanics::get_full_resist_chance(0)));
    assert(almost_equal(0.005, Mechanics::get_full_resist_chance(75)));
    assert(almost_equal(0.01, Mechanics::get_full_resist_chance(150)));
    assert(almost_equal(0.04, Mechanics::get_full_resist_chance(200)));
    assert(almost_equal(0.25, Mechanics::get_full_resist_chance(300)));
}
