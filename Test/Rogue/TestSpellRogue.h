#ifndef TESTSPELLROGUE_H
#define TESTSPELLROGUE_H

#include "Rogue.h"
#include "RogueSpells.h"
#include "TestSpellDamage.h"

class TestSpellRogue: public TestSpellDamage {
public:
    TestSpellRogue(EquipmentDb* equipment_db, const QString &spell_under_test);

    void set_up(const bool prepare_combat_iterations = true) override;
    void tear_down() override;

    virtual void test_combo_points() = 0;
    virtual void test_stealth() = 0;

    void given_rogue_is_on_gcd(Spell *spell);
    void given_rogue_is_on_gcd();
    void given_rogue_in_stealth();
    void given_rogue_not_in_stealth();
    void given_rogue_has_energy(const unsigned);

    void then_rogue_has_energy(const unsigned) const;
    void then_rogue_has_combo_points(const unsigned) const;

protected:
    Rogue* rogue;
};

#endif // TESTSPELLROGUE_H
