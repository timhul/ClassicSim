#pragma once

#include "Proc.h"
#include "TalentRequirer.h"

#include <QVector>

class Buff;
class Mage;

class ClearcastingMage: public Proc, public TalentRequirer {
public:
    ClearcastingMage(Mage* pchar);
    ~ClearcastingMage() override;

private:
    friend class MageSpells;

    Buff* buff;

    const QVector<unsigned> proc_ranges;

    void proc_effect() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
