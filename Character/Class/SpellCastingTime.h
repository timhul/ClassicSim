#ifndef SPELLCASTINGTIME_H
#define SPELLCASTINGTIME_H

#include "Spell.h"

class SpellCastingTime: public Spell {
public:
    SpellCastingTime(const QString& name,
                     Character* pchar,
                     bool restricted_by_gcd,
                     double cooldown,
                     int resource_cost,
                     int casting_time_ms);

    double get_cast_time() const;

    void complete_cast();

protected:
    int casting_time_ms;
    bool cast_in_progress;

    void start_cast();

    virtual bool is_ready_spell_specific() const override;

    virtual void complete_cast_effect() = 0;
};

#endif // SPELLCASTINGTIME_H
