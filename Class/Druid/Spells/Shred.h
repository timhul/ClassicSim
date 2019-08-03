#pragma once

#include "Spell.h"
#include "TalentRequirer.h"

#include <QVector>

class Druid;
class DruidSpells;

class Shred: public Spell, public TalentRequirer {
public:
    Shred(Druid* pchar, DruidSpells* druid_spells, const int spell_rank);
    ~Shred() override;

    bool is_rank_learned() const override;

private:
    Druid* druid;
    DruidSpells* druid_spells;

    const unsigned base_resource_cost {60};
    unsigned bonus_damage;

    QVector<unsigned> improved_shred_ranks {0, 6, 12};

    void spell_effect() override;
    SpellStatus is_ready_spell_specific() const override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
