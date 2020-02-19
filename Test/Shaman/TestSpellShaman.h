#pragma once

#include "TestSpellDamage.h"

class LightningBolt;
class MainhandAttack;
class Shaman;
class Spell;
class Stormstrike;

class TestSpellShaman : public TestSpellDamage {
public:
    TestSpellShaman(EquipmentDb* equipment_db, QString spell_under_test);

    void set_up(const bool prepare_combat_iterations = true) override;
    void tear_down() override;

protected:
    Shaman* shaman;

    MainhandAttack* mh_attack() const;
    Stormstrike* stormstrike() const;
    LightningBolt* lightning_bolt() const;

    void run_class_specific_tests() override;

    void given_stormstrike_enabled();
    void given_clearcasting_enabled();
    void given_shaman_has_mana(const unsigned mana);
    void given_shaman_is_on_gcd();
    void given_shaman_is_on_gcd(Spell* spell);
    void given_relic_equipped(const int item_id);
    void given_no_relic_equipped();
    void then_shaman_has_mana(const unsigned mana);
    void when_mh_attack_is_performed();
    void when_stormstrike_is_performed();
};
