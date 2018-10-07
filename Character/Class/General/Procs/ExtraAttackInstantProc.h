#ifndef EXTRAATTACKPROC_H
#define EXTRAATTACKPROC_H

#include "Proc.h"

class ExtraAttackOnNextSwingBuff;

class ExtraAttackInstantProc: public Proc {
public:
    ExtraAttackInstantProc(Character* pchar,
                           const QString& proc_name,
                           const QVector<ProcInfo::Source>& proc_sources,
                           const double proc_rate,
                           const int num_attacks);
    ~ExtraAttackInstantProc() override;

    void proc_effect() override;
    void set_extra_attack_buff(ExtraAttackOnNextSwingBuff* buff);

protected:
private:
    ExtraAttackOnNextSwingBuff* extra_attack_buff;

    const int num_attacks;

    void proc_from_next_swing_effect();
    void proc_from_instant_effect();
    void run_extra_attacks();
};

#endif // EXTRAATTACKPROC_H
