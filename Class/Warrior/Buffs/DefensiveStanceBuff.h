#pragma once

#include "SelfBuff.h"
#include "TalentRequirer.h"

class Warrior;

class DefensiveStanceBuff : public SelfBuff, public TalentRequirer {
public:
    DefensiveStanceBuff(Warrior* warrior);

private:
    Warrior* warrior;

    double current_threat_mod;

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
