#ifndef OFFHANDATTACKROGUE_H
#define OFFHANDATTACKROGUE_H

#include "OffhandAttack.h"
#include "TalentRequirer.h"

class OffhandAttackRogue: public OffhandAttack, public TalentRequirer {
public:
    OffhandAttackRogue(Character* pchar);

private:
    friend class DualWieldSpecializationRogue;

    QVector<double> talent_ranks;

    void increase_talent_rank_effect(const QString& talent_name) override;
    void decrease_talent_rank_effect(const QString& talent_name) override;
};

#endif // OFFHANDATTACKROGUE_H
