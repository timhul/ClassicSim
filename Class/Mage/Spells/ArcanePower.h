#pragma once

#include "Spell.h"
#include "TalentRequirer.h"

class Buff;
class Mage;

class ArcanePower: public Spell, public TalentRequirer {
public:
    ArcanePower(Mage* pchar);
    ~ArcanePower() override;

private:
    Buff* buff;

    void spell_effect() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
