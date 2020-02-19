#pragma once

#include "Spell.h"
#include "TalentRequirer.h"

class Shaman;
class ShamanSpells;
class StormstrikeBuff;

class Stormstrike : public Spell, public TalentRequirer {
public:
    Stormstrike(Shaman* pchar, ShamanSpells* spells, StormstrikeBuff* buff);
    ~Stormstrike() override;

private:
    Shaman* shaman;
    ShamanSpells* spells;
    Buff* stormstrike_buff;

    void spell_effect() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
