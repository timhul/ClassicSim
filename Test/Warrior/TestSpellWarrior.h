#ifndef TESTSPELLWARRIOR_H
#define TESTSPELLWARRIOR_H

#include "TestSpell.h"
#include "Warrior.h"
#include "WarriorSpells.h"

class TestSpellWarrior: public TestSpell {
public:
    TestSpellWarrior(QString spell_under_test);

    void set_up();
    void tear_down();

    void given_0_of_2_impale();
    void given_1_of_2_impale();
    void given_2_of_2_impale();
    void given_0_of_5_tactical_mastery();
    void given_1_of_5_tactical_mastery();
    void given_2_of_5_tactical_mastery();
    void given_3_of_5_tactical_mastery();
    void given_4_of_5_tactical_mastery();
    void given_5_of_5_tactical_mastery();
    void given_warrior_has_rage(const int);

    void then_warrior_has_rage(const int);

protected:
    Warrior* warrior;
};

#endif // TESTSPELLWARRIOR_H
