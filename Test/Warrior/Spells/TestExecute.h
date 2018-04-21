#ifndef TESTEXECUTE_H
#define TESTEXECUTE_H

class Engine;
class Equipment;
class CombatRoll;
class Target;
class Race;
class Warrior;

class TestExecute {
public:
    // Move to common class
    void set_up();
    void tear_down();



    // Test specific
    void test_all();
    void test_name_correct();
    void test_has_no_cooldown();
    void test_incurs_global_cooldown_on_use();

private:
    Engine* engine;
    Equipment* equipment;
    CombatRoll* combat;
    Target* target;
    Race* race;
    Warrior* warrior;

};

#endif // TESTEXECUTE_H
