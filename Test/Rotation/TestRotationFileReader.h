#ifndef TESTROTATIONFILEREADER_H
#define TESTROTATIONFILEREADER_H

#include "TestObject.h"

#include <QVector>

#include "ConditionVariableBuiltin.h"
#include "Resource.h"

class ConditionBuff;
class ConditionResource;
class Hunter;
class Paladin;
class Race;
class RaidControl;
class Rotation;
class RotationExecutor;
class SimSettings;
class Warrior;

class TestRotationFileReader : TestObject {
public:
    TestRotationFileReader();
    ~TestRotationFileReader() override;
    void test_all() override;

private:
    void test_values_after_initialization() override;

    void test_warrior_dw_fury();
    void test_hunter_aimed_shot_multi_shot();
    void test_paladin_seal_of_the_crusader();

    Race* race {nullptr};
    SimSettings* sim_settings {nullptr};
    Hunter* hunter {nullptr};
    Paladin* paladin {nullptr};
    Warrior* warrior {nullptr};
    RaidControl* raid_control {nullptr};
    QVector<Rotation*> rotations;

    void verify_executor_names(Rotation *rotation, QVector<RotationExecutor*> &executors, QVector<QString> &executor_names);
    void verify_resource_condition(ConditionResource* condition, const double cmp_value,
                                   const int comparator, const ResourceType resource_type);
    void verify_buff_condition(ConditionBuff* condition, const QString& name,
                               const double cmp_value, const int comparator);
    void verify_builtin_condition(ConditionVariableBuiltin* condition, const BuiltinVariables builtin,
                                  const double cmp_value, const int comparator);

    Rotation* get_rotation(const QString& name) const;

    void set_up_warrior();
    void set_up_hunter();
    void set_up_paladin();
    void tear_down();
};

#endif // TESTROTATIONFILEREADER_H
