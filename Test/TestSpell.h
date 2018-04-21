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
    TestSpell();
    ~TestSpell();

    void set_up_general();
    void tear_down_general();

    void given_no_previous_damage_dealt();
    void given_a_guaranteed_white_hit();
    void given_a_guaranteed_white_crit();
    void given_a_guaranteed_melee_ability_crit();
    void given_a_guaranteed_melee_ability_hit();
    void given_a_mainhand_weapon_with_100_min_max_dmg();
    void given_a_mainhand_weapon_with_3_speed();
    void given_a_mainhand_weapon_with_2_speed();

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
