#ifndef TESTSPELL_H
#define TESTSPELL_H

class Engine;
class Equipment;
class CombatRoll;
class Target;
class Race;
class Character;

class TestSpell {
public:
    void set_up_general();
    void tear_down_general();
    void given_no_previous_damage_dealt();
    void given_a_guaranteed_melee_ability_crit();
    void then_damage_dealt_is(const int damage);

protected:
    Engine* engine;
    Equipment* equipment;
    CombatRoll* combat;
    Target* target;
    Race* race;
    Character* pchar;
};

#endif // TESTSPELL_H
