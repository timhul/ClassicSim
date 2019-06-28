#pragma once

#include "Spell.h"

class SpellCastingTime: public Spell {
public:
    SpellCastingTime(const QString& name,
                     const QString& icon,
                     Character* pchar,
                     CooldownControl* cooldown_control,
                     bool restricted_by_gcd,
                     const ResourceType resource_type,
                     unsigned resource_cost,
                     int spell_rank = 1);

    double get_cast_time() const;

    void complete_cast();

protected:
    unsigned casting_time_ms {std::numeric_limits<unsigned>::max()};
    unsigned cast_id {std::numeric_limits<unsigned>::max()};

    void start_cast();

    virtual void reset_effect();
    virtual void complete_cast_effect() = 0;

    double spell_coefficient_from_casting_time() const;
};
