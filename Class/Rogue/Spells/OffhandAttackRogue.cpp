#include "OffhandAttackRogue.h"

OffhandAttackRogue::OffhandAttackRogue(Character* pchar) :
    OffhandAttack(pchar),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Dual Wield Specialization", 5, DisabledAtZero::No)})
{
    talent_ranks = {0.5, 0.55, 0.6, 0.65, 0.7, 0.75};
}

void OffhandAttackRogue::increase_talent_rank_effect(const QString&, const int curr) {
    offhand_penalty = talent_ranks[curr];
}

void OffhandAttackRogue::decrease_talent_rank_effect(const QString&, const int curr) {
    offhand_penalty = talent_ranks[curr];
}
