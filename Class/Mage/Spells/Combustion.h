#pragma once

#include "Spell.h"
#include "TalentRequirer.h"

class Buff;
class Mage;

class Combustion: public Spell, public TalentRequirer {
public:
    Combustion(Mage* pchar);
    ~Combustion() override;

    void use_charge();
    void stack_crit_chance();

private:
    Buff* buff;

    void spell_effect() override;

    SpellStatus is_ready_spell_specific() const override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
