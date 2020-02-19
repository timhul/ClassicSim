#include "GenericBuffProc.h"

#include "Buff.h"
#include "Utils/Check.h"

GenericBuffProc::GenericBuffProc(Character* pchar,
                                 const QString& proc_name,
                                 const QString& icon,
                                 const QVector<ProcInfo::Source>& proc_sources,
                                 const double proc_rate,
                                 const EnabledAtStart enabled_at_start,
                                 const MaintainBuffEnabled maintain_buff_enabled,
                                 Buff* buff) :
    Proc(proc_name, icon, proc_rate, 0, QVector<Proc*>(), proc_sources, pchar),
    enabled_at_start(enabled_at_start),
    maintain_buff_enabled(maintain_buff_enabled),
    buff(buff) {
    check(!proc_sources.empty(), "Must specify at least one proc source");

    if (enabled_at_start == EnabledAtStart::No) {
        enabled = false;
        if (maintain_buff_enabled == MaintainBuffEnabled::Yes && buff->is_enabled())
            buff->disable_buff();
    } else if (maintain_buff_enabled == MaintainBuffEnabled::Yes && !buff->is_enabled())
        buff->enable_buff();
}

GenericBuffProc::~GenericBuffProc() {
    if (maintain_buff_enabled == MaintainBuffEnabled::No)
        return;

    if (buff->is_enabled())
        buff->disable_buff();

    delete buff;
}

void GenericBuffProc::proc_effect() {
    buff->apply_buff();
}

void GenericBuffProc::enable_spell_effect() {
    if (maintain_buff_enabled == MaintainBuffEnabled::Yes)
        buff->enable_buff();
}

void GenericBuffProc::disable_spell_effect() {
    if (maintain_buff_enabled == MaintainBuffEnabled::Yes)
        buff->disable_buff();
}
