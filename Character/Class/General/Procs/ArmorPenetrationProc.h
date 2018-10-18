#ifndef ARMORPENETRATIONPROC_H
#define ARMORPENETRATIONPROC_H

#include "Proc.h"

class ArmorPenetrationBuff;

class ArmorPenetrationProc: public Proc {
public:
    ArmorPenetrationProc(Character* pchar,
                         const QString& proc_name,
                         const QVector<ProcInfo::Source>& proc_sources,
                         const double proc_rate,
                         const int reduction,
                         const int max_stacks,
                         const int duration);
    ~ArmorPenetrationProc() override;

private:
    ArmorPenetrationBuff* armor_penetration_buff;
    void proc_effect() override;
};

#endif // ARMORPENETRATIONPROC_H
