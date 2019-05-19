#ifndef RESOURCEGAINSPELL_H
#define RESOURCEGAINSPELL_H

#include "Spell.h"
#include "Resource.h"

#include <QVector>

class StatisticsResource;

class PeriodicResourceGainSpell : public Spell {
public:
    PeriodicResourceGainSpell(const QString& name,
                              const QString &icon,
                              Character* pchar,
                              bool restricted_by_gcd,
                              double cooldown,
                              double tick_rate,
                              double tick_until,
                              QVector<QPair<ResourceType, unsigned>> resource_gains);
    ~PeriodicResourceGainSpell() override;

    void perform_periodic() override;

private:
    double tick_rate;
    double tick_until;
    StatisticsResource* statistics_resource {nullptr};
    QVector<QPair<ResourceType, unsigned>> resource_gains;

    void spell_effect() override;
    void prepare_set_of_combat_iterations_spell_specific() override;
};

#endif // RESOURCEGAINSPELL_H
