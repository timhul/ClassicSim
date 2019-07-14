#include "ExtraAttackOnNextSwingProc.h"

#include "Character.h"
#include "ExtraAttackInstantProc.h"
#include "ExtraAttackOnNextSwingBuff.h"
#include "ProcInfo.h"
#include "Utils/Check.h"

ExtraAttackOnNextSwingProc::ExtraAttackOnNextSwingProc(Character* pchar,
                                                       const QString& proc_name,
                                                       const QString& icon,
                                                       const QVector<ProcInfo::Source>& proc_sources,
                                                       const double proc_rate,
                                                       const int num_attacks) :
    Proc(proc_name, icon, proc_rate, 0, QVector<Proc*>(), proc_sources, pchar),
    extra_attack_instant_proc(new ExtraAttackInstantProc(pchar,
                                                         QString("%1 Instant").arg(proc_name),
                                                         icon,
                                                         proc_sources, 1.0, num_attacks)),
    extra_attack_buff(new ExtraAttackOnNextSwingBuff(pchar, extra_attack_instant_proc, num_attacks))
{
    check((proc_sources.contains(ProcInfo::Source::MainhandSwing) || proc_sources.contains(ProcInfo::Source::OffhandSwing)),
          "No valid proc sources found");
    extra_attack_instant_proc->set_extra_attack_buff(extra_attack_buff);
    extra_attack_buff->enable_buff();
}

ExtraAttackOnNextSwingProc::~ExtraAttackOnNextSwingProc() {
    extra_attack_buff->disable_buff();
    delete extra_attack_instant_proc;
    delete extra_attack_buff;
}

void ExtraAttackOnNextSwingProc::proc_effect() {
    extra_attack_buff->apply_buff();
}

void ExtraAttackOnNextSwingProc::prepare_set_of_combat_iterations_spell_specific() {
    extra_attack_instant_proc->prepare_set_of_combat_iterations();
}
