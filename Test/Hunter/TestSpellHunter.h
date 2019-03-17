#ifndef TESTSPELLHUNTER_H
#define TESTSPELLHUNTER_H

#include "Hunter.h"
#include "HunterSpells.h"
#include "TestSpellDamage.h"

class TestSpellHunter: public TestSpellDamage {
public:
    TestSpellHunter(EquipmentDb* equipment_db, QString spell_under_test);

    void set_up(const bool prepare_combat_iterations = true) override;
    void tear_down() override;

    void given_hunter_has_mana(const unsigned mana);
    void then_hunter_has_mana(const unsigned mana);

protected:
    Hunter* hunter;
};

#endif // TESTSPELLHUNTER_H
