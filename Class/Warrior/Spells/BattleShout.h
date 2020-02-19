#pragma once

#include "Spell.h"
#include "TalentRequirer.h"

class BattleShoutBuff;
class Buff;
class Warrior;

class BattleShout : public Spell, public TalentRequirer {
public:
    BattleShout(Warrior* pchar, BattleShoutBuff* buff, const int spell_rank);
    ~BattleShout() override;

    Buff* get_buff() const;

    bool is_rank_learned() const override;

private:
    BattleShoutBuff* buff;

    const QVector<double> ranks_booming_voice {1.0, 1.1, 1.2, 1.3, 1.4, 1.5};
    const QVector<double> ranks_imp_shout {1.0, 1.05, 1.10, 1.15, 1.20, 1.25};

    int base_duration;
    int next_duration;
    unsigned base_attack_power;
    unsigned modified_by_talents_attack_power;

    void spell_effect() override;
    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
