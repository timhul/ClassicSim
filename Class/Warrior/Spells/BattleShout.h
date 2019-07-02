#pragma once

#include "Spell.h"
#include "TalentRequirer.h"

class BattleShoutBuff;
class Buff;
class Warrior;

class BattleShout: public Spell, public TalentRequirer {
public:
    BattleShout(Warrior* pchar, BattleShoutBuff* buff);
    ~BattleShout() override;

    Buff* get_buff() const;

private:
    BattleShoutBuff* buff;

    const QVector<unsigned> spell_ranks;
    const QVector<double> ranks_booming_voice;
    const QVector<double> ranks_imp_shout;
    int rank_spell;
    int base_duration;
    int next_duration;
    unsigned base_attack_power;
    unsigned modified_by_talents_attack_power;

    void spell_effect() override;
    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
