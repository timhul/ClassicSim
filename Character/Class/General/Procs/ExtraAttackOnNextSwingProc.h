#ifndef EXTRAATTACKONNEXTSWINGPROC_H
#define EXTRAATTACKONNEXTSWINGPROC_H

#include "Proc.h"

class ExtraAttackOnNextSwingBuff;
class ExtraAttackInstantProc;

class ExtraAttackOnNextSwingProc: public Proc {
public:
    ExtraAttackOnNextSwingProc(Engine* engine, Character* pchar, CombatRoll* roll,
                               QString proc_name, QVector<ProcInfo::Source> proc_sources,
                               const float proc_rate, const int num_attacks);
    ~ExtraAttackOnNextSwingProc();

    void proc_effect() override;

protected:
private:
    ExtraAttackInstantProc* extra_attack_instant_proc;
    ExtraAttackOnNextSwingBuff* extra_attack_buff;
};

#endif // EXTRAATTACKONNEXTSWINGPROC_H
