#ifndef DEATHWISHBUFF_H
#define DEATHWISHBUFF_H

#include "Buff.h"
#include "TalentRequirer.h"

class DeathWishBuff: public Buff, public TalentRequirer {
public:
    DeathWishBuff(Character* pchar);

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;

protected:
private:
    friend class DeathWishTalent;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};

#endif // DEATHWISHBUFF_H
