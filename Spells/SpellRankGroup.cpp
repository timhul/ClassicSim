#include "SpellRankGroup.h"

#include "SetBonusRequirer.h"
#include "Spell.h"
#include "Utils/Check.h"

SpellRankGroup::SpellRankGroup(const QString& name, const QVector<Spell*>& spell_group):
    name(name),
    spell_group(spell_group)
{}

Spell* SpellRankGroup::get_spell_rank(const int rank) {
    if (rank >= spell_group.size() || rank < 0)
        return nullptr;

    if (rank == 0)
        return get_max_available_spell_rank();

    Spell* spell = spell_group[rank -1];
    check((spell->get_spell_rank() == rank), QString("Asked for explicit rank but got mismatched rank for %1").arg(name).toStdString());

    return spell->is_rank_learned() ? spell : nullptr;
}

Spell* SpellRankGroup::get_max_available_spell_rank() {
    Spell* available = nullptr;

    for (const auto & spell : spell_group) {
        if (!spell->is_rank_learned())
            break;

        available = spell;
    }

    return available;
}
