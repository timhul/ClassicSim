#pragma once

#include "Proc.h"
#include "TalentRequirer.h"

#include <QVector>

class Mage;
class SharedDebuff;

class ImprovedScorch: public Proc, public TalentRequirer {
public:
    ImprovedScorch(Mage* pchar, SharedDebuff* fire_vulnerability);

private:
    friend class MageSpells;

    SharedDebuff* debuff;

    const QVector<unsigned> proc_ranges;

    void proc_effect() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
