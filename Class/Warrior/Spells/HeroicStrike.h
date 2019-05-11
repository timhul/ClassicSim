#ifndef HEROICSTRIKE_H
#define HEROICSTRIKE_H

#include "Spell.h"
#include "TalentRequirer.h"

class NoEffectBuff;
class Warrior;
class WarriorSpells;

class HeroicStrike: public Spell, public TalentRequirer {
public:
    HeroicStrike(Warrior* pchar, WarriorSpells* spells);
    ~HeroicStrike() override;

    bool is_queued() const;
    void cancel();
    void calculate_damage();

private:
    Warrior* warr;
    WarriorSpells* spells;
    NoEffectBuff* hs_buff;
    QVector<unsigned> spell_ranks;
    QVector<unsigned> talent_ranks;
    unsigned additional_dmg;

    void spell_effect() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};

#endif // HEROICSTRIKE_H
