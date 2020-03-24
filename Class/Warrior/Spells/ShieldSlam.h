#pragma once

#include <QVector>

#include "CastingTimeRequirer.h"
#include "Spell.h"
#include "TalentRequirer.h"

class Random;
class Warrior;
class WarriorSpells;

class ShieldSlam : public Spell, public TalentRequirer {
public:
    ShieldSlam(Warrior* pchar, WarriorSpells* spells, CooldownControl* cooldown_control);
    ~ShieldSlam() override;

private:
    Warrior* warr;
    WarriorSpells* spells;

    unsigned innate_threat;

    unsigned base_damage_min;
    unsigned base_damage_max;
    Random* damage_range;

    void spell_effect() override;
    SpellStatus is_ready_spell_specific() const override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
