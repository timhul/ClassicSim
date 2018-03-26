
#include "DeepWounds.h"
#include <QDebug>

DeepWounds::DeepWounds(Character *pchar) :
    Talent(pchar, "Deep Wounds", "3MR", "Assets/warrior/arms/tier3/Ability_backstab.png", 3)
{
    QString base_str = "Your critical strikes cause the opponent to bleed, dealing %1% of your melee weapon's average damage over 12 sec.";
    initialize_rank_descriptions(base_str, 20, 20);
}

DeepWounds::~DeepWounds() {

}

void DeepWounds::apply_rank_effect() {
    // TODO: Decide how rank effects work for this talent.
}

void DeepWounds::remove_rank_effect() {
    // TODO: Decide how rank effects work for this talent.
}
