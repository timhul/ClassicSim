#include "GenericBuffProc.h"

#include "Buff.h"
#include "EnabledProcs.h"
#include "ProcInfo.h"
#include "Utils/Check.h"

GenericBuffProc::GenericBuffProc(
        Character* pchar,
        const QString& proc_name,
        const QString& icon,
        const QVector<ProcInfo::Source>& proc_sources,
        const double proc_rate,
        Buff* buff) :
    Proc(proc_name, icon, proc_rate, 0, QVector<Proc*>(), proc_sources, pchar),
    buff(buff)
{
    check(!proc_sources.empty(), "Must specify at least one proc source");
    buff->enable_buff();
}

GenericBuffProc::~GenericBuffProc() {
    if (buff->is_enabled())
        buff->disable_buff();

    delete buff;
}

void GenericBuffProc::proc_effect() {
    buff->apply_buff();
}
