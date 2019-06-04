#include "TestMechanics.h"

#include <QDebug>

#include "Mechanics.h"
#include "Target.h"

void TestMechanics::test_all() {
    qDebug() << "TestMechanics";
    test_dodge_from_wpn_skill_diff();
    test_dw_white_miss();
    test_2h_white_miss();
    test_glancing_blow_rate();
    test_glancing_dmg_penalty();
    test_physical_crit_suppression_from_target_level();

    test_full_resistance_chance();
}

void TestMechanics::test_dodge_from_wpn_skill_diff() {
    auto* target = new Target(63);
    auto* mechanics = new Mechanics(target);

    assert(almost_equal(0.065, mechanics->get_dodge_chance(60, 300)));
    assert(almost_equal(0.065, mechanics->get_dodge_chance(60, 315)));
    // Weapon skill > defense slightly reduces dodge chance.
    assert(almost_equal(0.063, mechanics->get_dodge_chance(60, 320)));

    target->set_lvl(60);
    assert(almost_equal(0.044, mechanics->get_dodge_chance(60, 315)));

    // CLVL > TLVL reduces the dodge chance by 0.5%.
    assert(almost_equal(0.045, mechanics->get_dodge_chance(61, 300)));

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

    assert(almost_equal(0.28, mechanics->get_dw_white_miss_chance(60, 300)));
    assert(almost_equal(0.28, mechanics->get_dw_white_miss_chance(60, 301)));
    assert(almost_equal(0.28, mechanics->get_dw_white_miss_chance(60, 302)));
    assert(almost_equal(0.28, mechanics->get_dw_white_miss_chance(60, 303)));
    assert(almost_equal(0.28, mechanics->get_dw_white_miss_chance(60, 304)));
    assert(almost_equal(0.27, mechanics->get_dw_white_miss_chance(60, 305)));
    assert(almost_equal(0.27, mechanics->get_dw_white_miss_chance(60, 315)));
    assert(almost_equal(0.268, mechanics->get_dw_white_miss_chance(60, 320)));

    target->set_lvl(62);
    assert(almost_equal(0.26, mechanics->get_dw_white_miss_chance(60, 300)));

    target->set_lvl(61);
    assert(almost_equal(0.25, mechanics->get_dw_white_miss_chance(60, 300)));

    target->set_lvl(60);
    assert(almost_equal(0.24, mechanics->get_dw_white_miss_chance(60, 300)));

    delete mechanics;
    delete target;
}

void TestMechanics::test_2h_white_miss() {
    auto* target = new Target(63);
    auto* mechanics = new Mechanics(target);

    assert(almost_equal(0.09, mechanics->get_2h_white_miss_chance(60, 300)));
    assert(almost_equal(0.09, mechanics->get_2h_white_miss_chance(60, 301)));
    assert(almost_equal(0.09, mechanics->get_2h_white_miss_chance(60, 302)));
    assert(almost_equal(0.09, mechanics->get_2h_white_miss_chance(60, 303)));
    assert(almost_equal(0.09, mechanics->get_2h_white_miss_chance(60, 304)));
    assert(almost_equal(0.08, mechanics->get_2h_white_miss_chance(60, 305)));
    assert(almost_equal(0.08, mechanics->get_2h_white_miss_chance(60, 315)));
    assert(almost_equal(0.078, mechanics->get_2h_white_miss_chance(60, 320)));

    target->set_lvl(62);
    assert(almost_equal(0.07, mechanics->get_2h_white_miss_chance(60, 300)));

    target->set_lvl(61);
    assert(almost_equal(0.06, mechanics->get_2h_white_miss_chance(60, 300)));

    target->set_lvl(60);
    assert(almost_equal(0.05, mechanics->get_2h_white_miss_chance(60, 300)));

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
