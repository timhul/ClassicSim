#pragma once
#include "Proc.h"

class FelstrikerBuff;

class FelstrikerProc : public Proc {
public:
    FelstrikerProc(Character* pchar, const QString& name, const QVector<ProcInfo::Source>& proc_sources, const double proc_rate, const int duration);
    ~FelstrikerProc() override;

private:
    FelstrikerBuff* felstriker_buff;
    void proc_effect() override;
};
