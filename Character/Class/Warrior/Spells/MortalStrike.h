#ifndef MORTALSTRIKE_H
#define MORTALSTRIKE_H

#include "Spell.h"
#include "TalentRequirer.h"

class Warrior;

class MortalStrike: public Spell, public TalentRequirer {
public:
    MortalStrike(Character* pchar);

protected:
private:
    friend class MortalStrikeTalent;

    Warrior* warr;

    void spell_effect() override;

    void increase_talent_rank_effect(const int curr, const QString& talent_name) override;
    void decrease_talent_rank_effect(const int curr, const QString& talent_name) override;
};

#endif // MORTALSTRIKE_H
