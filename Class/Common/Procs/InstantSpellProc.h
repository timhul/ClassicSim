#pragma once

#include "Proc.h"
#include "MagicSchools.h"

class InstantSpellAttack;

enum class ConsumeCharge : bool;

class InstantSpellProc: public Proc {
public:
    InstantSpellProc(Character* pchar,
                     const QString& proc_name,
                     const QString &icon,
                     const QVector<ProcInfo::Source>& proc_sources,
                     const double proc_rate,
                     const MagicSchool school,
                     const unsigned min_damage,
                     const unsigned max_damage,
                     const double spell_coefficient,
                     const ConsumeCharge consume_charge);
    ~InstantSpellProc() override;

private:
    InstantSpellAttack* spell;
    void proc_effect() override;
};
