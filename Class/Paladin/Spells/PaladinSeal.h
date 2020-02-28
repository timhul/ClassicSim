#pragma once

#include "Spell.h"

class Buff;
class Paladin;
class PaladinSpells;

class PaladinSeal : public Spell {
public:
    PaladinSeal(QString name,
                QString icon,
                Paladin* paladin,
                const RestrictedByGcd restricted_by_gcd,
                const ResourceType resource_type,
                unsigned resource_cost,
                Buff* seal,
                Buff* judge_debuff);
    virtual ~PaladinSeal() override;

    Buff* get_buff() const;
    bool has_judge_debuff() const;
    virtual void refresh_seal() const = 0;

protected:
    friend class Judgement;

    Buff* seal;
    Buff* judge_debuff;

    void judge_seal();
    virtual void judge_effect() = 0;
    void spell_effect() override final;
};
