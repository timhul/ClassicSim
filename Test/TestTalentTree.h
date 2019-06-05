#ifndef TESTTALENTTREE_H
#define TESTTALENTTREE_H

#include <QString>

class Character;
class EquipmentDb;
class Race;
class RaidControl;
class SimSettings;
class TalentTree;
class Target;

class TestTalentTree {
public:
    TestTalentTree(EquipmentDb* equipment_db, QString tree_pos);
    virtual ~TestTalentTree() = default;

    void test_all();

protected:
    EquipmentDb* equipment_db;
    const QString tree_pos;
    Race* race {nullptr};
    Character* pchar {nullptr};
    Target* target {nullptr};
    SimSettings* sim_settings {nullptr};
    RaidControl* raid_control {nullptr};

    virtual void set_up() = 0;
    virtual void tear_down() = 0;

    void run_mandatory_tests();
    virtual void test_spending_talent_points() = 0;
    virtual void test_clearing_tree_after_filling() = 0;
    virtual void test_refilling_tree_after_switching_talent_setup() = 0;

    virtual void run_extra_tests();

    virtual QString get_position(const QString& name) const = 0;

    bool increment(const QString& name, int num_times = 1);
    bool decrement(const QString& name, int num_times = 1);
    void clear_tree();
    bool tree_has_points(const int points);
    void switch_to_setup(const int index);
};

#endif // TESTTALENTTREE_H
