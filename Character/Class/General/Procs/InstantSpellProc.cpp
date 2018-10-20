
#include "InstantSpellProc.h"
#include "InstantSpellAttack.h"
#include "Character.h"
#include "ProcInfo.h"
#include "Spells.h"

InstantSpellProc::InstantSpellProc(Character* pchar,
                                   const QString& proc_name,
                                   const QVector<ProcInfo::Source>& proc_sources,
                                   const double proc_rate,
                                   const MagicSchool school,
                                   const unsigned min_damage,
                                   const unsigned max_damage) :
    Proc(proc_name, proc_rate, 0, QVector<Proc*>(), proc_sources, pchar),
    spell(new InstantSpellAttack(pchar, proc_name, school, min_damage, max_damage))
{
    assert(proc_sources.contains(ProcInfo::Source::MainhandSwing) || proc_sources.contains(ProcInfo::Source::OffhandSwing));
    pchar->get_spells()->add_spell(spell);
}

InstantSpellProc::~InstantSpellProc() {
    pchar->get_spells()->remove_spell(spell);
    spell->disable();
    delete spell;
}

void InstantSpellProc::proc_effect() {
    spell->perform();
}
