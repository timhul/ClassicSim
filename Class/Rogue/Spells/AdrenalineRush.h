#pragma once

#include "Spell.h"
#include "TalentRequirer.h"

class AdrenalineRushBuff;
class Rogue;

class AdrenalineRush: public Spell, public TalentRequirer {
public:
    AdrenalineRush(Rogue* rogue);
    ~AdrenalineRush() override;

private:
    Rogue* rogue;
    AdrenalineRushBuff* ar_buff;

    void spell_effect() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
