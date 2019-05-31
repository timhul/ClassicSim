#pragma once

#include "SpellCastingTime.h"
#include "TalentRequirer.h"

#include <QVector>

class Buff;
class Shaman;
class Random;

class LightningBolt: public SpellCastingTime {
public:
    LightningBolt(Shaman* pchar, const int spell_rank);
    ~LightningBolt() override;

    bool is_rank_learned() const override;

private:
    Random* random;
    unsigned base_damage_min;
    unsigned base_damage_max;
    double spell_dmg_coefficient;

    void spell_effect() override;
    void complete_cast_effect() override;
};
