#pragma once

#include "TestSpellDamage.h"

class CatForm;
class Druid;
class Moonfire;
class MoonkinForm;
class Shred;
class Spell;
class Starfire;
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
    Starfire* starfire() const;
    MoonkinForm* moonkin_form() const;
    CatForm* cat_form() const;
    Shred* shred() const;

    void given_balance_talent_rank(const QString& talent_name, const unsigned num);
    void given_feral_talent_rank(const QString& talent_name, const unsigned num);
    void given_restoration_talent_rank(const QString& talent_name, const unsigned num);
    void given_balance_talent_ranks(const QVector<QPair<QString, unsigned>>& talent_ranks);

    void given_druid_has_mana(const unsigned mana);
    void given_druid_is_on_gcd(Spell* spell);

    void then_druid_has_mana(const unsigned mana);
    void then_druid_has_energy(const unsigned energy);
};
