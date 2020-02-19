#pragma once

#include "TestSpellDamage.h"

class Judgement;
class MainhandAttackPaladin;
class Paladin;
class SealOfCommand;
class SealOfTheCrusader;
class Spell;

class TestSpellPaladin : public TestSpellDamage {
public:
    TestSpellPaladin(EquipmentDb* equipment_db, QString spell_under_test);

    void set_up(const bool prepare_combat_iterations = true) override;
    void tear_down() override;

protected:
    Paladin* paladin;

    void run_class_specific_tests() override;

    Judgement* judgement() const;
    MainhandAttackPaladin* mh_attack() const;
    SealOfCommand* seal_of_command() const;
    SealOfTheCrusader* seal_of_the_crusader() const;

    void given_paladin_has_mana(const unsigned mana);
    void given_paladin_is_on_gcd();
    void given_paladin_is_on_gcd(Spell* spell);
    void given_relic_equipped(const int item_id);
    void given_no_relic_equipped();
    void given_sanctity_aura_is_active();
    void given_seal_of_command_is_active();
    void given_seal_of_command_is_enabled();
    void given_seal_of_the_crusader_is_active();

    void given_holy_talent_rank(const QString& talent_name, const unsigned num);
    void given_protection_talent_rank(const QString& talent_name, const unsigned num);
    void given_retribution_talent_rank(const QString& talent_name, const unsigned num);

    void given_vengeance_is_active(const unsigned num);
    void then_next_expected_use_is(const double next_expected_use);
    void then_paladin_has_mana(const unsigned mana);
    void when_judgement_is_performed();
    void when_mh_attack_is_performed();
    void when_seal_of_command_is_performed();
    void when_seal_of_the_crusader_is_performed();
};
