#ifndef TESTSPELLWARRIOR_H
#define TESTSPELLWARRIOR_H

#include "TestSpellDamage.h"
#include "Warrior.h"
#include "WarriorSpells.h"

class TestSpellWarrior: public TestSpellDamage {
public:
    TestSpellWarrior(EquipmentDb* equipment_db, QString spell_under_test);

    void set_up(const bool prepare_combat_iterations = true) override;
    void tear_down() override;

    void run_class_specific_tests() override;
    virtual void test_stance_cooldown() = 0;

    void given_0_of_2_impale();
    void given_1_of_2_impale();
    void given_2_of_2_impale();
    void given_0_of_5_tactical_mastery();
    void given_1_of_5_tactical_mastery();
    void given_2_of_5_tactical_mastery();
    void given_3_of_5_tactical_mastery();
    void given_4_of_5_tactical_mastery();
    void given_5_of_5_tactical_mastery();
    void given_warrior_in_battle_stance();
    void given_warrior_in_berserker_stance();
    void given_warrior_in_defensive_stance();

    void given_warrior_is_on_gcd(Spell *spell);
    void given_warrior_is_on_gcd();
    void given_warrior_has_rage(const unsigned);

    void when_switching_to_battle_stance();
    void when_switching_to_berserker_stance();
    void when_switching_to_defensive_stance();

    void then_warrior_has_rage(const unsigned);
    void then_overpower_is_active();

protected:
    Warrior* warrior {nullptr};
    WarriorSpells* spells {nullptr};
};

#endif // TESTSPELLWARRIOR_H
