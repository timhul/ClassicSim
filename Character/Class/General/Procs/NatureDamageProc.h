#ifndef NATUREDAMAGEPROC_H
#define NATUREDAMAGEPROC_H

#include "Proc.h"

class NatureDamageAttack;

class NatureDamageProc: public Proc {
public:
    NatureDamageProc(Character* pchar,
                         const QString& proc_name,
                         const QVector<ProcInfo::Source>& proc_sources,
                         const double proc_rate,
                         const unsigned min_damage,
                         const unsigned max_damage);
    ~NatureDamageProc() override;

private:
    NatureDamageAttack* nature_damage;
    void proc_effect() override;
};

#endif // NATUREDAMAGEPROC_H
