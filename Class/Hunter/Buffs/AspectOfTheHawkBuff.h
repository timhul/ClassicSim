#ifndef ASPECTOFTHEHAWKBUFF_H
#define ASPECTOFTHEHAWKBUFF_H

#include "Buff.h"
#include "SetBonusRequirer.h"

class AspectOfTheHawkBuff: public Buff, public SetBonusRequirer {
public:
    AspectOfTheHawkBuff(Character* pchar);

private:
    double dragonstalker_bonus {1.0};

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
    void activate_set_bonus_effect(const QString& set_name, const int set_bonus) override;
    void deactivate_set_bonus_effect(const QString& set_name, const int set_bonus) override;
};

#endif // ASPECTOFTHEHAWKBUFF_H
