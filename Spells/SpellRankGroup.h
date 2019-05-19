#pragma once

#include <QVector>

class Spell;

class SpellRankGroup {
public:
    SpellRankGroup(const QString& name, const QVector<Spell*>& spell_group);

    Spell* get_spell_rank(const int rank);
    Spell* get_max_available_spell_rank();

    const QString name;
    const QVector<Spell*> spell_group;
};
