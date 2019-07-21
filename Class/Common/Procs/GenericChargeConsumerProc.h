#pragma once

#include "Proc.h"

class Buff;

class GenericChargeConsumerProc: public Proc {
public:
    GenericChargeConsumerProc(Character* pchar,
                              const QString& proc_name,
                              const QString& icon,
                              const QVector<ProcInfo::Source>& proc_sources,
                              const double proc_rate,
                              Buff *buff);

private:
    Buff* buff;
    void proc_effect() override;

    bool proc_specific_conditions_fulfilled() const override;
};
