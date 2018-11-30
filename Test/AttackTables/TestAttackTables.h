#ifndef TESTATTACKTABLES_H
#define TESTATTACKTABLES_H

#include "TestCharacter.h"


class TestAttackTables : TestCharacter {
public:
    void test_all() override;

private:
    void test_basic_properties() override;
    void test_white_hit_table();
    void test_white_hit_table_update();
    void test_special_hit_table();
};

#endif // TESTATTACKTABLES_H
