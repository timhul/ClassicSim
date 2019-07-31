#pragma once

#include "SpellPeriodic.h"

#include <QVector>

enum class MagicSchool: int;
enum class Priority : int;

class PeriodicDamageSpell : public SpellPeriodic {
public:
    PeriodicDamageSpell(const QString& name,
                        const QString& icon,
                        Character* pchar,
                        const Priority priority,
                        const RestrictedByGcd restricted_by_gcd,
                        const MagicSchool school,
                        const double tick_rate,
                        const int duration,
                        const unsigned full_duration_dmg,
                        const unsigned resource_cost,
                        const double cast_time_ms,
                        const double spell_coefficient);
    ~PeriodicDamageSpell() override;

private:
    const MagicSchool school;
    const unsigned full_duration_dmg;
    const double duration;
    const double spell_coefficient;
    const double num_ticks;
    const double reported_resource_cost;
    const double reported_execution_time;

    double tick_rest {0.0};

    bool check_application_success() override;
    void new_application_effect() override;
    void refresh_effect() override;
    void tick_effect() override;
    void reset_effect() override;
};
