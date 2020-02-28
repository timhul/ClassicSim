#pragma once

#include "Spell.h"

class Buff;

class SpellPeriodic : public Spell {
public:
    SpellPeriodic(const QString& name,
                  const QString& icon,
                  Character* pchar,
                  Buff* marker_buff,
                  const RestrictedByGcd restricted_by_gcd,
                  const ResourceType resource_type,
                  const double tick_rate,
                  unsigned resource_cost,
                  int spell_rank = 1);
    virtual ~SpellPeriodic() override;

    void perform_periodic(const int application_id);

    static double get_spell_coefficient_from_duration(const double duration);
    static double get_spell_coefficient_for_dot_portion_of_hybrid_spell(const double duration, const double cast_time);
    static double get_spell_coefficient_for_instant_portion_of_hybrid_spell(const double duration, const double cast_time);

    bool is_active() const;
    void invalidate();

protected:
    Buff* marker_buff;
    const double tick_rate;
    bool start_of_combat_spell {false};

    void add_next_tick();

    void spell_effect() override final;
    virtual bool check_application_success() = 0;
    virtual void new_application_effect() = 0;
    virtual void refresh_effect() = 0;
    virtual void reset_effect() override = 0;
    virtual void tick_effect() = 0;
    void enable_spell_effect() override final;
    void disable_spell_effect() override final;

private:
    int application_id {-1};

    void start_ticking();
};
