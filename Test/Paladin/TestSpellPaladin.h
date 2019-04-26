#ifndef TESTSPELLPALADIN_H
#define TESTSPELLPALADIN_H

#include "TestSpellDamage.h"
#include "Paladin.h"
#include "PaladinSpells.h"

class TestSpellPaladin: public TestSpellDamage {
public:
    TestSpellPaladin(EquipmentDb* equipment_db, QString spell_under_test);

    void set_up(const bool prepare_combat_iterations = true) override;
    void tear_down() override;

protected:
    Paladin* paladin;

    void run_class_specific_tests() override;

    void given_paladin_is_on_gcd(Spell* spell);
    void given_paladin_is_on_gcd();
    void given_paladin_has_mana(const unsigned mana);
    void then_paladin_has_mana(const unsigned mana);
};

#endif // TESTSPELLPALADIN_H
