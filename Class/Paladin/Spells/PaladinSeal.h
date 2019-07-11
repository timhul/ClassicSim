#pragma once

#include "Spell.h"

class Buff;
class Paladin;

class PaladinSeal: public Spell {
public:
    PaladinSeal(QString name,
                QString icon,
                Paladin* pchar,
                const RestrictedByGcd restricted_by_gcd,
                const ResourceType resource_type,
                unsigned resource_cost,
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
