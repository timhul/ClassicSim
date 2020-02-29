#pragma once

#include "TestSpellDamage.h"

class ShadowBolt;
class Warlock;

class TestSpellWarlock : public TestSpellDamage {
public:
    TestSpellWarlock(EquipmentDb* equipment_db, QString spell_under_test);

    void set_up(const bool prepare_combat_iterations = true) override;
    void tear_down() override;

protected:
    Warlock* warlock;

    ShadowBolt* shadow_bolt() const;

    void run_class_specific_tests() override;

    void given_ruin_enabled();
    void given_destruction_talent_rank(const QString& talent_name, const unsigned num);
    void given_demonology_talent_rank(const QString& talent_name, const unsigned num);

    void given_warlock_has_mana(const unsigned mana);
    void given_warlock_is_on_gcd(Spell* spell);

    void then_warlock_has_mana(const unsigned mana);
};
