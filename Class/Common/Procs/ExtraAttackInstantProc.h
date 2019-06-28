#pragma once

#include "Proc.h"

class ExtraAttackOnNextSwingBuff;

class ExtraAttackInstantProc: public Proc {
public:
    ExtraAttackInstantProc(Character* pchar,
                           const QString& proc_name,
                           const QString& icon,
                           const QVector<ProcInfo::Source>& proc_sources,
                           const double proc_rate,
                           const int num_attacks);
    ~ExtraAttackInstantProc() override = default;

    void proc_effect() override;
    void set_extra_attack_buff(ExtraAttackOnNextSwingBuff* buff);

private:
    ExtraAttackOnNextSwingBuff* extra_attack_buff;

    const int num_attacks;

    void proc_from_next_swing_effect();
    void proc_from_instant_effect();
    void run_extra_attacks();
};
