#ifndef TESTTWOHANDEDWEAPONSPECIALIZATION_H
#define TESTTWOHANDEDWEAPONSPECIALIZATION_H

class EquipmentDb;
class Race;
class TwoHandedWeaponSpecialization;
class Warrior;

class TestTwoHandedWeaponSpecialization {
public:
    TestTwoHandedWeaponSpecialization(EquipmentDb* equipment_db);

    void test_all();

    void test_name_is_correct();
    void test_damage_modified_when_using_2handers();
    void test_damage_not_modified_when_not_using_2handers();

    void test_damage_added_per_rank();

private:
    EquipmentDb* equipment_db;
    Warrior* warrior;
    TwoHandedWeaponSpecialization* talent;
    Race* race;

    void set_up();
    void tear_down();

    double delta(double lhs, double rhs);

    void test_basic_properties();

    void given_warrior_has_1h_axe_equipped_in_mainhand();
    void given_warrior_has_1h_mace_equipped_in_mainhand();
    void given_warrior_has_1h_sword_equipped_in_mainhand();
    void given_warrior_has_fist_weapon_equipped_in_mainhand();
    void given_warrior_has_dagger_equipped_in_mainhand();

    void given_warrior_has_no_mainhand();
    void given_warrior_has_no_offhand();

    void given_warrior_has_2h_axe_equipped();
    void given_warrior_has_2h_mace_equipped();
    void given_warrior_has_2h_sword_equipped();
    void given_warrior_has_polearm_equipped();
    void given_warrior_has_staff_equipped();
};

#endif // TESTTWOHANDEDWEAPONSPECIALIZATION_H
