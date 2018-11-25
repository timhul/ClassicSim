#ifndef TESTTALENTTREE_H
#define TESTTALENTTREE_H

#include <QString>

class Character;
class EquipmentDb;
class Race;
class TalentTree;

class TestTalentTree {
public:
    TestTalentTree(EquipmentDb* equipment_db, const QString& tree_pos);
    virtual ~TestTalentTree() = default;

    void test_all();

protected:
    EquipmentDb* equipment_db;
    const QString tree_pos;
    Race* race;
    Character* pchar;

    virtual void set_up() = 0;
    virtual void tear_down() = 0;

    void run_mandatory_tests();
    virtual void test_spending_talent_points() = 0;
    virtual void test_clearing_tree_after_filling() = 0;
    virtual void test_refilling_tree_after_switching_talent_setup() = 0;

    virtual void run_extra_tests();

    virtual QString get_position(const QString& name) const = 0;

    bool increment_talent_num_times(const QString& name, int num_times);
    bool increment(const QString& name);
    bool decrement(const QString& name);
    void clear_tree();
    bool tree_has_points(const int points);
};

#endif // TESTTALENTTREE_H
