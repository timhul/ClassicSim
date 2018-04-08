
#include "DeepWoundsTalent.h"
#include <QDebug>

DeepWoundsTalent::DeepWoundsTalent(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Deep Wounds", "3MR", "Assets/warrior/arms/tier3/Ability_backstab.png", 3)
{
    QString base_str = "Your critical strikes cause the opponent to bleed, dealing %1% of your melee weapon's average damage over 12 sec.";
    initialize_rank_descriptions(base_str, 20, 20);
}

DeepWoundsTalent::~DeepWoundsTalent() {

}

void DeepWoundsTalent::apply_rank_effect() {
    // TODO: Decide how rank effects work for this talent.
}

void DeepWoundsTalent::remove_rank_effect() {
    // TODO: Decide how rank effects work for this talent.
}
