
#include "ArmorPenetrationProc.h"
#include "ArmorPenetrationBuff.h"
#include "Character.h"
#include "ProcInfo.h"

ArmorPenetrationProc::ArmorPenetrationProc(Character* pchar,
                                           const QString& proc_name,
                                           const QString& icon,
                                           const QVector<ProcInfo::Source>& proc_sources,
                                           const double proc_rate,
                                           const int reduction,
                                           const int max_stacks,
                                           const int duration) :
    Proc(proc_name, icon, proc_rate, 0, QVector<Proc*>(), proc_sources, pchar),
    armor_penetration_buff(new ArmorPenetrationBuff(pchar, proc_name, reduction, max_stacks, duration))
{
    assert(proc_sources.contains(ProcInfo::Source::MainhandSwing) || proc_sources.contains(ProcInfo::Source::OffhandSwing));

    assert(max_stacks > 0);
    armor_penetration_buff->enable_buff();
}

ArmorPenetrationProc::~ArmorPenetrationProc() {
    armor_penetration_buff->disable_buff();
    delete armor_penetration_buff;
}

void ArmorPenetrationProc::proc_effect() {
    armor_penetration_buff->apply_buff();
}
