#ifndef ADRENALINERUSH_H
#define ADRENALINERUSH_H

#include "Spell.h"
#include "TalentRequirer.h"

class AdrenalineRushBuff;
class Rogue;

class AdrenalineRush: public Spell, public TalentRequirer {
public:
    AdrenalineRush(Character* pchar);
    ~AdrenalineRush() override;

protected:
private:
    friend class AdrenalineRushTalent;

    Rogue* rogue;
    AdrenalineRushBuff* ar_buff;

    void spell_effect() override;

    void increase_talent_rank_effect(const QString& talent_name) override;
    void decrease_talent_rank_effect(const QString& talent_name) override;
};

#endif // ADRENALINERUSH_H
