#ifndef TESTUTILSWARRIOR_H
#define TESTUTILSWARRIOR_H

#include "TestUtils.h"

class Spell;
class Warrior;

class TestWarriorUtils : public TestUtils {
public:
    void given_warrior_has_1h_axe_equipped_in_mainhand(Warrior* warrior);
    void given_warrior_has_1h_mace_equipped_in_mainhand(Warrior* warrior);
    void given_warrior_has_1h_sword_equipped_in_mainhand(Warrior* warrior);
    void given_warrior_has_fist_weapon_equipped_in_mainhand(Warrior* warrior);
    void given_warrior_has_dagger_equipped_in_mainhand(Warrior* warrior);

    void given_warrior_has_no_mainhand(Warrior* warrior);
    void given_warrior_has_no_offhand(Warrior* warrior);

    void given_warrior_has_1h_axe_equipped_in_offhand(Warrior* warrior);
    void given_warrior_has_1h_mace_equipped_in_offhand(Warrior* warrior);
    void given_warrior_has_1h_sword_equipped_in_offhand(Warrior* warrior);
    void given_warrior_has_fist_weapon_equipped_in_offhand(Warrior* warrior);
    void given_warrior_has_dagger_equipped_in_offhand(Warrior* warrior);

    void given_warrior_has_2h_axe_equipped(Warrior* warrior);
    void given_warrior_has_2h_mace_equipped(Warrior* warrior);
    void given_warrior_has_2h_sword_equipped(Warrior* warrior);
    void given_warrior_has_polearm_equipped(Warrior* warrior);
    void given_warrior_has_staff_equipped(Warrior* warrior);
};

#endif // TESTUTILSWARRIOR_H
