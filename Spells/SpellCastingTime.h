#ifndef SPELLCASTINGTIME_H
#define SPELLCASTINGTIME_H

#include "Spell.h"

class SpellCastingTime: public Spell {
public:
    SpellCastingTime(const QString& name,
                     const QString& icon,
                     Character* pchar,
                     bool restricted_by_gcd,
                     double cooldown,
                     const ResourceType resource_type,
                     unsigned resource_cost,
                     unsigned casting_time_ms);

    double get_cast_time() const;

    void complete_cast();

protected:
    unsigned casting_time_ms;
    unsigned cast_id;

    void start_cast();

    virtual void reset_effect();
    virtual void complete_cast_effect() = 0;
};

#endif // SPELLCASTINGTIME_H
