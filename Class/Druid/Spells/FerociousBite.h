#pragma once

#include <QVector>

#include "Spell.h"
#include "TalentRequirer.h"

class Random;
class Druid;

class FerociousBite: public Spell, public TalentRequirer {
public:
    FerociousBite(Druid* druid, const int spell_rank);
    ~FerociousBite() override;

    bool is_rank_learned() const override;

private:
    Druid* druid;
    Random* instant_dmg;
    double bonus_dmg_per_energy_converted {1.0};
    QVector<QPair<unsigned, unsigned>> damage_ranges_per_combo_point;

    double feral_aggression_modifier {1.0};
    const QVector<double> feral_aggression_modifiers {1.0, 1.03, 1.06, 1.09, 1.12, 1.15};

    void set_combo_point_damage_range();

    void spell_effect() override;
    SpellStatus is_ready_spell_specific() const override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
