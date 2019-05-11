#ifndef EXTRAATTACKONNEXTSWINGPROC_H
#define EXTRAATTACKONNEXTSWINGPROC_H

#include "Proc.h"

class ExtraAttackOnNextSwingBuff;
class ExtraAttackInstantProc;

class ExtraAttackOnNextSwingProc: public Proc {
public:
    ExtraAttackOnNextSwingProc(Character* pchar,
                               const QString& proc_name,
                               const QString &icon,
                               const QVector<ProcInfo::Source>& proc_sources,
                               const double proc_rate,
                               const int num_attacks);
    ~ExtraAttackOnNextSwingProc() override;

    void proc_effect() override;

private:
    ExtraAttackInstantProc* extra_attack_instant_proc;
    ExtraAttackOnNextSwingBuff* extra_attack_buff;

    void prepare_set_of_combat_iterations_spell_specific() override;
};

#endif // EXTRAATTACKONNEXTSWINGPROC_H
