
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
                                           const int duration,
                                           const bool extend_duration_on_proc) :
    Proc(proc_name, icon, proc_rate, 0, QVector<Proc*>(), proc_sources, pchar),
    extend_duration_on_proc(extend_duration_on_proc),
    proc_requirement_buff(nullptr),
    armor_penetration_buff(new ArmorPenetrationBuff(pchar, proc_name, icon, reduction, max_stacks, duration))
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
    if (extend_duration_on_proc || !armor_penetration_buff->is_active())
        armor_penetration_buff->apply_buff();
    else
        armor_penetration_buff->refresh_buff();
}

ArmorPenetrationBuff* ArmorPenetrationProc::get_buff() const {
    return this->armor_penetration_buff;
}

void ArmorPenetrationProc::set_proc_requirement_buff(Buff* buff) {
    this->proc_requirement_buff = buff;
}

bool ArmorPenetrationProc::proc_specific_conditions_fulfilled() const {
    return proc_requirement_buff == nullptr ? true : proc_requirement_buff->is_active();
}
