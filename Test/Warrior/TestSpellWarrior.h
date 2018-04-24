#ifndef TESTSPELLWARRIOR_H
#define TESTSPELLWARRIOR_H

#include "TestSpell.h"
#include "Warrior.h"

class TestSpellWarrior: public TestSpell {
public:
    void set_up();
    void tear_down();

    void given_0_of_2_impale();
    void given_1_of_2_impale();
    void given_2_of_2_impale();
    void given_warrior_has_rage(const int);

    void then_warrior_has_rage(const int);

protected:
    Warrior* warrior;
};

#endif // TESTSPELLWARRIOR_H
