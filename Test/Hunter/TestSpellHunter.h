#ifndef TESTSPELLHUNTER_H
#define TESTSPELLHUNTER_H

#include "Hunter.h"
#include "HunterSpells.h"
#include "TestSpellDamage.h"

class TestSpellHunter: public TestSpellDamage {
public:
    TestSpellHunter(EquipmentDb* equipment_db, QString spell_under_test);

protected:
    Hunter* hunter;

    void set_up(const bool prepare_combat_iterations = true) override;
    void tear_down() override;

    void given_hunter_is_on_gcd();
    void given_1_of_5_efficiency();
    void given_2_of_5_efficiency();
    void given_3_of_5_efficiency();
    void given_4_of_5_efficiency();
    void given_5_of_5_efficiency();

    void given_1_of_5_mortal_shots();
    void given_2_of_5_mortal_shots();
    void given_3_of_5_mortal_shots();
    void given_4_of_5_mortal_shots();
    void given_5_of_5_mortal_shots();

    void given_1_of_5_ranged_weapon_specialization();
    void given_2_of_5_ranged_weapon_specialization();
    void given_3_of_5_ranged_weapon_specialization();
    void given_4_of_5_ranged_weapon_specialization();
    void given_5_of_5_ranged_weapon_specialization();

    void given_1_of_3_monster_slaying();
    void given_2_of_3_monster_slaying();
    void given_3_of_3_monster_slaying();

    void given_hunter_has_mana(const unsigned mana);
    void then_hunter_has_mana(const unsigned mana);
};

#endif // TESTSPELLHUNTER_H
