#pragma once

#include "TestSpellDamage.h"

class Evocation;
class Fireball;
class Frostbolt;
class Mage;
class Scorch;
class Spell;

class TestSpellMage: public TestSpellDamage {
public:
    TestSpellMage(EquipmentDb* equipment_db, QString spell_under_test);

    void set_up(const bool prepare_combat_iterations = true) override;
    void tear_down() override;

protected:
    Mage* mage;

    Fireball* fireball() const;
    Scorch* scorch() const;
    Frostbolt* frostbolt() const;
    Evocation* evocation() const;

    void run_class_specific_tests() override;

    void given_fire_talent_rank(const QString& talent_name, const unsigned num);
    void given_frost_talent_rank(const QString& talent_name, const unsigned num);

    void given_mage_has_mana(const unsigned mana);
    void given_mage_is_on_gcd(Spell* spell);

    void then_mage_has_mana(const unsigned mana);
};
