#pragma once

#include "SpellPeriodic.h"
#include "TalentRequirer.h"

#include <QVector>

class Buff;
class Warrior;
class WarriorSpells;

class Rend: public SpellPeriodic, public TalentRequirer {
public:
    Rend(Warrior* pchar, WarriorSpells* spells);
    ~Rend() override;

private:
    Warrior* warr;
    WarriorSpells* spells;
    double talent_modifier;
    double damage_remaining;
    int base_damage;
    double period_tick;
    int max_ticks;
    int num_ticks_left;
    const QVector<double> talent_ranks;

    SpellStatus is_ready_spell_specific() const override;
    bool check_application_success() override;
    void new_application_effect() override;
    void refresh_effect() override;
    void tick_effect() override;
    void reset_effect() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
