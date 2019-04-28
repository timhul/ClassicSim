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
                Buff* seal);
    virtual ~PaladinSeal() override;

    Buff* get_buff() const;
    virtual void refresh_seal() const = 0;

protected:
    friend class Judgement;

    Buff* seal;

    void judge_seal();
    virtual void judge_effect() = 0;
    void spell_effect() override final;
};

#endif // PALADINSEAL_H
