
#include "ShadowBoltProc.h"
#include "ShadowBoltAttack.h"
#include "Character.h"
#include "ProcInfo.h"
#include "Spells.h"

ShadowBoltProc::ShadowBoltProc(Character* pchar,
                               const QString& proc_name,
                               const QVector<ProcInfo::Source>& proc_sources,
                               const double proc_rate,
                               const unsigned min_damage,
                               const unsigned max_damage) :
    Proc(proc_name, proc_rate, 0, QVector<Proc*>(), proc_sources, pchar),
    shadow_bolt(new ShadowBoltAttack(pchar, proc_name, min_damage, max_damage))
{
    assert(proc_sources.contains(ProcInfo::Source::MainhandSwing) || proc_sources.contains(ProcInfo::Source::OffhandSwing));
    pchar->get_spells()->add_spell(shadow_bolt);
}

ShadowBoltProc::~ShadowBoltProc() {
    pchar->get_spells()->remove_spell(shadow_bolt);
    shadow_bolt->disable();
    delete shadow_bolt;
}

void ShadowBoltProc::proc_effect() {
    shadow_bolt->perform();
}
