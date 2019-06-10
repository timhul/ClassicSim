#pragma once

#include "Spell.h"
#include "TalentRequirer.h"

class Buff;
class HuntersMarkBuff;

class HuntersMark: public Spell, public TalentRequirer {
public:
    HuntersMark(Character *pchar, HuntersMarkBuff* hunters_mark);
    ~HuntersMark() override;

private:
    HuntersMarkBuff* hunters_mark;
    QVector<double> imp_hunters_mark_ranks;
    unsigned hunters_mark_bonus;
    const unsigned base_ranged_ap_bonus;

    void spell_effect() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
