#pragma once

#include "Proc.h"

class ArmorPenetrationBuff;
class Buff;

const static bool REFRESH_EXTENDS_DURATION = true;
const static bool REFRESH_DOES_NOT_EXTEND_DURATION = false;

class ArmorPenetrationProc: public Proc {
public:
    ArmorPenetrationProc(Character* pchar,
                         const QString& proc_name,
                         const QString &icon,
                         const QVector<ProcInfo::Source>& proc_sources,
                         const double proc_rate,
                         const int reduction,
                         const int max_stacks,
                         const int duration,
                         const bool extend_duration_on_proc);
    ~ArmorPenetrationProc() override;

    ArmorPenetrationBuff* get_buff() const;
    void set_proc_requirement_buff(Buff*);

private:
    const bool extend_duration_on_proc;
    Buff* proc_requirement_buff;
    ArmorPenetrationBuff* armor_penetration_buff;

    void proc_effect() override;
    bool proc_specific_conditions_fulfilled() const override;
};
