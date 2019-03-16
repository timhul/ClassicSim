#ifndef RESOURCEGAINSPELL_H
#define RESOURCEGAINSPELL_H

#include "Spell.h"
#include "Resource.h"

#include <QMap>


class PeriodicResourceGainSpell : public Spell {
public:
    PeriodicResourceGainSpell(const QString& name,
                              const QString &icon,
                              Character* pchar,
                              bool restricted_by_gcd,
                              double cooldown,
                              double tick_rate,
                              double tick_until,
                              QMap<ResourceType, unsigned> resource_gains);

    void perform_periodic() override;

private:
    double tick_rate;
    double tick_until;
    QMap<ResourceType, unsigned> resource_gains;

    void spell_effect() override;

};

#endif // RESOURCEGAINSPELL_H
