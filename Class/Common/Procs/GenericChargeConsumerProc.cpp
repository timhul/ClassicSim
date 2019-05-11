#include "GenericChargeConsumerProc.h"

#include "Buff.h"
#include "EnabledProcs.h"
#include "ProcInfo.h"
#include "Utils/Check.h"

GenericChargeConsumerProc::GenericChargeConsumerProc(
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
}

void GenericChargeConsumerProc::proc_effect() {
    buff->use_charge();
}

bool GenericChargeConsumerProc::proc_specific_conditions_fulfilled() const {
    return buff->is_active();
}
