#pragma once

#include "TestSpellDamage.h"

class Druid;
class Moonfire;
class Spell;
class Wrath;

class TestSpellDruid: public TestSpellDamage {
public:
    TestSpellDruid(EquipmentDb* equipment_db, QString spell_under_test);

    void set_up(const bool prepare_combat_iterations = true) override;
    void tear_down() override;

protected:
    Druid* druid;

    void run_class_specific_tests() override;

    Wrath* wrath() const;
    Moonfire* moonfire() const;

    void given_balance_talent_rank(const QString& talent_name, const unsigned num);
    void given_feral_talent_rank(const QString& talent_name, const unsigned num);
    void given_restoration_talent_rank(const QString& talent_name, const unsigned num);

    void given_druid_has_mana(const unsigned mana);
    void given_druid_is_on_gcd(Spell* spell);

    void then_druid_has_mana(const unsigned mana);
};
