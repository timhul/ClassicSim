#ifndef ProcPPM_H
#define ProcPPM_H

#include "Proc.h"
#include "ProcInfo.h"

namespace EnchantSlot {
    static const int MAINHAND = 0;
    static const int OFFHAND = 1;
}

class ProcPPM: public Proc {
public:
    ProcPPM(const QString &name, const int weapon, const double ppm, const double inner_cooldown,
            const bool recursive, const QVector<Proc*> linked_procs,
            const QVector<ProcInfo::Source> proc_sources,
            Engine* engine, Character* pchar, CombatRoll* roll);
    ~ProcPPM();

    virtual void proc_effect() = 0;

    virtual int get_proc_range() const;

protected:
    const double proc_rate_base;
    const int weapon;
private:
};


#endif // ProcPPM_H
