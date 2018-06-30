#ifndef TESTBLOODRAGE_H
#define TESTBLOODRAGE_H

#include "TestSpellWarrior.h"

class TestBloodrage: public TestSpellWarrior {
public:
    TestBloodrage();

    void test_all();

    Bloodrage* bloodrage();

    void test_name_correct();
    void test_has_60_second_cooldown();
    void test_does_not_incur_global_cooldown_on_use();
    void test_costs_0_rage();
    void test_gain_10_rage_immediately();
    void test_gain_10_rage_over_10_seconds();

    void when_bloodrage_is_performed();

    void then_periodic_bloodrage_rage_gain_is(const int expected_rage_gain);

private:
};

#endif // TESTBLOODRAGE_H
