#pragma once

#include "OffhandAttack.h"
#include "TalentRequirer.h"

class OffhandAttackRogue : public OffhandAttack, public TalentRequirer {
public:
    OffhandAttackRogue(Character* pchar);

private:
    friend class DualWieldSpecializationRogue;

    const QVector<double> talent_ranks;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
