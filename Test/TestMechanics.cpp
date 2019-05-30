#include "TestMechanics.h"

#include <QDebug>

#include "Mechanics.h"
#include "Target.h"

void TestMechanics::test_all() {
    qDebug() << "TestMechanics";
    test_dodge_from_wpn_skill_diff();
    test_dw_white_miss();
    test_glancing_blow_rate();
    test_glancing_dmg_penalty_linear();
    test_glancing_dmg_penalty_exponential();

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

void TestMechanics::test_glancing_dmg_penalty_linear() {
    auto* target = new Target(63);
    auto* mechanics = new Mechanics(target);

    assert(almost_equal(0.7, mechanics->get_linear_glancing_blow_dmg_penalty(5)));

    assert(almost_equal(0.7, mechanics->get_linear_glancing_blow_dmg_penalty(300)));
    assert(almost_equal(0.85, mechanics->get_linear_glancing_blow_dmg_penalty(305)));
    assert(almost_equal(1.0, mechanics->get_linear_glancing_blow_dmg_penalty(310)));
    assert(almost_equal(1.0, mechanics->get_linear_glancing_blow_dmg_penalty(10000)));

    delete mechanics;
    delete target;
}

void TestMechanics::test_glancing_dmg_penalty_exponential() {
    auto* target = new Target(63);
    auto* mechanics = new Mechanics(target);

    assert(almost_equal(0.65, mechanics->get_glancing_blow_dmg_penalty(5)));

    assert(almost_equal(0.65, mechanics->get_glancing_blow_dmg_penalty(300)));
    assert(almost_equal(0.85, mechanics->get_glancing_blow_dmg_penalty(305)));
    assert(almost_equal(0.95, mechanics->get_glancing_blow_dmg_penalty(310)));
    assert(almost_equal(1.0, mechanics->get_glancing_blow_dmg_penalty(315)));
    assert(almost_equal(1.0, mechanics->get_glancing_blow_dmg_penalty(10000)));

    delete mechanics;
    delete target;
}

void TestMechanics::test_dw_white_miss() {
    auto* target = new Target(63);
    auto* mechanics = new Mechanics(target);

    assert(almost_equal(0.28, mechanics->get_dw_white_miss_chance(300)));
    assert(almost_equal(0.24, mechanics->get_dw_white_miss_chance(315)));

    target->set_lvl(62);
    assert(almost_equal(0.25, mechanics->get_dw_white_miss_chance(300)));

    target->set_lvl(61);
    assert(almost_equal(0.245, mechanics->get_dw_white_miss_chance(300)));

    target->set_lvl(60);
    assert(almost_equal(0.24, mechanics->get_dw_white_miss_chance(300)));

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
