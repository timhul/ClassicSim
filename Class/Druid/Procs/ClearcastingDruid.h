#pragma once

#include "ProcPPM.h"
#include "TalentRequirer.h"

#include <QVector>

class Buff;
class Druid;

class ClearcastingDruid: public ProcPPM, public TalentRequirer {
public:
    ClearcastingDruid(Druid* pchar);
    ~ClearcastingDruid() override;

private:
    friend class DruidSpells;

    Buff* buff;

    void proc_effect() override;
    unsigned get_proc_range() const override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
