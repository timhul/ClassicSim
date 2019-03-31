#include "InstantSpellProc.h"

#include "Character.h"
#include "CharacterSpells.h"
#include "InstantSpellAttack.h"
#include "ProcInfo.h"
#include "Utils/Check.h"

InstantSpellProc::InstantSpellProc(Character* pchar,
                                   const QString& proc_name,
                                   const QString& icon,
                                   const QVector<ProcInfo::Source>& proc_sources,
                                   const double proc_rate,
                                   const MagicSchool school,
                                   const unsigned min_damage,
                                   const unsigned max_damage) :
    Proc(proc_name, icon, proc_rate, 0, QVector<Proc*>(), proc_sources, pchar),
    spell(new InstantSpellAttack(pchar, proc_name, icon, school, min_damage, max_damage))
{
    check(!proc_sources.empty(), "No valid proc sources found");
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
