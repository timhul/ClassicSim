#pragma once

#include "Proc.h"

class Buff;

enum class EnabledAtStart: bool {
    Yes = true,
    No = false,
};

enum class MaintainBuffEnabled: bool {
    Yes = true,
    No = false,
};

class GenericBuffProc: public Proc {
public:
    GenericBuffProc(Character* pchar,
                    const QString& proc_name,
                    const QString& icon,
                    const QVector<ProcInfo::Source>& proc_sources,
                    const double proc_rate,
                    const EnabledAtStart enabled_at_start,
                    const MaintainBuffEnabled maintain_buff_enabled,
                    Buff* buff);
    ~GenericBuffProc() override;

private:
    const EnabledAtStart enabled_at_start;
    const MaintainBuffEnabled maintain_buff_enabled;
    Buff* buff;
    void proc_effect() override;

    void enable_spell_effect() override;
    void disable_spell_effect() override;
};
