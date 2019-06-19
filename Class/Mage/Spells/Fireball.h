#pragma once

#include "SpellCastingTime.h"
#include "TalentRequirer.h"

#include <QVector>

class Buff;
class FireballInstant;
class Mage;
class MageSpells;

class Fireball: public SpellCastingTime, public TalentRequirer {
public:
    Fireball(Mage* pchar, const int spell_rank);
    ~Fireball() override;

    bool is_rank_learned() const override;
    void prepare_set_of_combat_iterations() override;

private:
    FireballInstant* damage_spell;

    unsigned base_damage_min;
    unsigned base_damage_max;
    unsigned base_dot_damage;
    int base_dot_duration;
    unsigned base_resource_cost;
    unsigned base_casting_time_ms;
    double spell_dmg_coefficient;
    QVector<unsigned> improved_fireball_ranks {0, 100, 200, 300, 400, 500};

    void spell_effect() override;
    void complete_cast_effect() override;
    void reset_effect() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
