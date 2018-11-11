
#include "SweepingStrikes.h"
#include <QDebug>

SweepingStrikes::SweepingStrikes(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Sweeping Strikes", "5ML", "Assets/ability/Ability_rogue_slicedice.png", 1)
{
    QString base_str = "Your next 5 melee attacks strike an additional nearby opponent.";
    rank_descriptions.insert(0, base_str);
    rank_descriptions.insert(1, base_str);
}

SweepingStrikes::~SweepingStrikes() = default;

void SweepingStrikes::apply_rank_effect() {
    // TODO: Decide how rank effects work for this talent.
}

void SweepingStrikes::remove_rank_effect() {
    // TODO: Decide how rank effects work for this talent.
}
