#include "GenericSpellProc.h"

#include "Character.h"
#include "CharacterSpells.h"
#include "Spell.h"
#include "Utils/Check.h"

GenericSpellProc::GenericSpellProc(
        Character* pchar,
        const QString& proc_name,
        const QString& icon,
        const QVector<ProcInfo::Source>& proc_sources,
        const double proc_rate,
        Spell* spell) :
    Proc(proc_name, icon, proc_rate, 0, QVector<Proc*>(), proc_sources, pchar),
    spell(spell)
{
    check(!proc_sources.empty(), "Must specify at least one proc source");
    pchar->get_spells()->add_spell_group({spell});
}

GenericSpellProc::~GenericSpellProc() {
    pchar->get_spells()->remove_spell(spell);

    if (spell->is_enabled())
        spell->disable();

    delete spell;
}

void GenericSpellProc::proc_effect() {
    spell->perform();
}
