#ifndef PALADINSEAL_H
#define PALADINSEAL_H

#include "Spell.h"

class Buff;
class Paladin;

class PaladinSeal: public Spell {
public:
    PaladinSeal(QString name,
                QString icon,
                Paladin* pchar,
                bool restricted_by_gcd,
                double cooldown,
                const ResourceType resource_type,
                int resource_cost,
                Buff* seal,
                Buff* judge_debuff);
    virtual ~PaladinSeal() override;

    Buff* get_buff() const;

private:
    friend class Judgement;

    Buff* seal;
    Buff* judge_debuff;

    void judge_seal();
    void spell_effect() override final;
};

#endif // PALADINSEAL_H
