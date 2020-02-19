#pragma once

#include <QVector>

#include "SpellPeriodic.h"

class StatisticsResource;

class PeriodicResourceGainSpell : public SpellPeriodic {
public:
    PeriodicResourceGainSpell(const QString& name,
                              const QString& icon,
                              Character* pchar,
                              const RestrictedByGcd restricted_by_gcd,
                              const double tick_rate,
                              const int duration,
                              QVector<QPair<ResourceType, unsigned>> resource_gains);
    ~PeriodicResourceGainSpell() override;

protected:
    StatisticsResource* statistics_resource {nullptr};

private:
    QVector<QPair<ResourceType, unsigned>> resource_gains;

    void prepare_set_of_combat_iterations_spell_specific() override final;

    bool check_application_success() override final;
    void new_application_effect() override;
    void refresh_effect() override final;
    void tick_effect() override final;
    void reset_effect() override;
};
