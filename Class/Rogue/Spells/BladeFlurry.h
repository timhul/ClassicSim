#pragma once

#include "Spell.h"
#include "TalentRequirer.h"

class BladeFlurryBuff;
class Rogue;

class BladeFlurry : public Spell, public TalentRequirer {
public:
    BladeFlurry(Rogue* rogue);
    ~BladeFlurry() override;

private:
    Rogue* rogue;
    BladeFlurryBuff* bf_buff;

    void spell_effect() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
