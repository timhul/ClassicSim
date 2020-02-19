#pragma once

#include "Spell.h"
#include "TalentRequirer.h"

class Buff;
class Warrior;
class WarriorSpells;

class HeroicStrike : public Spell, public TalentRequirer {
public:
    HeroicStrike(Warrior* warrior, WarriorSpells* spells, Buff* hs_buff, const int spell_rank);
    ~HeroicStrike() override;

    bool is_queued() const;
    void cancel();
    void calculate_damage();

    bool is_rank_learned() const override;

private:
    Warrior* warr;
    WarriorSpells* spells;
    Buff* hs_buff;
    unsigned additional_dmg;

    const QVector<unsigned> improved_hs_ranks {15, 14, 13, 12};

    void spell_effect() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
