#pragma once

#include "Spell.h"

class Druid;
class DruidSpells;
class TigersFuryBuff;

class TigersFury : public Spell {
public:
    TigersFury(Druid* pchar, DruidSpells* druid_spells, TigersFuryBuff* buff, const int spell_rank);
    ~TigersFury() override;

    bool is_rank_learned() const override;

private:
    Druid* druid;
    DruidSpells* druid_spells;
    TigersFuryBuff* buff;

    unsigned bonus_damage;

    void spell_effect() override;
    SpellStatus is_ready_spell_specific() const override;
};
