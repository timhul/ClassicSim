
#include "GenericChargeConsumerProc.h"
#include "Character.h"
#include "ProcInfo.h"
#include "Spells.h"
#include "Buff.h"
#include "EnabledProcs.h"

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
    assert(!proc_sources.empty());
}

GenericChargeConsumerProc::~GenericChargeConsumerProc() {

}

void GenericChargeConsumerProc::proc_effect() {
    buff->use_charge();
}

bool GenericChargeConsumerProc::proc_specific_conditions_fulfilled() const {
    return buff->is_active();
}
