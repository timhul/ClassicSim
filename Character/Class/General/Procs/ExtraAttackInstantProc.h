#ifndef EXTRAATTACKPROC_H
#define EXTRAATTACKPROC_H

#include "Proc.h"

class ExtraAttackOnNextSwingBuff;

class ExtraAttackInstantProc: public Proc {
public:
    ExtraAttackInstantProc(Engine* engine, Character* pchar, CombatRoll* roll,
                           QVector<ProcInfo::Source> proc_sources, const float proc_rate);
    ~ExtraAttackInstantProc();

    void proc_effect() override;
    void set_extra_attack_buff(ExtraAttackOnNextSwingBuff* buff);

protected:
private:
    ExtraAttackOnNextSwingBuff* extra_attack_buff;

    void proc_from_next_swing_effect();
    void proc_from_instant_effect();
    void run_extra_attacks();
};

#endif // EXTRAATTACKPROC_H
