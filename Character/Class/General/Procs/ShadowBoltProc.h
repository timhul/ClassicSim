#ifndef SHADOWBOLTPROC_H
#define SHADOWBOLTPROC_H

#include "Proc.h"

class ShadowBoltAttack;

class ShadowBoltProc: public Proc {
public:
    ShadowBoltProc(Character* pchar,
                         const QString& proc_name,
                         const QVector<ProcInfo::Source>& proc_sources,
                         const double proc_rate,
                         const unsigned min_damage,
                         const unsigned max_damage);
    ~ShadowBoltProc() override;

private:
    ShadowBoltAttack* shadow_bolt;
    void proc_effect() override;
};

#endif // SHADOWBOLTPROC_H
