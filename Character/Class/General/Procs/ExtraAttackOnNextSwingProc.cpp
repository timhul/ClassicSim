
#include "ExtraAttackOnNextSwingProc.h"
#include "Character.h"
#include "StatisticsResource.h"
#include "ProcInfo.h"
#include "ExtraAttackInstantProc.h"
#include "ExtraAttackOnNextSwingBuff.h"

ExtraAttackOnNextSwingProc::ExtraAttackOnNextSwingProc(Engine* engine, Character* pchar,
                                                       CombatRoll* roll,
                                                       QVector<ProcInfo::Source> proc_sources,
                                                       const float proc_rate,
                                                       const int num_attacks) :
    Proc("Extra Attack On Next Swing Proc", proc_rate, 0, false, QVector<Proc*>(), proc_sources, engine, pchar, roll),
    extra_attack_instant_proc(new ExtraAttackInstantProc(engine, pchar, roll, proc_sources, 1.0)),
    extra_attack_buff(new ExtraAttackOnNextSwingBuff(pchar, extra_attack_instant_proc, num_attacks))
{
    assert(proc_sources.contains(ProcInfo::Source::MainhandSwing) || proc_sources.contains(ProcInfo::Source::OffhandSwing));
    extra_attack_instant_proc->set_extra_attack_buff(extra_attack_buff);
}

ExtraAttackOnNextSwingProc::~ExtraAttackOnNextSwingProc() {
    delete extra_attack_instant_proc;
    delete extra_attack_buff;
}

void ExtraAttackOnNextSwingProc::proc_effect() {
    extra_attack_buff->apply_buff();
}
