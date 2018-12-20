#include "Character.h"
#include "TestTalentTree.h"

#include <utility>
#include "Talents.h"

TestTalentTree::TestTalentTree(EquipmentDb* equipment_db, QString tree_pos):
    equipment_db(equipment_db),
    tree_pos(std::move(tree_pos)),
    race(nullptr),
    pchar(nullptr)
{}

void TestTalentTree::test_all() {
    run_mandatory_tests();

    run_extra_tests();
}

void TestTalentTree::run_mandatory_tests() {
    set_up();
    test_spending_talent_points();
    tear_down();

    set_up();
    test_clearing_tree_after_filling();
    tear_down();

    set_up();
    test_refilling_tree_after_switching_talent_setup();
    tear_down();
}

void TestTalentTree::run_extra_tests() {

}

void TestTalentTree::clear_tree() {
    pchar->get_talents()->clear_tree(tree_pos);
}

bool TestTalentTree::tree_has_points(const int points) {
    return points == pchar->get_talents()->get_tree_points(tree_pos);
}

void TestTalentTree::switch_to_setup(const int index) {
    pchar->get_talents()->set_current_index(index);
}

bool TestTalentTree::increment(const QString& name, int num_times) {
    QString spell = get_position(name);
    bool success = true;
    for (int i = 0; i < num_times; ++i) {
        if (!pchar->get_talents()->increment_rank(tree_pos, spell))
            success = false;
    }

    return success;
}

bool TestTalentTree::decrement(const QString& name, int num_times) {
    QString spell = get_position(name);
    bool success = true;
    for (int i = 0; i < num_times; ++i) {
        if (!pchar->get_talents()->decrement_rank(tree_pos, spell))
            success = false;
    }

    return success;
}
