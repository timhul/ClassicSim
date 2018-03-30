
#include "ImprovedHeroicStrike.h"
#include <QDebug>

ImprovedHeroicStrike::ImprovedHeroicStrike(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Improved Heroic Strike", "1LL", "Assets/warrior/arms/tier1/Ability_rogue_ambush.png", 3)
{
    QString base_str = "Reduces the cost of your Heroic Strike ability by %1 rage.";
    initialize_rank_descriptions(base_str, 1, 1);
}

ImprovedHeroicStrike::~ImprovedHeroicStrike() {

}

void ImprovedHeroicStrike::apply_rank_effect() {
    // TODO: Decide how rank effects work for this talent.
}

void ImprovedHeroicStrike::remove_rank_effect() {
    // TODO: Decide how rank effects work for this talent.
}
