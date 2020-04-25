#pragma once

#include "TestSpellDamage.h"

class CatForm;
class Druid;
class Moonfire;
class MoonkinForm;
class BearForm;
class Maul;
class Shred;
class Swipe;
class Spell;
class Starfire;
class Wrath;
class FerociousBite;
class Enrage;

class TestSpellDruid : public TestSpellDamage {
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
    BearForm* bear_form() const;
    Shred* shred() const;
    Swipe* swipe() const;
    Maul* maul() const;
    FerociousBite* ferocious_bite() const;
    Enrage* enrage() const;

    void given_balance_talent_rank(const QString& talent_name, const unsigned num);
    void given_feral_talent_rank(const QString& talent_name, const unsigned num);
    void given_restoration_talent_rank(const QString& talent_name, const unsigned num);
    void given_balance_talent_ranks(const QVector<QPair<QString, unsigned>>& talent_ranks);
    void given_feral_talent_ranks(const QVector<QPair<QString, unsigned>>& talent_ranks);
    void given_druid_has_combo_points(const unsigned num);
    void given_druid_has_mana(const unsigned mana);
    void given_druid_has_energy(const unsigned energy);
    void given_druid_has_rage(const unsigned rage);
    void given_druid_is_on_gcd(Spell* spell);

    void then_druid_has_mana(const unsigned mana);
    void then_druid_has_energy(const unsigned energy);
    void then_druid_has_rage(const unsigned rage);
};
