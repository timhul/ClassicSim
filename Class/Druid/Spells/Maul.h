#pragma once

#include "Spell.h"
#include "TalentRequirer.h"

class Buff;
class Druid;
class DruidSpells;

class Maul : public Spell, public TalentRequirer {
public:
    Maul(Druid* druid, DruidSpells* spells, Buff* maul_buff, const int spell_rank);
    ~Maul() override;

    bool is_queued() const;
    void cancel();
    void calculate_damage();

    bool is_rank_learned() const override;

private:
    Druid* drood;
    DruidSpells* spells;
    Buff* maul_buff;
    unsigned additional_dmg;
    double damage_mod;

    const QVector<unsigned> ferocity_ranks {15, 14, 13, 12, 11, 10};

    void spell_effect() override;
    SpellStatus is_ready_spell_specific() const override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
