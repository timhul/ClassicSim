#pragma once

#include <QVector>

#include "CastingTimeRequirer.h"
#include "Spell.h"
#include "TalentRequirer.h"

class Warrior;
class WarriorSpells;

class SunderArmor : public Spell, public TalentRequirer {
public:
    SunderArmor(Warrior* pchar, WarriorSpells* spells);
    ~SunderArmor() override;

private:
    Warrior* warr;
    WarriorSpells* spells;
    const QVector<unsigned> innate_threat_by_spell_rank;
    unsigned innate_threat;
    const QVector<unsigned> talent_ranks;

    void spell_effect() override;
    SpellStatus is_ready_spell_specific() const override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
