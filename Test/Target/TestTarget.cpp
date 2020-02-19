#include "TestTarget.h"

#include <QDebug>

#include "Mechanics.h"
#include "Target.h"

TestTarget::TestTarget() : TestObject(nullptr) {}

void TestTarget::test_all() {
    qDebug() << "TestTarget";
    set_up();
    test_values_after_initialization();
    tear_down();

    set_up();
    test_armor_increase_does_increase_armor();
    tear_down();

    set_up();
    test_armor_decrease_does_decrease_armor();
    tear_down();

    set_up();
    test_armor_never_reduced_below_zero();
    tear_down();

    set_up();
    test_armor_increase_does_not_increase_armor_if_other_effects_outweigh();
    tear_down();
}

void TestTarget::set_up() {
    target = new Target(60);
}

void TestTarget::tear_down() {
    delete target;
}

void TestTarget::test_values_after_initialization() {
    assert(target->get_lvl() == 60);
    assert(target->get_armor() == Mechanics::get_boss_base_armor());
    assert(target->get_defense() == target->get_lvl() * 5);
    assert(target->get_resistance(MagicSchool::Arcane) == 70);
    assert(target->get_resistance(MagicSchool::Fire) == 70);
    assert(target->get_resistance(MagicSchool::Frost) == 70);
    assert(target->get_resistance(MagicSchool::Holy) == 0);
    assert(target->get_resistance(MagicSchool::Nature) == 70);
    assert(target->get_resistance(MagicSchool::Shadow) == 70);
}

void TestTarget::test_armor_increase_does_increase_armor() {
    target->increase_armor(500);

    assert(target->get_armor() == Mechanics::get_boss_base_armor() + 500);
}

void TestTarget::test_armor_decrease_does_decrease_armor() {
    assert(Mechanics::get_boss_base_armor() > 499);

    target->decrease_armor(500);

    assert(target->get_armor() == Mechanics::get_boss_base_armor() - 500);
}

void TestTarget::test_armor_never_reduced_below_zero() {
    target->decrease_armor(Mechanics::get_boss_base_armor());
    assert(target->get_armor() == 0);

    target->decrease_armor(500);

    assert(target->get_armor() == 0);
}

void TestTarget::test_armor_increase_does_not_increase_armor_if_other_effects_outweigh() {
    target->decrease_armor(Mechanics::get_boss_base_armor() - 1);
    assert(target->get_armor() == 1);

    target->decrease_armor(500);
    target->decrease_armor(1);

    target->increase_armor(500);
    assert(target->get_armor() == 0);
}
