#pragma once

#include <QVector>

#include "CastingTimeRequirer.h"
#include "Spell.h"
#include "TalentRequirer.h"

class Random;
class Warrior;
class WarriorSpells;

class Revenge : public Spell {
public:
    Revenge(Warrior* pchar, WarriorSpells* spells, CooldownControl* cooldown_control);
    ~Revenge() override;

private:
    Warrior* warr;
    WarriorSpells* spells;

    const QVector<unsigned> innate_threat_by_spell_rank;
    unsigned innate_threat;

    unsigned base_damage_min;
    unsigned base_damage_max;
    Random* damage_range;

    void spell_effect() override;
    SpellStatus is_ready_spell_specific() const override;
};
