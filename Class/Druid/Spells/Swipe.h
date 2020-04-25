#pragma once

#include <QVector>

#include "Spell.h"
#include "TalentRequirer.h"

class Druid;
class DruidSpells;
class Proc;

class Swipe : public Spell, public TalentRequirer {
public:
    Swipe(Druid* pchar, DruidSpells* druid_spells, Proc* blood_frenzy, const int spell_rank);
    ~Swipe() override;

    bool is_rank_learned() const override;

private:
    Druid* druid;
    DruidSpells* druid_spells;
    Proc* primal_fury;

    const unsigned base_resource_cost {20};
    unsigned bonus_damage;
    double damage_mod;

    const QVector<unsigned> ferocity_ranks {0, 1, 2, 3, 4, 5};

    void spell_effect() override;
    SpellStatus is_ready_spell_specific() const override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
