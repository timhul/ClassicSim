#pragma once

#include "Proc.h"

class Spell;

class GenericSpellProc: public Proc {
public:
    GenericSpellProc(Character* pchar,
                    const QString& proc_name,
                    const QString& icon,
                    const QVector<ProcInfo::Source>& proc_sources,
                    const double proc_rate,
                    Spell* spell);
    ~GenericSpellProc() override;

private:
    Spell* spell;
    void proc_effect() override;
};
