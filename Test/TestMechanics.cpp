#include "TestMechanics.h"

#include "Mechanics.h"
#include "Target.h"

void TestMechanics::test_all() {
    test_dodge_from_wpn_skill_diff();
    test_dw_white_miss();
    test_glancing_blow_rate();
    test_glancing_dmg_penalty();

    test_full_resistance_chance();
}

void TestMechanics::test_dodge_from_wpn_skill_diff() {
    auto* target = new Target(63);
    auto* mechanics = new Mechanics(target);

    assert(almost_equal(0.05, mechanics->get_dodge_chance(300)));
    assert(almost_equal(0.05, mechanics->get_dodge_chance(315)));

    target->set_lvl(60);
    assert(almost_equal(0.044, mechanics->get_dodge_chance(315)));

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

    assert(almost_equal(0.7, mechanics->get_glancing_blow_dmg_penalty(5)));

    assert(almost_equal(0.7, mechanics->get_glancing_blow_dmg_penalty(300)));
    assert(almost_equal(0.85, mechanics->get_glancing_blow_dmg_penalty(305)));
    assert(almost_equal(1.0, mechanics->get_glancing_blow_dmg_penalty(310)));
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
    auto* target = new Target(63);
    auto* mechanics = new Mechanics(target);

    assert(almost_equal(0.0, mechanics->get_full_resist_chance(0)));
    assert(almost_equal(0.005, mechanics->get_full_resist_chance(75)));
    assert(almost_equal(0.01, mechanics->get_full_resist_chance(150)));
    assert(almost_equal(0.04, mechanics->get_full_resist_chance(200)));
    assert(almost_equal(0.25, mechanics->get_full_resist_chance(300)));

    delete mechanics;
    delete target;
}
