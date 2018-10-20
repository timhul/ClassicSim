
#include "NatureDamageProc.h"
#include "NatureDamageAttack.h"
#include "Character.h"
#include "ProcInfo.h"
#include "Spells.h"

NatureDamageProc::NatureDamageProc(Character* pchar,
                               const QString& proc_name,
                               const QVector<ProcInfo::Source>& proc_sources,
                               const double proc_rate,
                               const unsigned min_damage,
                               const unsigned max_damage) :
    Proc(proc_name, proc_rate, 0, QVector<Proc*>(), proc_sources, pchar),
    nature_damage(new NatureDamageAttack(pchar, proc_name, min_damage, max_damage))
{
    assert(proc_sources.contains(ProcInfo::Source::MainhandSwing) || proc_sources.contains(ProcInfo::Source::OffhandSwing));
    pchar->get_spells()->add_spell(nature_damage);
}

NatureDamageProc::~NatureDamageProc() {
    pchar->get_spells()->remove_spell(nature_damage);
    nature_damage->disable();
    delete nature_damage;
}

void NatureDamageProc::proc_effect() {
    nature_damage->perform();
}
