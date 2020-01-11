#pragma once

#include "Hunter.h"
#include "HunterSpells.h"
#include "TestSpellDamage.h"

class MultiShot;

class TestSpellHunter: public TestSpellDamage {
public:
    TestSpellHunter(EquipmentDb* equipment_db, QString spell_under_test);

protected:
    Hunter* hunter;

    void set_up(const bool prepare_combat_iterations = true) override;
    void tear_down() override;

    MultiShot* multi_shot() const;

    void given_hunter_is_on_gcd();
    void given_beast_mastery_talent_rank(const QString& talent_name, const unsigned num);
    void given_marksmanship_talent_rank(const QString& talent_name, const unsigned num);
    void given_survival_talent_rank(const QString& talent_name, const unsigned num);
    void given_mortal_shots_rank(const unsigned num);

    void given_hunter_has_mana(const unsigned mana);
    void then_hunter_has_mana(const unsigned mana);
};
